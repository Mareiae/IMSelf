#include "chat.h"
#include "UI/friend.h"
#include "UI/perinfowidget.h"
#include "UI/permesswidget.h"
#include "Socket/Client/tcp.h"
#include "Socket/Client/udp.h"
#include <QListWidgetItem>
#include <QDebug>
Chat::Chat(const QMap<QString,QString>& pSelfInfo)
    :MainForm(pSelfInfo)
{
    QString nick[3] = {"Keing","Kynic","La Fe"};
    QString id[3] = {"84545822@qq.com","251525@qq.com","1521512@qq.com"};
    for(int i = 0;i < 3;++i){
        QMap<QString,QString> map;
        map.insert("img",":/Icons/1.jpg");
        map.insert("nick",nick[i]);
        map.insert("id",id[i]);
        map.insert("remark","");
        m_friendFlist.push_back(map);
    }
    sendLoginStatus();//向服务器发送当前账号登录状态;
    addFriend();//添加好友列表;
    childThreadStart(); //启动客户端子线程;接收其他朋友消息;
    connect(&childThreadobj,&Server::recvNewMessage,this,&Chat::recvNewMessage); //连接子线程信号;
}
Chat::~Chat()
{
    childThreadobj.closeThread(true);
}
void Chat::addFriend()
{
    //好友列表为空时;
    if(m_friendFlist.empty()){
        QListWidgetItem * item = new QListWidgetItem;
        item->setText("暂无好友");
        item->setTextAlignment(Qt::AlignCenter);
        getFriendListWidget()->addItem(item);
        return;
    }

    for(const auto& perFriend : m_friendFlist){
        QPixmap head;
        head.load(perFriend["img"]);
        FriendInfoWidget *perWidget = new FriendInfoWidget(
                    head.scaled(50,50),perFriend["nick"],perFriend["id"],perFriend["remark"],getFlexDiget());

        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(210,60));
        getFriendListWidget()->addItem(item);
        getFriendListWidget()->setItemWidget(item,perWidget->getWidget());
    }
}
void Chat::friendListSelectedItem()
{
    //显示个人信息组件;
    getPerInfoStack()->setCurrentIndex(2);
    //获取当前选中的行;
    int row = getFriendListWidget()->currentRow();
    if(row > m_friendFlist.size()){
        return;
    }
    //检查原先是否已存在面板;
    QLayoutItem * item;
    while((item = getCardLayout()->takeAt(0)) != nullptr)
    {
        //若存在则只需跟新个人信息;
        if(item->widget())
        {
            delete item->widget();
        }
        delete item;
    }

    QPixmap head;
    QString nick,id,remark;
    head.load(m_friendFlist[row].value("img"));
    nick = m_friendFlist[row].value("nick");
    id = m_friendFlist[row].value("id");
    remark = m_friendFlist[row].value("remark");

    //若不存在则添加新的个人面板;
    PerInfoWidget *perItem = new PerInfoWidget(head,nick,remark,id,getFlexDiget());
    getCardLayout()->addWidget(perItem->getPerWidget());
    //设置组件水平居中显示;
    getCardLayout()->setAlignment(perItem->getPerWidget(),Qt::AlignHCenter|Qt::AlignVCenter);
    //发送按钮点击事件;
    connect(perItem,&PerInfoWidget::infoWidSendBtn_onClicked,this,[=]()
    {
        this->perInfoSendBtn_onClicked(perItem->getHeadimg(),perItem->getNick(),perItem->getId());
    });
}
void Chat::perInfoSendBtn_onClicked(const QPixmap& head,const QString& nick,const QString& id)
{
    getPerInfoStack()->setCurrentIndex(1);
    getFriendIpRequest(id);    //向服务器发送请求，获取好友ip地址;

    //点击发送按钮则更新聊天面板信息;
    QLayoutItem * item;
    while((item = getMessLayout()->takeAt(0)) != nullptr)
    {
        //当聊天面板已存在时;
        if(item->widget())
        {
            delete item->widget();
        }
        delete item;
    }
    //不存在则添加新的面板;
    PerMessWidget *pitem = new PerMessWidget(head,nick,id,getFlexDiget());
    getMessLayout()->addWidget(pitem);
    connect(pitem,&PerMessWidget::messSendBtnonClicked,this,&Chat::sendtoMessage);
    ptr_messListWidget = pitem->getMessListWidget();
}
void Chat::sendLoginStatus()
{
    /*
     * 向服务器发送当前账号登录状态;
     * */
    //创建udp数据包;
    UDP::MSG msg;
    memset(&msg,0,sizeof (msg));
    msg.type = UDP::LOGIN;
    strcpy(msg.send_user,getSelfInfoMap().find("id")->toUtf8().data());
    char send_msg[sizeof(msg)] = {0};
    memcpy(send_msg,&msg,sizeof(msg));

    //创建一个udp socket套接字;
    Udp m_udp;
    if(!m_udp.initServer("47.106.14.185",5500)) return;
    m_udp.sendMessage(send_msg,sizeof (send_msg));
}
void Chat::getFriendIpRequest(const QString &friendId)
{
    /*
     * 向服务器发送请求，获取当前要发送消息的朋友对象的ip;
     * */
    //创建udp套接字;
    Udp m_udp;
    m_udp.initServer("47.106.14.185",5500);
    //创建udp套接字数据包;
    UDP::MSG pack;
    memset(&pack,0,sizeof (pack));
    pack.type = UDP::IPREQUEST;
    strcpy(pack.send_user,getSelfInfoMap().find("id")->toUtf8().data());
    strcpy(pack.recv_user,friendId.toUtf8().data());
    char sendBuff[sizeof (pack)] = {0};
    memcpy(sendBuff,&pack,sizeof (pack));
    //向服务器发送请求,获取当前好友ip;
    m_udp.sendMessage(sendBuff,sizeof (pack));
}
void Chat::childThreadStart()
{
    /*
     * 客户端子线程执行函数;
     * 负责接收是否有新的消息;
     * */
    std::thread child_thread(&Server::recvMessage,std::ref(childThreadobj));
    child_thread.detach(); //主线程和子线程分开执行;
}
void Chat::recvNewMessage(const char *buff)
{
    //将接收到的缓冲消息转化为数据包;
    UDP::MSG pack;
    memset(&pack,0,sizeof (pack));
    memcpy(&pack,buff,sizeof(pack));

    char *dstIp = inet_ntoa(pack.addr.sin_addr);
    //如果包的种类为获取朋友ip;
    if(pack.type == UDP::IPREQUEST){
        //若朋友不在线则向服务器转发消息;
        if(strcmp(dstIp,"0.0.0.0") == 0){
            friendAddressTuple = std::make_tuple<QString,int>("47.106.14.185",5500);
        }else{
            //若朋友在线则直接向朋友发送消息;
            friendAddressTuple = std::make_tuple<QString,int>(dstIp,5501);
        }
    }else if(pack.type == UDP::CONNECT){
        //若包类型为请求连接包，则向朋友发送探测包;
        builtConnect(pack.send_user,dstIp);
    }else if(pack.type == UDP::CHAR){
        qDebug()<<"recv new mess:"<<pack.send_char;
        addMessToListWidget(pack.send_char);
    }
}
void Chat::builtConnect(const QString &sendUser, const char *sendIp)
{
    UDP::MSG pack;
    size_t size_p = sizeof (pack);
    memset(&pack,0,size_p);
    pack.type = UDP::NAT; //申明包的类型为探测包;

    //添加发送人，接收人;
    strcpy(pack.send_user,getSelfInfoMap().find("id")->toUtf8().data());
    strcpy(pack.recv_user,sendUser.toUtf8().data());
    char send_msg[sizeof (pack)] = {0};
    memcpy(send_msg,&pack,size_p);

    //创建udp套接字发送探测包;
    Udp udp;
    udp.initServer(sendIp,5501);
    udp.sendMessage(send_msg,sizeof (send_msg));
}
void Chat::sendtoMessage(const QString& text)
{
    if(std::get<0>(friendAddressTuple) == nullptr) return;
    //新建发送数据包;
    UDP::MSG pack;
    memset(&pack,0,sizeof (pack));
    pack.type = UDP::CHAR; //数据包类型表示为有新的聊天信息;
    strcpy(pack.send_user,getSelfInfoMap().find("id")->toUtf8().data());
    strcpy(pack.send_char,text.toUtf8().data());

    //建立发送缓冲;
    char sendBuff[sizeof (pack)] = {0};
    memcpy(sendBuff,&pack,sizeof (pack));

    //创建udp套接字;
    Udp udp;
    udp.initServer(std::get<0>(friendAddressTuple).toUtf8().data(),std::get<1>(friendAddressTuple));
    bool flag = udp.sendMessage(sendBuff,sizeof (sendBuff));
    if(flag){
        addMessToListWidget(text);
    }
}
void Chat::addMessToListWidget(const QString& text)
{
    if(ptr_messListWidget == nullptr){
        return;
    }
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(text);
    ptr_messListWidget->addItem(item);
}

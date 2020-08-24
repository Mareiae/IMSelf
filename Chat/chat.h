#ifndef CHAT_H
#define CHAT_H
#include "UI/mainform.h"
#include "Socket/Server/server.h"
#include <thread>
class Chat:public MainForm
{
public:
    explicit Chat(const QMap<QString,QString>& pSelfInfo);
    ~Chat();
    void addFriend();   //添加朋友列表;
    void sendLoginStatus(); //向服务器发送当前账号在线状态;
    void getFriendIpRequest(const QString& friendId);//向服务器获取朋友ip地址;
    void childThreadStart(); //启动子线程接数据;
    void recvNewMessage(const char* buff); //接收消息处理函数;
    void sendtoMessage(const QString& text); //发送消息函数;
    void builtConnect(const QString& sendUser,const char *sendIp); //探测包发送函数;
    void addMessToListWidget(const QString& text);//将接收到的消息添加到列表控件中;


private:
    //存储朋友列表信息容器;keys:img头像文件路径,nick昵称,id账号,remark备注;
    QVector<QMap<QString,QString>> m_friendFlist;
    Server childThreadobj; //子线程执行内容;
    std::tuple<QString, u_short> friendAddressTuple; //动态存储朋友ip信息;
    QListWidget *ptr_messListWidget; //聊天消息列表显示控件;
protected:
    void friendListSelectedItem(); //好友列表点击事件;
public slots:
    //好友个人信息面板中发送消息按钮点击事件;
    void perInfoSendBtn_onClicked(const QPixmap& head,const QString& nick,const QString& id);
};

#endif // CHAT_H

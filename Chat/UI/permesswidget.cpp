#include "permesswidget.h"
#include <QScrollBar>
#include <QVBoxLayout>
#include <QToolTip>
#include <QShortcut>
PerMessWidget::PerMessWidget(const QPixmap& head,const QString& nick,const QString& id,double flexDiget,QWidget *parent)
    :QWidget(parent),m_head(head),m_nick(nick),m_id(id),m_flexDiget(flexDiget)
{
    setStyleSheet("QWidget{background-color:#fafafa}");
    setObjectName("perMessWidget");

    QVBoxLayout *ptr_mainlay = new QVBoxLayout;
    ptr_mainlay->addLayout(addNickChatList(),5);
    ptr_mainlay->addLayout(addtoolList(),1);
    ptr_mainlay->addLayout(addTextEdit(),1);
    ptr_mainlay->setMargin(0);
    ptr_mainlay->setSpacing(11);
    setLayout(ptr_mainlay);
}
PerMessWidget::~PerMessWidget()
{

}
QLayout* PerMessWidget::addNickChatList()
{
    //设置昵称标签;
    ptr_nicklabel = new QLabel(m_nick);
    ptr_nicklabel->setFont(QFont("微软雅黑",12));

    //消息显示列表;
    ptr_messList = new QListWidget;
    ptr_messList->setStyleSheet("QListWidget{background-color:#fafafa;border:0px}");
    ptr_messList->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {border: none;"
                                                 "background: #dfdfdf;"
                                                 "width: 12px;}"
                                                 "QScrollBar::handle:vertical {border: none;"
                                                 "border-radius: 5px;"
                                                 "background: #cfcfcf;}");
    ptr_messList->horizontalScrollBar()->hide();

    QVBoxLayout *ptr_nickMesslay = new QVBoxLayout;
    ptr_nickMesslay->addWidget(ptr_nicklabel);
    ptr_nickMesslay->addWidget(ptr_messList);
    return ptr_nickMesslay;
}
QLayout* PerMessWidget::addtoolList()
{
    //添加表情，文件，截图，聊天记录，语言聊天，视频聊天组件;
    QString iconsName[6] = {"face.svg","file.svg","cut.svg","chatRecord.svg","soundChat.svg","videoChat.svg"};
    QString toolTipName[6] = {"表情","文件","截图","聊天记录","语言聊天","视频聊天"};
    QHBoxLayout *ptr_toollay = new QHBoxLayout;
    for(int i = 0;i < 6;++i){
        ptr_toolBtn[i] = new QPushButton;
        ptr_toolBtn[i]->setToolTip(toolTipName[i]);
        ptr_toolBtn[i]->setIcon(QIcon(":/Icons/"+iconsName[i]));
        ptr_toolBtn[i]->setFlat(true);
        ptr_toolBtn[i]->setFixedSize(QSize(int(20*m_flexDiget),int(20*m_flexDiget)));
        ptr_toolBtn[i]->setIconSize(QSize(int(20*m_flexDiget),int(20*m_flexDiget)));
        ptr_toolBtn[i]->setStyleSheet("QPushButton{border-style:none;}");
        if(i == 4)
            ptr_toollay->addStretch();
        ptr_toollay->addWidget(ptr_toolBtn[i]);
        connect(ptr_toolBtn[i],&QPushButton::clicked,this,[=]()
        {
            QString sendChar = ptr_messEdit->toPlainText();
            if(sendChar.isEmpty())
            {
                QPoint xy = ptr_sendBtn->pos();
                xy.setX(xy.x()-10);
                xy.setY(xy.y()+250);
                QToolTip::showText(mapToGlobal(xy),"发送信息不能为空");
                return;
            }
            emit messToolItemonClicked();
        });
    }
    ptr_toollay->setMargin(int(10*m_flexDiget));
    ptr_toollay->setSpacing(int(10*m_flexDiget));
    ptr_toollay->setContentsMargins(int(25*m_flexDiget),0,int(25*m_flexDiget),10);
    return ptr_toollay;
}
QLayout* PerMessWidget::addTextEdit()
{
    //富文本输入框设置;
    ptr_messEdit = new QTextEdit;
    ptr_messEdit->setStyleSheet("QTextEdit{border-style:none}");
    ptr_messEdit->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {border: none;background: #dfdfdf;"
                                                 "width: 8px;}"
                                                 "QScrollBar::handle:vertical {border: none;"
                                                 "border-radius: 3px;"
                                                 "background: #cfcfcf;}"
                                                 "QScrollBar::add-page:vertical {border: none;"
                                                 "background-color: #dfdfdf;}"
                                                 "QScrollBar::sub-page:vertical {border: none;"
                                                 "background-color: #dfdfdf;}");
    ptr_messEdit->setFont(QFont("微软雅黑",10,QFont::Normal));
    ptr_messEdit->setAcceptDrops(true);


    //发送按钮;
    ptr_sendBtn = new QPushButton("发送(S)");
    ptr_sendBtn->setFixedSize(QSize(int(65*m_flexDiget),int(30*m_flexDiget)));
    ptr_sendBtn->setStyleSheet("QPushButton{border:0px; border-radius:4px;background-color:#f9f9f9}"
                           "QPushButton:hover{border:0px; border-radius:4px;background-color:#6495ED;"
                           "color:#F8F8FF;padding-left:-1px;padding-bottom:-1px}"
                           "#QPushButton:pressed{border:0px; border-radius:4px;background-color:#5CACEE;"
                           "color:white;padding-left:-1px;padding-bottom:-1px}");
    ptr_sendBtn->setFont(QFont("微软雅黑",10));
    QHBoxLayout *ptr_sendlay = new QHBoxLayout;
    ptr_sendlay->addStretch();
    ptr_sendlay->addWidget(ptr_sendBtn);
    connect(ptr_sendBtn,&QPushButton::clicked,this,[=]()
    {
        QString sendChar = ptr_messEdit->toPlainText();
        if(sendChar.isEmpty())
        {
            QPoint xy = ptr_sendBtn->pos();
            xy.setX(xy.x());
            xy.setY(xy.y()+15);
            QToolTip::showText(mapToGlobal(xy),"内容不能为空");
            return;
        }
        emit messSendBtnonClicked(sendChar);
        ptr_messEdit->clear();
    });

    QVBoxLayout *ptr_mlay = new QVBoxLayout;
    ptr_mlay->addWidget(ptr_messEdit);
    ptr_mlay->addLayout(ptr_sendlay);
    ptr_mlay->setContentsMargins(int(25*m_flexDiget),0,int(25*m_flexDiget),10);
    return ptr_mlay;
}

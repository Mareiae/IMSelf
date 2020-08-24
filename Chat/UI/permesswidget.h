#ifndef PERMESSWIDGET_H
#define PERMESSWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QWidget>
class PerMessWidget:public QWidget
{
    Q_OBJECT
public:
    PerMessWidget(const QPixmap& head,const QString& nick,const QString& id,double flexDiget,QWidget *parent = nullptr);
    ~PerMessWidget();
    QLayout* addNickChatList(); //昵称，消息列表设置;
    QLayout* addtoolList(); //工具栏设置;
    QLayout* addTextEdit(); //消息内容编辑设置;


private:
    QPixmap m_head; //头像;
    QString m_nick; //昵称;
    QString m_id;   //账号;
    double m_flexDiget; //缩放系数;

    QLabel *ptr_nicklabel;  //昵称标签;
    QListWidget *ptr_messList;  //消息记录显示列表;
    QTextEdit *ptr_messEdit;    //消息编辑控件;
    QPushButton *ptr_sendBtn;   //发送消息按钮;
    QPushButton *ptr_toolBtn[6];    //工具栏按钮;

signals:
    //工具栏按钮点击事件;
    void messToolItemonClicked();
    //发送消息按钮点击事件;
    void messSendBtnonClicked(const QString&);

public:
    //更新发送消息面板信息;
    void updateMessWidInfo(const QPixmap& head,const QString& nick,const QString& id)
    {
        m_head = head;
        m_nick = nick;
        m_id = id;
    }
    QString getNick()
    {
        return m_nick;
    }
    QListWidget* getMessListWidget()const{
        return  ptr_messList;
    }
};

#endif // PERMESSWIDGET_H

#ifndef CHATRECORDWIDGET_H
#define CHATRECORDWIDGET_H
#include <QWidget>
#include <QLabel>
class ChatRecordWidget
{
public:
    ChatRecordWidget(QPixmap& headimg,QString& id,QString& nickName,QString& chatText,QString& lastTime);
    ~ChatRecordWidget();
    QWidget* getChatRecordWidget();
private:
    QWidget *ptr_recordWidget;  //聊天记录部件；
    QLabel *ptr_headimg;
    QLabel *ptr_textChat;
    QLabel *ptr_lastTime;
    QLabel *ptr_nickName;

    QPixmap m_headimg;  //头像；
    QString m_id;   //账号id;
    QString m_nickName; //昵称;
    QString m_chatText; //聊天信息;
    QString m_lastTime; //时间;

protected:
    //更新头像;
    void updateHeadimg(const QPixmap& head){
        ptr_headimg->setPixmap(head.scaled(50,50));
    }
    //更新聊天内容;
    void updateChatText(const QString& text){
        ptr_textChat->setText(text);
    }
    //更新聊天时间;
    void updateChatTime(const QString& time){
        ptr_lastTime->setText(time);
    }
    //更新昵称;
    void updateNickName(const QString& nickName){
        ptr_nickName->setText(nickName);
    }
};

#endif // CHATRECORDWIDGET_H

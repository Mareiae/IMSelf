#include "chatrecordwidget.h"
#include <QGridLayout>
ChatRecordWidget::ChatRecordWidget(QPixmap& headimg,QString& id,QString& nickName,QString& chatText,QString& lastTime)
    :m_headimg(headimg),m_id(id),m_nickName(nickName),m_chatText(chatText),m_lastTime(lastTime)
{
    ptr_headimg = new QLabel;
    ptr_headimg->setPixmap(m_headimg.scaled(50,50));

    ptr_nickName = new QLabel;
    ptr_nickName->setText(m_nickName);

    ptr_lastTime = new QLabel;
    ptr_lastTime->setText(m_lastTime);

    ptr_textChat = new QLabel;
    if(m_chatText.size() > 8){
        m_chatText.resize(11);
        m_chatText[8] = '.';
        m_chatText[9] = '.';
        m_chatText[10] = '.';
        ptr_textChat->setText(m_chatText);
    }
    ptr_textChat->setFont(QFont("Consolas",9));

    QGridLayout *ptr_mlay = new QGridLayout;
    ptr_mlay->addWidget(ptr_headimg,0,0,2,1);
    ptr_mlay->addWidget(ptr_nickName,1,0,1,1);
    ptr_mlay->addWidget(ptr_lastTime,2,0,1,1);
    ptr_mlay->addWidget(ptr_textChat,1,1,1,1);
    ptr_mlay->setSpacing(10);

    ptr_recordWidget = new QWidget;
    ptr_recordWidget->setLayout(ptr_mlay);
}
ChatRecordWidget::~ChatRecordWidget()
{

}
QWidget* ChatRecordWidget::getChatRecordWidget()
{
    return ptr_recordWidget;
}

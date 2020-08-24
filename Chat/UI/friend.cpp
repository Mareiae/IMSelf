#include "friend.h"
#include <QHBoxLayout>
FriendInfoWidget::FriendInfoWidget(const QPixmap& heading, const QString &nickName, const QString &id, const QString &remark,double flexDiget)
    :ptr_headimg(heading),m_nickName(nickName),m_id(id),m_remark(remark),m_flexDiget(flexDiget)
{
    //显示头像;
    QLabel *ptr_headLabel = new QLabel;
    ptr_headLabel->setPixmap(ptr_headimg.scaled(int(50*m_flexDiget),int(50*m_flexDiget)));

    //显示昵称备注;
    ptr_remarkLabel = new QLabel;
    if(m_remark == ""){
        ptr_remarkLabel->setText(m_nickName);
    }else{
        ptr_remarkLabel->setText(m_remark);
    }
    ptr_remarkLabel->setFont(QFont("Consolas",11));

    QHBoxLayout *ptr_mlay = new QHBoxLayout;
    ptr_mlay->addWidget(ptr_headLabel);
    ptr_mlay->addWidget(ptr_remarkLabel);
    ptr_mlay->setSpacing(10);
    ptr_mlay->addStretch();

    ptr_friendWid = new QWidget;
    ptr_friendWid->setLayout(ptr_mlay);
}
FriendInfoWidget::~FriendInfoWidget()
{

}
QWidget* FriendInfoWidget::getWidget()
{
    //返回单个朋友信息标签;
    return ptr_friendWid;
}

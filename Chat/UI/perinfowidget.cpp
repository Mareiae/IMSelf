#include "perinfowidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
PerInfoWidget::PerInfoWidget(const QPixmap& head,const QString& nick,const QString& remark,const QString& id,double flexDiget,QWidget *parent)
    :QWidget(parent),m_head(head),m_nick(nick),m_id(id),m_remark(remark),m_flexDiget(flexDiget)
{
    //添加昵称，头像标签;
    ptr_head = new QLabel;
    ptr_head->setPixmap(head.scaled(int(75*m_flexDiget),int(75*m_flexDiget)));
    ptr_nick = new QLabel;
    if(m_remark == ""){
        ptr_nick->setText(m_nick);
     }else {
        ptr_nick->setText(m_remark);
    }
    ptr_nick->setFont(QFont("Microsoft YaHei",13,QFont::Normal));
    QHBoxLayout *h1lay = new QHBoxLayout;
    h1lay->addWidget(ptr_nick);
    h1lay->addStretch();
    h1lay->addWidget(ptr_head);

    //添加账号标签;
    QLabel *ptr_idLabel = new QLabel("账号:");
    ptr_idLabel->setFont(QFont("微软雅黑",10));
    ptr_id = new QLabel(m_id);
    ptr_id->setFont(QFont("Consolas",11));

    //添加备注标签;
    QLabel *ptr_remarkLabel = new QLabel("备注:");
    ptr_remarkLabel->setFont(QFont("微软雅黑",10));
    ptr_remark = new QLineEdit;
    if(m_remark == ""){
        ptr_remark->setPlaceholderText("点击添加备注");
    }else {
        ptr_remark->setText(m_remark);
    }
    ptr_remark->setFont(QFont("微软雅黑",11));
    ptr_remark->setStyleSheet("QLineEdit{border-style:none;background-color:#fafafa;}"
                              "QLineEdit:focus{border-bottom:1px solid #87CEFA;border-style:outset;background-color:#fafafa;}");


    QVBoxLayout * vlay2 = new QVBoxLayout;
    QVBoxLayout * vlay3 = new QVBoxLayout;
    vlay2->addWidget(ptr_remarkLabel);
    vlay2->addWidget(ptr_idLabel);
    vlay3->addWidget(ptr_remark);
    vlay3->addWidget(ptr_id);

    QHBoxLayout * hblay = new QHBoxLayout;
    hblay->addLayout(vlay2);
    hblay->addLayout(vlay3);
    hblay->setSpacing(int(30*m_flexDiget));

    //添加发送消息按钮;
    QPushButton *ptr_sendBtn = new QPushButton("发送消息");
    ptr_sendBtn->setStyleSheet("QPushButton{border-radius:3px;background-color:#008B00;border-style:none;color:white}"
                           "QPushButton:hover{background-color:#00CD66;color:white}");
    ptr_sendBtn->setFixedSize(QSize(int(180*m_flexDiget),int(35*m_flexDiget)));
    ptr_sendBtn->setFont(QFont("微软雅黑",12));
    connect(ptr_sendBtn,&QPushButton::clicked,this,[&]()
    {
        //若点击发送消息按钮时，则促发信号;
        emit infoWidSendBtn_onClicked();
    });
    QHBoxLayout * hlay4 = new QHBoxLayout;
    hlay4->addWidget(ptr_sendBtn);

    h1lay->setAlignment(Qt::AlignCenter);
    hblay->setAlignment(Qt::AlignCenter);
    hlay4->setAlignment(Qt::AlignCenter);
    QVBoxLayout * vlay = new QVBoxLayout;
    vlay->addStretch();
    vlay ->addLayout(h1lay);
    vlay->addLayout(hblay);
    vlay->addLayout(hlay4);
    vlay->addStretch();
    vlay->setMargin(0);
    vlay->setSpacing(int(50*m_flexDiget));

    ptr_perInfoWidget = new QWidget;
    ptr_perInfoWidget->setFixedSize(QSize(int(370*m_flexDiget),int(270*m_flexDiget)));
    ptr_perInfoWidget->setLayout(vlay);


}
PerInfoWidget::~PerInfoWidget(){}
QWidget* PerInfoWidget::getPerWidget()
{
    return ptr_perInfoWidget;
}
void  PerInfoWidget::updataInfoWidget(const QPixmap& head,const QString& nick,const QString& id,const QString& remark)
{
    m_head = head;
    m_nick  = nick;
    m_id = id;
    m_remark = remark;

    ptr_head->setPixmap(m_head.scaled(int(75*m_flexDiget),int(75*m_flexDiget)));
    ptr_nick->setText(m_nick);
    ptr_id->setText(m_id);
    ptr_remark->setText(m_remark);
}

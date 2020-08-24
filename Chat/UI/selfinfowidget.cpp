#include "UI/selfinfowidget.h"
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
SelfInfoWidget::SelfInfoWidget(const QMap<QString,QString>& pSelfInfo,double flexDiget)
    :selfInfo(pSelfInfo),m_flexDiget(flexDiget)
{
    setCursor(QCursor(Qt::PointingHandCursor));  //更改鼠标样式;
    setIcon(QIcon(selfInfo["img"]));

    setIconSize(QSize(int(37*m_flexDiget),int(37*m_flexDiget)));
    setFixedSize(QSize(int(37*m_flexDiget),int(37*m_flexDiget)));
    setMenu(infoWidget());
}
SelfInfoWidget::~SelfInfoWidget(){

}
QMenu* SelfInfoWidget::infoWidget()
{
    //添加账号，昵称标签
    QLabel *ptr_infolab[3];
    std::vector<QString> vec = {selfInfo["user"],"账号:",selfInfo["id"]};
    for(unsigned i = 0;i < 3;++i)
    {
        ptr_infolab[i] = new QLabel(vec[i]);
        if(i == 0)
        {
            ptr_infolab[i]->setFont(QFont("Microsoft YaHei",12));
            ptr_infolab[i]->setStyleSheet("QLabel{color:#262b31}");
        }else{
            ptr_infolab[i]->setFont(QFont("Microsoft YaHei",10));
            ptr_infolab[i]->setStyleSheet("QLabel{color:#6d757e}");
        }
    }
    //添加更换头像按钮;
    QPushButton *ptr_changeImg = new QPushButton("更换头像");
    ptr_changeImg->setFixedSize(QSize(int(100*m_flexDiget),int(25*m_flexDiget)));
    ptr_changeImg->setFont(QFont("Microsoft YaHei",10,QFont::Bold));
    ptr_changeImg->setStyleSheet("QPushButton{border-radius:3px;background-color:#008B00;border-style:none;color:white}"
                           "QPushButton:hover{background-color:#00CD66;color:white}");

    //添加头像显示标签;
    QLabel *ptr_imglab = new QLabel;
    ptr_imglab->setPixmap(QPixmap(selfInfo["img"]).scaled(int(60*m_flexDiget),int(60*m_flexDiget)));

    //为窗体添加栅格布局;
    QGridLayout *ptr_gridlay = new QGridLayout;
    ptr_gridlay->addWidget(ptr_infolab[0],0,0,1,2);
    ptr_gridlay->addWidget(ptr_infolab[1],1,0,1,1);
    ptr_gridlay->addWidget(ptr_infolab[2],1,1,1,1);
    ptr_gridlay->addWidget(ptr_changeImg,2,0,1,4,Qt::AlignCenter);
    ptr_gridlay->addWidget(ptr_imglab,0,2,2,2);
    ptr_gridlay->setSpacing(5);

    //添加头像点击悬浮菜单;
    QMenu *ptr_selfMenu = new QMenu;
    ptr_selfMenu->setLayout(ptr_gridlay);
    return ptr_selfMenu;
}

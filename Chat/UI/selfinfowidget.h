#ifndef SELFINFOWIDGET_H
#define SELFINFOWIDGET_H
#include <QPushButton>
#include <QMap>
#include <QMenu>
class SelfInfoWidget:public QPushButton
{
public:
    explicit SelfInfoWidget(const QMap<QString,QString>& pSelfInfo,double flexDiget);
    ~SelfInfoWidget();
    QMenu* infoWidget();  //个人信息显示函数;

private:
    /*
     * selfInfo(个人信息存储Map):
     * user 用户名;
     * id 账号;
     * img 头像
     * */
    QMap<QString,QString> selfInfo;
    double m_flexDiget;//缩放系数;
};

#endif // SELFINFOWIDGET_H

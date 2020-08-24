#ifndef PERINFOWIDGET_H
#define PERINFOWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
class PerInfoWidget:public QWidget
{
    Q_OBJECT
public:
    PerInfoWidget(const QPixmap& head,const QString& nick,const QString& remark,const QString& id,double flexDiget,QWidget *parent = nullptr);
    ~PerInfoWidget();
    QWidget* getPerWidget();
    //更新个人信息函数;
    void updataInfoWidget(const QPixmap& head,const QString& nick,const QString& id,const QString& remark);

private:
    QPixmap m_head; //头像;
    QString m_nick; //昵称;
    QString m_id;   //账号;
    QString m_remark;   //备注;

    QLabel *ptr_head; //头像标签;
    QLabel *ptr_nick; //昵称标签;
    QLabel *ptr_id; //账号标签;
    QLineEdit *ptr_remark; //备注标签;
    QWidget *ptr_perInfoWidget;
    double m_flexDiget;    //桌面缩放系数;

public:
    //获取头像;
    QPixmap getHeadimg()const{
        return m_head;
    }
    //获取昵称;
    QString getNick()const{
        return m_nick;
    }
    //获取账号;
    QString getId()const{
        return m_id;
    }
signals:
    void infoWidSendBtn_onClicked();
};

#endif // PERINFOWIDGET_H

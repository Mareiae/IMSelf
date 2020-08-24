#ifndef FRIEND_H
#define FRIEND_H
#include <QWidget>
#include <QPixmap>
#include <QLabel>
class FriendInfoWidget
{
public:
    FriendInfoWidget(const QPixmap& heading,const QString& nickName,const QString& id,const QString& remark,double flexDiget);
    ~FriendInfoWidget();
    QWidget* getWidget();   //获取个人信息标签;
private:
    QPixmap ptr_headimg;   //头像
    QString m_nickName; //昵称
    QString m_id;   //账号id
    QString m_remark;   //备注;

    QWidget *ptr_friendWid;
    QLabel *ptr_remarkLabel;
    double m_flexDiget; //缩放系数;
public:
    //更新备注信息;
    void updateRemarkName(const QString& remarkName){
        m_remark = remarkName;
        ptr_remarkLabel->setFont(m_remark);
    }
    //获取头像;
    QPixmap getHeadimg()const{
        return ptr_headimg;
    }
    //获取昵称;
    QString getNickName()const{
        return m_nickName;
    }
    //获取账号id
    QString getId(){
        return m_id;
    }
    //获取昵称备注;
    QString getRemarkName(){
        return m_remark;
    }
};

#endif // FRIEND_H

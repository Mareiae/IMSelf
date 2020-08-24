#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMap>
#include <QVector>
#include <QStackedWidget>
#include <QListWidget>
#include <QScreen>
class MainForm : public QWidget
{
    Q_OBJECT
public:
    MainForm(const QMap<QString,QString>& pSelfInfo,QWidget *parent = nullptr);
    ~MainForm();
    QLayout* paintNavBar(); //设置左侧导航栏;
    QLayout* paintFriListForm();    //绘制好友列表窗体;
    QLayout* paintChatForm();   //绘制聊天窗体;
    void setFormStreth(); //计算窗口缩放比例;


private:
    QMap<QString,QString> selfInfoMap;  //存储个人信息;
    QLineEdit *ptr_searchEdit;  //搜索部件;
    QStackedWidget *ptr_listStackWidget;   //添加栈部件;
    QListWidget *ptr_listWidget[3]; //聊天列表，好友列表，搜索列表;
    QStackedWidget *ptr_chatStackWidget; //聊天面板，个人信息面板栈;
    QVBoxLayout *ptr_chatlay[3];
    std::pair<double,double> flexDiget;    //桌面缩放系数;
    double aveFlexDiget;    //平均缩放值;

protected:
   void mousePressEvent(QMouseEvent *event);    //实现鼠标拖动窗口;
   bool eventFilter(QObject * watched,QEvent *event);
   virtual void friendListSelectedItem(){}

   //获取缩放系数;
   double getFlexDiget()const{
       return aveFlexDiget;
   }
   //获取好友列表;
   QListWidget* getFriendListWidget(){
       return ptr_listWidget[1];
   }
   //获取聊天记录;
   QListWidget* getChatRecordWidget(){
       return ptr_listWidget[0];
   }
   //获取搜索结果列表;
   QListWidget* getSearchListWidget(){
       return ptr_listWidget[2];
   }
   //获取个人信息栈面板;
   QStackedWidget* getPerInfoStack(){
       return ptr_chatStackWidget;
   }
   //获取个人信息组件布局;
   QLayout* getCardLayout(){
       return ptr_chatlay[2];
   }
   //获取聊天信息组件布局;
   QLayout* getMessLayout(){
       return ptr_chatlay[1];
   }
   //获取个人信息;
   QMap<QString,QString> getSelfInfoMap()const{
       return selfInfoMap;
   }
};

#endif // MAINFORM_H

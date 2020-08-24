#include "mainform.h"
#include <windows.h>
#include <QLineEdit>
#include <QMouseEvent>
#include <QScrollBar>
#include <QGuiApplication>
#include "selfinfowidget.h"
#include "perinfowidget.h"
#include <QDebug>
MainForm::MainForm(const QMap<QString,QString>& pSelfInfo,QWidget *parent)
    :QWidget(parent),selfInfoMap(pSelfInfo)
{
    /*
     * 设置窗口大小
     * 去除窗口顶部默认标题栏，例如最大化，最小化按钮等
     * 设置窗口背景色
     * */
    setFormStreth();
    //设置窗口大小
    setMinimumSize(QSize(int(710*flexDiget.first),int(500*flexDiget.second)));
    //去除默认窗口导航栏按钮
    setWindowFlag(Qt::FramelessWindowHint);
    QHBoxLayout *ptr_mainlayout = new QHBoxLayout(this);
    ptr_mainlayout ->addLayout(paintNavBar());
    ptr_mainlayout ->addLayout(paintFriListForm());
    ptr_mainlayout->addLayout(paintChatForm());
    //设置主布局外边距,内边距为0
    ptr_mainlayout->setMargin(0);
    ptr_mainlayout->setSpacing(0);
    setLayout(ptr_mainlayout);
}
MainForm::~MainForm()
{
}
void MainForm::setFormStreth()
{
    //计算桌面缩放长，宽比例;
    QScreen *ptr_screen=QGuiApplication::primaryScreen ();
    int widthScreen = ptr_screen->availableSize().width();
    int heightScreen = ptr_screen->availableSize().height();
    flexDiget = std::make_pair<double,double>(static_cast<double>(widthScreen)/1366,static_cast<double>(heightScreen)/763);
    aveFlexDiget = (flexDiget.first+flexDiget.second)/2;
}
void MainForm::mousePressEvent(QMouseEvent *event)
{
    /*
     * 鼠标拖动窗口实现函数;
     * */
#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
           SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
       event->ignore();
#else
#endif
}
bool MainForm::eventFilter(QObject* watched,QEvent* event)
{
    if(watched == ptr_searchEdit)
    {
        if(QEvent::FocusIn == event->type()){
            ptr_searchEdit->setStyleSheet("QLineEdit{background-color:white;border-color:#cfcfcf;border-radius:3px;}");
            ptr_listStackWidget->setCurrentIndex(2);
        }else if(QEvent::FocusOut == event->type()){
            ptr_searchEdit->setStyleSheet("QLineEdit{border-style:none;background-color:rgba(190,190,190,0.5);border-radius:3px;}");
        }
    }
    return false;
}
QLayout* MainForm::paintNavBar()
{
    //添加左侧导航栏背景部件;
    QWidget *ptr_navWidget = new QWidget;
    ptr_navWidget->setStyleSheet("QWidget{background-color:#111922}");
    //固定导航栏背景部件位置，禁止放大缩放;
    QSizePolicy navSizePolicy = ptr_navWidget->sizePolicy();
    navSizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    ptr_navWidget->setSizePolicy(navSizePolicy);
    //为背景部件添加布局;
    QVBoxLayout *ptr_navWidlay = new QVBoxLayout;
    ptr_navWidget->setLayout(ptr_navWidlay);

    //添加头像部件;
    SelfInfoWidget *head = new SelfInfoWidget(selfInfoMap,getFlexDiget());
    ptr_navWidlay->addWidget(head);


    //添加聊天，通讯录，设置部件;
    QPushButton **ptr_navBtn = new QPushButton*[3];
    QString navName[3] = {"聊天","通讯录","设置"};
    QString navIconName[3] = {"chatFocus","book","set"};
    for(int i = 0;i < 3;++i){
        ptr_navBtn[i] = new QPushButton;
        ptr_navBtn[i]->setIcon(QIcon(":/Icons/"+navIconName[i]+".svg"));
        ptr_navBtn[i]->setIconSize(QSize(int(34*aveFlexDiget),int(34*aveFlexDiget)));
        ptr_navBtn[i]->setFlat(true);   //设置按钮背景透明;
        ptr_navBtn[i]->setToolTip(QString(navName[i]));
        ptr_navBtn[i]->setStyleSheet("QPushButton{border:0px}");
        ptr_navBtn[i]->setCursor(QCursor(Qt::PointingHandCursor));  //更改鼠标样式;
        if(i == 2){
            ptr_navWidlay->addStretch();
        }
        connect(ptr_navBtn[i],&QPushButton::clicked,this,[=]()
        {
            QPushButton *pNavBtn = qobject_cast<QPushButton *>(sender());
            QWidget *pWindow = this->window();
            if (pWindow->isTopLevel()){
                if(pNavBtn == ptr_navBtn[0]){
                    ptr_navBtn[0]->setIcon(QIcon(":/Icons/chatFocus.svg"));
                    ptr_navBtn[1]->setIcon(QIcon(":/Icons/book.svg"));
                    ptr_navBtn[2]->setIcon(QIcon(":/Icons/set.svg"));
                    ptr_listStackWidget->setCurrentIndex(0);
                }else if(pNavBtn == ptr_navBtn[1]){
                    ptr_navBtn[1]->setIcon(QIcon(":/Icons/bookFocus.svg"));
                    ptr_navBtn[0]->setIcon(QIcon(":/Icons/chat.svg"));
                    ptr_navBtn[2]->setIcon(QIcon(":/Icons/set.svg"));
                    ptr_listStackWidget->setCurrentIndex(1);
                }else if(pNavBtn == ptr_navBtn[2]){
                    ptr_navBtn[2]->setIcon(QIcon(":/Icons/setFocus.svg"));
                }
            }
        });
        ptr_navWidlay->addWidget(ptr_navBtn[i]);
    }

    //导航栏中布局;
    QVBoxLayout *ptr_navlayout = new QVBoxLayout;
    ptr_navlayout->addWidget(ptr_navWidget);
    return ptr_navlayout;
}
QLayout* MainForm::paintFriListForm()
{
    //添加搜索框;
    ptr_searchEdit = new QLineEdit;
    ptr_searchEdit->setPlaceholderText("搜索");
    QAction* searAct = new QAction;
    searAct->setIcon(QIcon(":/Icons/search.svg"));
    ptr_searchEdit->addAction(searAct,QLineEdit::LeadingPosition);
    ptr_searchEdit->setFixedSize(QSize(int(180*aveFlexDiget),int(30*aveFlexDiget)));
    ptr_searchEdit->installEventFilter(this);
    ptr_searchEdit->setFont(QFont("Consolas",9));
    ptr_searchEdit->setStyleSheet("QLineEdit{border-style:none;background-color:rgba(190,190,190,0.5);border-radius:3px;}");


    //添加好友按钮：
    QPushButton *ptr_addFriend = new QPushButton;
    ptr_addFriend->setIcon(QIcon(":/Icons/addFriend.svg"));
    ptr_addFriend->setFixedSize(QSize(int(30*aveFlexDiget),int(30*aveFlexDiget)));
    ptr_addFriend->setToolTip("添加好友");
    ptr_addFriend->setStyleSheet("QPushButton{border-style:none;background-color:rgba(190,190,190,0.5);border-radius:3px;}"
                                "QPushButton:hover{background-color:rgba(122,128,144,0.5)}");
    //为搜索框，添加好友按钮添加水平布局;
    QHBoxLayout *ptr_searchlay = new QHBoxLayout;
    ptr_searchlay->addWidget(ptr_searchEdit,4);
    ptr_searchlay->addWidget(ptr_addFriend,1);
    ptr_searchlay->setSpacing(int(10*aveFlexDiget));
    ptr_searchlay->setContentsMargins(int(10*aveFlexDiget),int(20*aveFlexDiget),int(10*aveFlexDiget),int(10*aveFlexDiget));

    //添加好友列表，聊天列表，搜索列表;
    ptr_listStackWidget = new QStackedWidget;
    ptr_listStackWidget->setFixedWidth(int(230*aveFlexDiget));
    for(int i = 0;i < 3;++i){
        ptr_listWidget[i] = new QListWidget;
        ptr_listWidget[i]->setStyleSheet("QListWidget{background:#f0f0f0;border:0px}"
                                "QListWidget::item:hover{background:#E8E8E8}"
                                "QListWidget::item:selected{background:#D3D3D3}");
        ptr_listWidget[i]->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {border: none;"
                                                     "background: #dfdfdf;"
                                                     "width: 12px;}"
                                                     "QScrollBar::handle:vertical {border: none;"
                                                     "border-radius: 5px;"
                                                     "background: #cfcfcf;}"
                                                     "QScrollBar::add-page:vertical {border: none;"
                                                     "background-color: #dfdfdf;}"
                                                     "QScrollBar::sub-page:vertical {border: none;"
                                                     "background-color: #dfdfdf;}");
        ptr_listWidget[i]->setFocusPolicy(Qt::NoFocus);
        ptr_listStackWidget->addWidget(ptr_listWidget[i]);
    }
    ptr_listStackWidget->setCurrentIndex(0);    //默认显示聊天列表;
    connect(ptr_listWidget[1],&QListWidget::itemClicked,this,&MainForm::friendListSelectedItem);

    QVBoxLayout *ptr_listlayout = new QVBoxLayout;
    ptr_listlayout->addLayout(ptr_searchlay);
    ptr_listlayout->addWidget(ptr_listStackWidget);
    return ptr_listlayout;
}
QLayout* MainForm::paintChatForm()
{
    QHBoxLayout *ptr_barlayout = new QHBoxLayout;
    //最小化，最大化，关闭按钮申明;
    QPushButton **barBtn = new QPushButton*[3];
    QString barTipName[3] =  {"最小化","最大化","关闭"};
    QString barIconNmae[3] = {"min.svg","max.svg","close.svg"};
    ptr_barlayout->addStretch();
    //重新添加最小化，最大化，关闭按钮;
    for(int i = 0;i < 3;++i){
        barBtn[i] = new QPushButton;
        barBtn[i]->setIcon(QIcon(":/Icons/"+barIconNmae[i]));
        barBtn[i]->setToolTip(QString(barTipName[i]));
        barBtn[i]->setFixedSize(QSize(int(25*aveFlexDiget),int(25*aveFlexDiget)));
        //barBtn[i]->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        connect(barBtn[i],&QPushButton::clicked,this,[=](){
            //实现最小化，最大化，关闭按钮功能;
            QPushButton *pbarBtn = qobject_cast<QPushButton *>(sender());
            QWidget *pWindow = this->window();
            if (pWindow->isTopLevel()){
                if(pbarBtn == barBtn[0]){
                    pWindow->showMinimized();
                }else if(pbarBtn == barBtn[1]){
                    pWindow->isMaximized()?pWindow->showNormal() : pWindow->showMaximized();
                    pWindow->isMaximized()?barBtn[1]->setIcon(QIcon(":/Icons/minStreth.svg"))
                        :barBtn[1]->setIcon(QIcon(":/Icons/max.svg"));
                }else if(pbarBtn == barBtn[2]){
                    pWindow->close();
                }
            }
        });
        //设置鼠标滑过样式;
        if(i == 2){
            barBtn[i]->setStyleSheet("QPushButton{border:0px}"
                                     "QPushButton:hover{background-color:red}");
        }else{
            barBtn[i]->setStyleSheet("QPushButton{border:0px}"
                                     "QPushButton:hover{background-color:#BEBEBE}");
        }
        ptr_barlayout->addWidget(barBtn[i]);
    }
    ptr_barlayout->setSpacing(int(5*aveFlexDiget));
    ptr_barlayout->setMargin(0);
    QWidget *ptr_barWid = new QWidget;
    ptr_barWid->setStyleSheet("QWidget{background-color:#fafafa}");
    ptr_barWid->setLayout(ptr_barlayout);

    //添加默认显示窗口，聊天窗口，个人信息显示窗口组件;
    ptr_chatStackWidget = new QStackedWidget;
    for(int i = 0;i < 3;++i){
        QWidget *ptr_chatWidget = new QWidget;
        ptr_chatWidget->setStyleSheet("QWidget{background-color:#fafafa;}");
        ptr_chatWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        ptr_chatlay[i] = new QVBoxLayout;
        ptr_chatWidget->setLayout(ptr_chatlay[i]);
        ptr_chatStackWidget->addWidget(ptr_chatWidget);
    }

    QVBoxLayout *ptr_chatlayout = new QVBoxLayout;
    ptr_chatlayout->addWidget(ptr_barWid);
    ptr_chatlayout->addWidget(ptr_chatStackWidget);
    return ptr_chatlayout;
}













#ifndef SERVER_H
#define SERVER_H
#include <QWidget>
#include <winsock2.h>
class Server:public QWidget
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();
    void initServer();  //初始化服务;
    void recvMessage(); //接收消息;
    bool closeSocket(); //关闭套接字;
    void closeThread(bool flag){isClosed = flag;}
private:
    SOCKET m_socket; //套接字;
    struct sockaddr_in servAddr;  //服务端地址结构;
    char buffRecv[1024]; //接收数据缓存数组;
    bool isClosed = false;  //是否结束线程;
signals:
    void recvNewMessage(const char*);//若线程接收到新的数据则促发该信号;
};
#endif // SERVER_H

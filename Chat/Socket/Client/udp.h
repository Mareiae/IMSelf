#ifndef UDP_H
#define UDP_H
#include <winsock2.h>
#include <iostream>
#include <ws2tcpip.h>
#define MAX_LINE 1024
namespace UDP{
//Udp数据包;
enum TYPE
{
    LOGIN, //登录状态;
    CHAR,   //新消息数据;
    FILE,   //文件类型;
    IPREQUEST, //请求朋友ip地址;
    CONNECT,   //连接探测请求;
    NAT //nat穿透;
};
#pragma pack(4)
struct MSG
{
    TYPE type;//包种类;
    char send_char[MAX_LINE];   //数据;
    char recv_user[20]; //接收用户;
    char send_user[20]; //发送用户;
    sockaddr_in addr;
};
#pragma pack()
}

class Udp
{
public:
    Udp();
    ~Udp();
    bool initServer(const char *ip,u_short port); //初始化服务;
    bool recvMessage(void *buff,int size); //接受消息;
    bool sendMessage(void *buff,int size);//发送消息;
    bool closeSocket(); //关闭socket;

private:
    SOCKET m_socket;
    struct sockaddr_in servAddr;  //服务端地址结构;
};

#endif // UDP_H

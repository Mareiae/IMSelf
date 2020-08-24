#ifndef TCP_H
#define TCP_H
#include <winsock2.h>
#include <iostream>
namespace TCP
{
//数据包;
#pragma pack(4)
    struct MSG{
        char user_type;   // a-login    f-friends
        //self
        char user_email[20];
        char user_pass[20];
        char user_name[20];
        //friends
        char nick_name[20];
        char friend_email[20];
        char friend_name[20];
        //others
        char login_result;
        uint32_t size;
    };
#pragma pack()
}
class Tcp
{
public:
    Tcp();
    ~Tcp();
    bool initServer();
    bool sendMessage(void* buff,int size);
    bool recvMessage(void* buff,int size);
    bool closeSocket();

private:
    SOCKET m_socket;
};

#endif // TCP_H

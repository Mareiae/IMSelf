#include "udp.h"

Udp::Udp()
{

}
Udp::~Udp()
{
    if(!closeSocket()){
        closesocket(m_socket);
        WSACleanup();
    }
}
bool Udp::initServer(const char* ip,u_short port)
{
    WSADATA wsd;
    if(WSAStartup(MAKEWORD(2,2),&wsd) != 0)
    {
        return false;
    }
    //创建socket;
    m_socket = socket(AF_INET,SOCK_DGRAM,0);
    if(m_socket == INVALID_SOCKET)
        return false;

    memset(&servAddr,0,sizeof (servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.S_un.S_addr = inet_addr(ip);
    servAddr.sin_port = htons(port);
#if 1
    struct timeval tv_out;
    tv_out.tv_sec = 10;
    tv_out.tv_usec = 0;
    //设置socket延迟;
    setsockopt(m_socket,SOL_SOCKET,SO_RCVTIMEO,reinterpret_cast<char*>(&tv_out),sizeof (tv_out));
#endif
    return true;
}
bool Udp::recvMessage(void *buff, int size)
{
    socklen_t len = sizeof (servAddr);
    if (recvfrom(m_socket,reinterpret_cast<char *>(buff), size, 0,reinterpret_cast<struct sockaddr *>(&servAddr),&len) == SOCKET_ERROR)
    {
        //若接收发生错误则关闭当前socket;
        closeSocket();
        return false;
    }
    return true;
}
bool Udp::sendMessage(void *buff, int size)
{
    socklen_t len = sizeof (servAddr);
    if(sendto(m_socket,reinterpret_cast<char *>(buff),size+1,0,reinterpret_cast<struct sockaddr *>(&servAddr),len) == SOCKET_ERROR){
        //若发送发生错误则关闭当前socket;
        closeSocket();
        return false;
    }
    return true;
}
bool Udp::closeSocket()
{
    if(closesocket(m_socket) != 0)
        return false;
    WSACleanup();
    return true;
}

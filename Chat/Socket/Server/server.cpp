#include "server.h"
#include <QDebug>
Server::Server(QWidget *parent)
    :QWidget(parent)
{
    initServer();
}
Server::~Server()
{
    if(!closeSocket()){
        closesocket(m_socket);
        WSACleanup();
    }
}
void Server::initServer()
{
    WSADATA wsd;
    if(WSAStartup(MAKEWORD(2,2),&wsd) != 0){
        return;
    }
    //创建socket;
    m_socket = socket(AF_INET,SOCK_DGRAM,0);
    if(m_socket == INVALID_SOCKET)
        return;

    memset(&servAddr,0,sizeof (servAddr));
    servAddr.sin_family = AF_INET;  //协议类型位ipv4;
    servAddr.sin_addr.S_un.S_addr = htonl(ADDR_ANY); //接收任意ip;
    servAddr.sin_port = htons(5501); //开放端口5501;

    //绑定socket;
    if(bind(m_socket,reinterpret_cast<sockaddr*>(&servAddr),sizeof(servAddr)) == SOCKET_ERROR)
    {
        closesocket(m_socket);
        WSACleanup();
    }
#if 1
    struct timeval tv_out;
    tv_out.tv_sec = 10;
    tv_out.tv_usec = 0;
    //设置socket延迟;
    setsockopt(m_socket,SOL_SOCKET,SO_RCVTIMEO,reinterpret_cast<char*>(&tv_out),sizeof (tv_out));
#endif
}
bool Server::closeSocket()
{
    if(closesocket(m_socket) != 0)
        return false;
    WSACleanup();
    return true;
}
void Server::recvMessage()
{
   int len = sizeof (servAddr);
   int last;
   while(true)
   {
       if(isClosed == true){
           closeSocket();
           break;
       }
       memset(buffRecv,0,sizeof (buffRecv));
       last = recvfrom(m_socket,buffRecv,sizeof (buffRecv),0,reinterpret_cast<sockaddr*>(&servAddr),&len);
       if(last > 0){
           //buffRecv[last] = '\0';
           emit recvNewMessage(buffRecv);
           Sleep(1000);
       }
   }
}

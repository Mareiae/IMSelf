#include "tcp.h"

Tcp::Tcp()
{

}
Tcp::~Tcp()
{
    if(!closeSocket()){
        closesocket(m_socket);
        WSACleanup();
    }
}
bool Tcp::initServer()
{
    WSADATA wsaData;
    struct sockaddr_in serverAddr;  //服务端地址结构;

    if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0){
        return false;
    }
    //创建socket;
    if((m_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == static_cast<SOCKET>(SOCKET_ERROR)){
        return false;
    }

    memset(&serverAddr,0,sizeof (serverAddr));
    serverAddr.sin_family = AF_INET;    //设置类型为ipv4;
    serverAddr.sin_port = htons(4500);  //设置端口;
    serverAddr.sin_addr.S_un.S_addr = inet_addr("47.106.14.185");   //添加服务器地址;

    //创建连接;
    if((::connect(m_socket,reinterpret_cast<SOCKADDR *>(&serverAddr),sizeof (serverAddr))) == SOCKET_ERROR)
    {
        closesocket(m_socket);
        WSACleanup();
        return false;
    }
    return true;
}
bool Tcp::sendMessage(void *buff, int size)
{
    int index = 0,ret;
    while (size != 0)
    {
        if (size > 4096){
            //若发送的数据长度大于4096时，则只发送4096字节的数据;
            ret = send(m_socket,reinterpret_cast<char *>(buff)+index,4096,0);
        }else{
            ret = send(m_socket,reinterpret_cast<char *>(buff)+index,size,0);
        }
        //发生socket错误，或则对端关闭连接时；需关闭当前socket,并退出;
        if (ret == SOCKET_ERROR || ret == 0){
            closeSocket();
            break;
        }
        //获取剩余未发送的数据长度;
        size -= ret;
        index += ret;
    }
    return size == 0 ? true : false;
}
bool Tcp::recvMessage(void *buff, int size)
{
    int ret,index = 0;
    while (size != 0)
    {
        ret = recv(m_socket,reinterpret_cast<char *>(buff) + index,size,0);
        if(ret == SOCKET_ERROR || ret == 0){
            //发生socket错误，或则对端关闭连接时；需关闭当前socket,并退出;
            closeSocket();
            break;
        }
        //获取剩余未接受的数据长度;
        size -= ret;
        index += ret;
    }
    return size == 0 ? true :false;
}
bool Tcp::closeSocket()
{
    if(closesocket(m_socket) != 0)
        return false;
    WSACleanup();
    return true;
}


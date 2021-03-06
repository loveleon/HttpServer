#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

#include "object.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

typedef struct sockaddr sockaddr;

class Socket: public Object
{
    public:
        Socket(Object *parent = NULL);
        Socket(int domain, int type, int protocol = 0,
               Object *parent = NULL);
        virtual ~Socket();

        void initSocket(int domain, int type, int protocol = 0);
        int bind();
        int listen(int backlog);
        int accept(Socket &acc_sock);
        int connectToHost();
        int closeSocket();

        void setSocketAddress(short int family, const char *hostname,
                              unsigned short int port);
        void setSocketAddress(short int family, unsigned long int address,
                              unsigned short int port);

        inline int sendData(const char *data, int data_size)const;
        inline int receiveData(char *buffer, int buff_size)const;

        inline short int getLocalPort();
        inline short int getPeerPort();

        int getPeerAddress(sockaddr *addr)const;
        int getLocalAddress(sockaddr *addr)const;

    private:
        Socket(const Socket &socket);
        Socket& operator=(const Socket &socket);
        void _assign(const Socket &socket);

        int local_sockfd;
        struct sockaddr_in address;
};

int Socket::sendData(const char *data, int data_size)const
{
    return send(local_sockfd, data, data_size, 0);
}

int Socket::receiveData(char *buffer, int buff_size)const
{
    return recv(local_sockfd, buffer, buff_size, MSG_DONTWAIT);
}

short int Socket::getLocalPort()
{
    socklen_t addr_len = sizeof(address);
    int res = getsockname(local_sockfd, (sockaddr*)&address, &addr_len);
    if(res == 0)
        return ntohs(address.sin_port);
    return -1;
}

short int Socket::getPeerPort()
{
    socklen_t addr_len = sizeof(address);
    int res = getpeername(local_sockfd, (sockaddr*)&address, &addr_len);
    if(res == 0)
        return ntohs(address.sin_port);
    return -1;
}


#endif // SOCKET_H_INCLUDED

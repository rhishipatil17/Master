#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

#define MAX_LISTEN_COUNT 20
#define REC_BUFFER_SIZE 30720

namespace Tcp
{
    typedef int SocketHandle;
    typedef int Port;
    typedef std::string IPAddr;

    enum ReturnCode
    {
        Failure = -1,
        Success
    };

    enum ServerState
    {
        NotStarted,
        Initialized,
        Listening,
        Connected,
        Paused
    };

    class TcpServer
    {
        public:
            ~TcpServer();
            static TcpServer& getInstance();
            ReturnCode initServer(const IPAddr &addr,const Port &port);
            ReturnCode startServer();
            ReturnCode acceptConnection();
            int readData(char (&Buffer)[REC_BUFFER_SIZE]);
            int sendData(const char *const Data, size_t DataSize);
            void closeServer();
            void closeClient();

        private:
            TcpServer();
            TcpServer(const TcpServer &obj) = delete;
            TcpServer& operator=(const TcpServer &obj) = delete;
            void clearServerAddress();

            SocketHandle mSocket;
            SocketHandle mClientSocket;
            struct sockaddr_in mServerAddress;
            unsigned int mServerAddressLength;
            ServerState mState;

    };
}

#endif
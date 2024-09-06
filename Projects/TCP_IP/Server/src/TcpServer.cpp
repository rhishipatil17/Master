#include "TcpServer.h"

using namespace Tcp;

TcpServer& TcpServer::getInstance()
{
    static TcpServer server;
    return server;
}

TcpServer::TcpServer()
{
    mSocket = 0;
    clearServerAddress();
    mServerAddressLength = sizeof(mServerAddress);
    mState = NotStarted;
}
TcpServer::~TcpServer()
{
    closeClient();
    closeServer();
    clearServerAddress();
    mState = NotStarted;
}

ReturnCode TcpServer::initServer(const IPAddr &addr,const Port &port)
{
    ReturnCode retCode = Failure;
    do
    {
        if(mClientSocket)
            closeClient();
        if(mSocket)
            closeServer();

        mSocket = socket(AF_INET, SOCK_STREAM, 0);
        if(mSocket < 0)
        {
            mState = NotStarted;
            mSocket = 0;
            break;
        }

        mServerAddress.sin_family = AF_INET;
        mServerAddress.sin_port = htons(port);
        mServerAddress.sin_addr.s_addr = inet_addr(addr.c_str());
        int ret = bind(mSocket,(struct sockaddr*)&(mServerAddress), mServerAddressLength);
        if(ret < 0)
        {
            mState = NotStarted;
            mSocket = 0;
            clearServerAddress();
            break;
        }

        mState = Initialized;
        retCode = Success;
    }while(0);
    return retCode;
}

ReturnCode TcpServer::startServer()
{
    ReturnCode retCode = Failure;
    do
    {
        if(mState != Initialized)
        {
            break;
        }

        int ret = listen(mSocket, MAX_LISTEN_COUNT);
        if(ret < 0)
        {
            break;
        }

        mState = Listening;
        retCode = Success;
    } while(0);
    return retCode;
}

ReturnCode TcpServer::acceptConnection()
{
    if(mState != Listening)
        return Failure;

    SocketHandle soc;
    do
    {
        soc = accept(mSocket, (struct sockaddr*)&(mServerAddress), &mServerAddressLength);

    } while(soc < 0);
    mState = Connected;
    mClientSocket = soc;

    return Success;
}

int TcpServer::readData(char (&Buffer)[REC_BUFFER_SIZE])
{
    if(mState != Connected)
        return Failure;
    else
        return read(mClientSocket, Buffer, REC_BUFFER_SIZE);
}

int TcpServer::sendData(const char *const Data, size_t DataSize)
{
    if(mState != Connected)
        return Failure;
    else
        return write(mClientSocket, Data, DataSize);
}

void TcpServer::closeServer()
{
    close(mSocket);
    mSocket = 0;
    mState = NotStarted;
}

void TcpServer::closeClient()
{
    close(mClientSocket);
    mClientSocket = 0;
    //TODO: add correct server state
}

void TcpServer::clearServerAddress()
{
    mServerAddress.sin_family = NULL;
    mServerAddress.sin_port = NULL;
    mServerAddress.sin_addr.s_addr = NULL;
}
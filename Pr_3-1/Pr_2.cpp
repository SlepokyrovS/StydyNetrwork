#include iostream
#include cstdlib
#include cstring
#include unistd.h
#include netinetin.h
#include arpainet.h

using namespace std;

void errHandler (const char  why, const int exitCode = 1)
{
    cerr  why  endl;
}

int main ()
{
    sockaddr_in  selfAddr = new (sockaddr_in);
    selfAddr-sin_family = AF_INET;
    selfAddr-sin_port = 0;
    selfAddr-sin_addr.s_addr = 0;

    sockaddr_in  remoteAddr = new (sockaddr_in);
    remoteAddr-sin_family = AF_INET;
    remoteAddr-sin_port = htons(13);
    remoteAddr-sin_addr.s_addr = inet_addr(82.179.90.12);

    char  buf = new char[256];
    strcpy(buf, Sending messagen);
    int msgLen = strlen(buf);

    int mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mySocket == -1)
    {
        errHandler(Error open socket, 11);
    }

    int rc = bind(mySocket, (const sockaddr) selfAddr, sizeof (sockaddr_in));
    if (rc == -1)
    {
        close(mySocket);
        errHandler(Error connect socket with local address, 12);
    }

    rc = connect(mySocket, (const sockaddr) remoteAddr, sizeof (sockaddr_in));
    if (rc == -1)
    {
        close(mySocket);
        errHandler(Error connect socket with remote server, 13);
    }

    rc = send(mySocket, buf, msgLen, 0);
    if (rc == -1)
    {
        close(mySocket);
        errHandler(Error send message, 14);
    }
    cout  We send   buf  endl;

    rc = recv(mySocket, buf, 256, 0);
    if (rc == -1)
    {
        close(mySocket);
        errHandler(Error recevie answer, 15);
    }
    cout  buf  endl;

    close(mySocket);

    delete selfAddr;
    delete remoteAddr;

    return 0;
}
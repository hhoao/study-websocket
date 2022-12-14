#include "easywsclient.hpp"
#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif
#include <cassert>
#include <cstdio>
#include <string>

using easywsclient::WebSocket;
static WebSocket::pointer ws = NULL;

void handle_message(const std::string & message)
{
    printf(">>> %s\n", message.c_str());
    if (message == "world") { ws->close(); }
}

int main()
{
#ifdef _WIN32
    INT rc;
    WSADATA wsaData;

    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc) {
        printf("WSAStartup Failed.\n");
        return 1;
    }
#endif
    ws = WebSocket::from_url("ws://localhost:8888");
    assert(ws); ////判断ws对象是否为空null ,当没有连接上的时候这个对象是NULL
    ws->send("goodbye");
    ws->send("hello");
    while (ws->getReadyState() != WebSocket::CLOSED) {
      ws->poll();//这个函数一定要在循环里调用，发送和接收都是基于这个函数进行异步处理的
      ws->dispatch(handle_message);
    }
    delete ws;
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}

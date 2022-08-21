#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

//开启服务器端口
#define SERV_PORT 8888
#include "tcp_epoll.h"
int main() {
    start_server(SERV_PORT);
    return 0;
}

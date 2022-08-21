//
// Created by hhoa on 22-8-18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include "./tcp_epoll.h"
#include "./tcp_session.h"
#include "./tcp_ws.h"


void start_server(int port) {
    printf("启动服务 port: %d\n", port);
    //初始化session管理
    init_session_manager();
    struct sockaddr_in serv_addr;
    socklen_t serv_len = sizeof(serv_addr);
    //创建套接字
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    //初始化socket_in
    memset(&serv_addr, 0, serv_len);
    serv_addr.sin_family = AF_INET;                    //地址族
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);    //监听本机所有的IP
    serv_addr.sin_port = htons(port);                //设置端口

    //绑定端口和IP
    bind(lfd, (struct sockaddr *) &serv_addr, serv_len);

    //设置同时监听的最大个数
    listen(lfd, 128);
    printf("start accept ...\n");

    struct sockaddr_in client_addr;
    socklen_t cli_len = sizeof(client_addr);

    //创建epoll树根节点
    int epfd = epoll_create(2000);
    //初始化epoll树
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = lfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
    struct epoll_event all[2000];
    while (1) {
        clear_offline_session();
        //使用epoll通知内核fd文件IO检测
        int ret = epoll_wait(epfd, all, sizeof(all) / sizeof(all[0]), -1);
        int i;
        for (i = 0; i < ret; ++i) {
            //遍历all数组中的前ret个元素
            int fd = all[i].data.fd;
            //判断是否有新连接
            if (fd == lfd) {
                //有新连接
                int cfd = accept(lfd, (struct sockaddr *) &client_addr, &cli_len);
                if (cfd == -1) {
                    perror("accept error");
                    exit(1);
                }
                //设置cfd为非阻塞模式
                int flag = fcntl(cfd, F_GETFL);
                flag |= O_NONBLOCK;
                fcntl(cfd, F_SETFL, flag);
                //将新得到的cfd上epoll树
                ev.events = EPOLLIN | EPOLLET; //边沿模式
                ev.data.fd = cfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
                char ip[64] = {0};
                save_session(cfd, inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ip, sizeof(ip)),
                             ntohs(client_addr.sin_port));
            } else {
                struct session *session = get_session(fd);
                //处理已连接的客户端发过来的数据
                if (!(all[i].events & EPOLLIN)) {
                    //如果没有读的操作那么跳过
                    continue;
                }
                //读数据
                char buf[1024] = {0};
                int len;
                while ((len = recv(fd, buf, sizeof(buf), 0)) > 0) {
//                while(1){
//                    for (i = 0; i < 2 || (i < 255 && buf[i - 2] != '\r' && buf[i - 1] != '\n'); ++i) {
//                        if (recv(fd, buf, sizeof(buf), 0) == 0) {
//                            return;
//                        }
//                    }
                    printf("接受的数据为:\n %s\n", buf);
                    if (buf[0] == '\r' && buf[1] == '\n') { break; }
                    if (session->is_shake_hand == 0) {
                        process_ws_shake_hand(session->c_sock, buf);
                        session->is_shake_hand = 1;
                    } else {
                        //解析数据
                        char msg[8196] = {0};
                        ret = on_ws_recv_data(session, (unsigned char *) buf, len, (char *) &msg);
                        if (ret) {
                            //解析成功后处理数据
                            ws_send_data(session, (unsigned char *) msg, strlen(msg));
                        }
                    }
                }
                if (len == -1) {
                    if (errno != EAGAIN) {
                        perror("recv error");
                        exit(1);
                    }
                } else if (len == 0) {
                    //客户端关闭
                    //下树
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                    if (ret == -1) {
                        perror("epoll_ctl - del error");
                        exit(1);
                    }
                    close_session(session);
                }
            }
        }
    }
    close(lfd);
    exit_session_manager();
}
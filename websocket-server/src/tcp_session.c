//
// Created by hhoa on 22-8-18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./tcp_session.h"

#define MAX_SESSION_NUM 6000
#define my_malloc malloc
#define my_free free

#define MAX_RECV_BUFFER 8096

struct {
    struct session* online_session;

    struct session* cache_mem;
    struct session* free_list;


    char recv_buffer[MAX_RECV_BUFFER];
    int readed; // 当前已经从socket里面读取的数据;

    int has_removed;
    int prot_mode; // 0 表示二进制协议，size + 数据的模式
    // 1,表示文本协议，以回车换行来分解收到的数据为一个包
}session_manager;

static struct session* cache_alloc() {
    struct session* s = NULL;
    if (session_manager.free_list != NULL) {
        s = session_manager.free_list;
        session_manager.free_list = s->next;
    }
    else { // 调用系统的函数 malloc
        s = my_malloc(sizeof(struct session));
    }
    memset(s, 0, sizeof(struct session));

    return s;
}

//释放一个会话
static void cache_free(struct session* s) {
    // 判断一下，是从cache分配出去的，还是从系统my_malloc分配出去的？
    if (s >= session_manager.cache_mem && s < session_manager.cache_mem + MAX_SESSION_NUM) {
        s->next = session_manager.free_list;
        session_manager.free_list = s;
    }
    else {
        my_free(s);
    }
}

/**初始化会话管理*/
void init_session_manager() {
    memset(&session_manager, 0, sizeof(session_manager));
    // 将6000个session一次分配出来。
    session_manager.cache_mem = (struct session*)my_malloc(MAX_SESSION_NUM * sizeof(struct session));
    memset(session_manager.cache_mem, 0, MAX_SESSION_NUM * sizeof(struct session));
    int i;
    for (i = 0; i < MAX_SESSION_NUM; i++) {
        session_manager.cache_mem[i].next = session_manager.free_list;
        session_manager.free_list = &session_manager.cache_mem[i];
    }
}

void exit_session_manager() {
    //退出所有会话
}

//保存一个会话
struct session* save_session(int c_sock, const char* ip, int port) {
    struct session* s = cache_alloc();
    s->c_sock = c_sock;
    s->c_port = port;
    s->removed = 0;
    int len = strlen(ip);
    if (len >= 32) {
        len = 31;
    }
    strncpy(s->c_ip, ip, len);
    s->c_ip[len] = 0;
    s->next = session_manager.online_session;
    session_manager.online_session = s;
    printf("client %s:%d connected...\n", s->c_ip, s->c_port);
    return s;
}

/**遍历各个会话并且调用函数*/
void foreach_online_session(int(*callback)(struct session* s, void* p), void*p) {
    if (callback == NULL) {
        return;
    }
    struct session* walk = session_manager.online_session;
    while (walk) {
        if (walk->removed == 1) {
            walk = walk->next;
            continue;
        }
        if (callback(walk, p)) {
            return;
        }
        walk = walk->next;
    }
}

struct session* get_session(int c_sock){
    struct session* walk = session_manager.online_session;
    while (walk) {
        if (walk->removed == 1) {
            walk = walk->next;
            continue;
        }
        if(walk->c_sock == c_sock){
            return walk;
        }
        walk = walk->next;
    }
    return NULL;
}

void close_session(struct session* s) {
    s->removed = 1;
    s->is_shake_hand = 0;
    session_manager.has_removed = 1;
    printf("client %s:%d exit\n", s->c_ip, s->c_port);
}

void clear_offline_session() {
    if (session_manager.has_removed == 0) {
        return;
    }
    struct session** walk = &session_manager.online_session;
    while (*walk) {
        struct session* s = (*walk);
        if (s->removed) {
            *walk = s->next;
            s->next = NULL;
            close(s->c_sock);
            s->c_sock = 0;
            // 释放session
            cache_free(s);
        }
        else {
            walk = &(*walk)->next;
        }
    }
    session_manager.has_removed = 0;
}

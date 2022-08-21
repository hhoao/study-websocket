//
// Created by hhoa on 22-8-18.
//

#ifndef EMBEDDED_FINAL_HOMEWORK_TCP_SESSION_H
#define EMBEDDED_FINAL_HOMEWORK_TCP_SESSION_H

struct session {
    char c_ip[32];
    int c_port;
    int c_sock;
    int removed;
    int is_shake_hand;
    struct session* next;
};

void init_session_manager();
void exit_session_manager();

/**
 * 有客服端进来，保存这个session
 * @param c_sock 句柄
 * @param ip 
 * @param port
 * @return session
 */
struct session* save_session(int c_sock, const char* ip, int port);

/**
 * 根据句柄获取会话
 * @param c_sock 句柄
 * @return 会话
 */
struct session* get_session(int c_sock);

/**
 * 关闭一个会话
 * @param s 会话
 */
void close_session(struct session* s);

/**
 * 遍历我们session集合里面的所有session
 * @param callback 回调函数
 * @param p
 */
void foreach_online_session(int(*callback)(struct session* s, void* p), void*p);

/**清理下线的会话*/
void clear_offline_session();
#endif //EMBEDDED_FINAL_HOMEWORK_TCP_SESSION_H

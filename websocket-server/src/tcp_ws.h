//
// Created by hhoa on 22-8-18.
//

#ifndef EMBEDDED_FINAL_HOMEWORK_TCP_WS_H
#define EMBEDDED_FINAL_HOMEWORK_TCP_WS_H

/**握手协议*/
void process_ws_shake_hand(int sock, char* http_str);

/**发送信息给客户端*/
void ws_send_data(struct session* s, unsigned char* pkg_data, unsigned int pkg_len);

/**解析包*/
int on_ws_recv_data(struct session* s, unsigned char*pkg_data, int pkg_len, char* msg);
#endif //EMBEDDED_FINAL_HOMEWORK_TCP_WS_H

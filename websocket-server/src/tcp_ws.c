//
// Created by hhoa on 22-8-18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <openssl/evp.h>
#include "./tcp_session.h"
#include "./tcp_ws.h"
#include "http-parser/http_parser.h"
#include "b64.h"

static char header_key[64];
static char client_ws_key[128];
static const char websocket_magic_number[] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";


char *wb_accept = "HTTP/1.1 101 Switching Protocols\r\n" \
				  "Upgrade: websocket-client\r\n" \
				  "Connection: Upgrade\r\n" \
				  "Sec-WebSocket-Accept: %s\r\n\r\n";


static int on_header_field(http_parser* p, const char *at,size_t length) {
    strncpy(header_key, at, length);
    header_key[length] = 0;
    return 0;
}

static int on_header_value(http_parser* p, const char *at,size_t length) {
    if (strcmp(header_key, "Sec-WebSocket-Key") != 0) {
        return 0;
    }
    strncpy(client_ws_key, at, length);
    client_ws_key[length] = 0;
    return 0;
}
/**
 * 获取加密摘要
 * @param md_value 加密的后的值
 * @param md_len 加密的长度
 * @param name 加密类型, 例如SHA1、SHA256
 * @param key 密钥
 */
void getMd(unsigned char* md_value, unsigned int* md_len, const char * name, const char* key){
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_get_digestbyname(name);
    if (md == NULL) {
        printf("Unknown message digest\n");
        exit(1);
    }
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex2(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, key, strlen(key));
    EVP_DigestFinal_ex(mdctx, md_value, md_len);
    EVP_MD_CTX_free(mdctx);
}
/**
 * 输出socket状态
 * @param fd 文件描述符
 */
void printSocketStat(int fd){
    int optval,optlen = sizeof(int);
    getsockopt(fd,SOL_SOCKET,SO_TYPE,&optval,&optlen);
    printf("optval6 = %d\n",optval);
}
//握手
void process_ws_shake_hand(int sock, char* http_str) {
    http_parser p;
    http_parser_init(&p, HTTP_REQUEST);
    http_parser_settings s;
    http_parser_settings_init(&s);
    s.on_header_field = on_header_field;
    s.on_header_value = on_header_value;
    static char key_migic[256];
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    // 解析http数据, 如果不是http报文, 则报错
    http_parser_execute(&p, &s, http_str, strlen(http_str));
    // 回一个http的数据给我们的client,建立websocket链接
    sprintf(key_migic, "%s%s", client_ws_key, websocket_magic_number);
    getMd(md_value, &md_len, "SHA1", key_migic);
    char* b64_str = b64_encode(md_value, md_len);
    // 将这个http的报文回给我们的websocket连接请求的客户端，
    // 生成websocket连接。
    char accept_buffer[256];
    sprintf(accept_buffer, wb_accept, b64_str);
    printf("发送的数据为:\n %s\n", accept_buffer);
    if(send(sock, accept_buffer, strlen(accept_buffer), 0) < 0){
        perror("send");
    }
    free(b64_str);
}


//发送数据(没有mask)
void ws_send_data(struct session* s, unsigned char* pkg_data, unsigned int pkg_len) {
    static unsigned char send_buffer[8196];
    unsigned int send_len;
    // 固定的头
    send_buffer[0] = 0x81;
    if (pkg_len <= 125) {
        send_buffer[1] = pkg_len; // 最高bit为0，
        send_len = 2;
    }
    else if (pkg_len <= 0xffff) {
        send_buffer[1] = 126;
        send_buffer[2] = (pkg_len & 0x000000ff);
        send_buffer[3] = ((pkg_len & 0x0000ff00) >> 8);
        send_len = 4;
    }
    else {
        send_buffer[1] = 127;
        send_buffer[2] = (pkg_len & 0x000000ff);
        send_buffer[3] = ((pkg_len & 0x0000ff00) >> 8);
        send_buffer[4] = ((pkg_len & 0x00ff0000) >> 16);
        send_buffer[5] = ((pkg_len & 0xff000000) >> 24);

        send_buffer[6] = 0;
        send_buffer[7] = 0;
        send_buffer[8] = 0;
        send_buffer[9] = 0;
        send_len = 10;
    }
    memcpy(send_buffer + send_len, pkg_data, pkg_len);
    send_len += pkg_len;
    send(s->c_sock, send_buffer, send_len, 0);
}

/**解析包*/
int on_ws_recv_data(struct session* s, unsigned char*pkg_data, int pkg_len, char* msg) {
    int ret =0;
    // 第一个字节是头，已经判断，跳过;
    unsigned char* mask = NULL;
    unsigned char* raw_data = NULL;
    unsigned int len = pkg_data[1];
    // 最高的一个bit始终为1,我们要把最高的这个bit,变为0;
    len = (len & 0x0000007f);
    if (len <= 125) {
        mask = pkg_data + 2; // 头字节，长度字节
    }
    else if (len == 126) { // 后面两个字节表示长度；
        len = ((pkg_data[2]) | (pkg_data[3] << 8));
        mask = pkg_data + 2 + 2;
    }
    else if (len == 127){ // 这种情况不用考虑,考虑前4个字节的大小，后面不管;
        unsigned int low = ((pkg_data[2]) | (pkg_data[3] << 8) | (pkg_data[4] << 16) | (pkg_data[5] << 24));
        unsigned int hight = ((pkg_data[6]) | (pkg_data[7] << 8) | (pkg_data[8] << 16) | (pkg_data[9] << 24));
        if (hight != 0) { // 表示后四个字节有数据int存放不了，太大了，我们不要了。
            return ret;
        }
        len = low;
        mask = pkg_data + 2 + 8;
    }
    // mask 固定4个字节，所以后面的数据部分
    raw_data = mask + 4;
    // 还原我们的发送过来的数据;
    // 从原始数据的第0个字节开始，然后，每个字节与对应的mask进行异或，得到真实的数据。
    // 由于mask只有4个字节，所以mask循环重复使用;(0, 1, 2, 3, 0, 1, 2, 3);
    static unsigned char recv_buf[8096];
    unsigned int i;
    for (i = 0; i < len; i++) {
        recv_buf[i] = raw_data[i] ^ mask[i % 4]; // mask只有4个字节的长度，所以，要循环使用，如果超出，取余就可以了。
    }
    recv_buf[len] = 0;
    int head = pkg_data[0];
    // if(pkg_data[0]==0x81 || pkg_data[0]==0x82){
    if(head==129 || head==130){
        printf("%s:%d recv data:%s\n",s->c_ip,s->c_port,recv_buf);
        memcpy(msg, recv_buf, len);
        ret = 1;
    }else{
        printf("the head is not : 0x81 or 0x82\n");
    }
    return ret;
}


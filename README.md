# WebSocket学习
通过websocket客户端和服务器源码来加深WebSocket学习

---
## 一、WebSocket介绍
WebSocket是双向的，服务器可以主动向客户端推送信息，客户端也可以主动向服务器发送信息。

它是一个有状态协议，这意味着客户端和服务器之间的连接将保持活动状态，直到被任何一方（客户端或服务器）终止。在通过客户端和服务器中的任何一方关闭连接之后，连接将从两端终止。

WebSocket协议的其他特点:
* 建立在 TCP 协议之上，服务器端的实现比较容易。
* 与 HTTP 协议有着良好的兼容性。默认端口也是80和443，并且握手阶段采用 HTTP 协议，因此握手时不容易屏蔽，能通过各种 HTTP 代理服务器。
* 数据格式比较轻量，性能开销小，通信高效。
* 可以发送文本，也可以发送二进制数据。
* 没有同源限制，客户端可以与任意服务器通信。
* 协议标识符是ws（如果加密，则为wss），服务器网址就是 URL。
  `ws://example.com:80/some/pathj`

WebSocket Protocol RFC: https://www.rfc-editor.org/rfc/rfc6455

---
##  二、重新回顾HTTP协议:

---
HTTP协议（Hyper Text Transfer Protocol，超文本传输协议）
1. 概括
* HTTP基于TCP/IP通信协议来传递数据。

* TTP基于客户端/服务端（C/S）架构模型，通过一个可靠的链接来交换信息，是一个无状态(不保存客户的任何信息)的请求/响应协议。

2. 特点
* HTTP是无连接：无连接的含义是限制每次连接只处理一个请求。服务器处理完客户的请求，并收到客户的应答后，即断开连接。采用这种方式可以节省传输时间。
* HTTP是媒体独立的：只要客户端和服务器知道如何处理的数据内容，任何类型的数据都可以通过HTTP发送。客户端以及服务器指定使用适合的MIME-type内容类型。
* HTTP是无状态：无状态是指协议对于事务处理没有记忆能力。缺少状态意味着如果后续处理需要前面的信息，则它必须重传，这样可能导致每次连接传送的数据量增大。另一方面，在服务器不需要先前信息时它的应答就较快。

更多有关HTTP协议信息请看: https://developer.mozilla.org/en-US/docs/Web/HTTP

<table>
    <caption>HTTP响应通用报文格式</caption>
    <tr style="border: 0">
        <th rowspan="" style="border-width: 1px 0 0 0;">状态行</th>
        <td colspan="2">方法</td>
        <td>sp</td>
        <td colspan="2">URL</td>
        <td>sp</td>
        <td colspan="2">版本</td>
        <td>cr</td>
        <td>if</td>
    </tr>
    <tr style="border: 0">
        <th rowspan="3" style="border-width: 1px 0 0 0;">首部行</th>
        <td colspan="2">首部字段名</td>
        <td>sp</td>
        <td colspan="2">值</td>
        <td>cr</td>
        <td>lf</td>
    </tr>
    <tr style="border: 0">
        <td colspan="8" style="text-align: center">....</td>
    </tr>
     <tr style="border: 0">
        <td colspan="2">首部字段名</td>
        <td>sp</td>
        <td colspan="2">值</td>
        <td>cr</td>
        <td>lf</td>
    </tr>   
    <tr style="border: 0">
        <th rowspan="1" style="border-width: 1px 0 0 0;">空行</th>
        <td>cr</td>
        <td>lf</td>
    </tr>
    <tr style="border: 0">
        <th rowspan="2" style="border-width: 1px 0 1px 0;">实体体</th>
        <td colspan="10" style="text-align: center">实体体</td>
    </tr>
    <tr style="border: 0">
        <td colspan="10" style="text-align: center">...</td>
    </tr>
</table>

HTTP请求报文: 
```http request
GET /some-dir/page.html HTTP/1.1
HOST: www.someschool.edu
Connection: close
User-agent: Mozilla/5.0
Accept-language: fr
```

----

<table>
    <caption>HTTP响应通用报文格式</caption>
    <tr style="border: 0">
        <th rowspan="" style="border-width: 1px 0 0 0;">状态行</th>
        <td colspan="2">版本</td>
        <td>sp</td>
        <td colspan="2">状态码</td>
        <td>sp</td>
        <td colspan="2">短语</td>
        <td>cr</td>
        <td>if</td>
    </tr>
    <tr style="border: 0">
        <th rowspan="3" style="border-width: 1px 0 0 0;">首部行</th>
        <td colspan="2">首部字段名</td>
        <td>sp</td>
        <td colspan="2">值</td>
        <td>cr</td>
        <td>lf</td>
    </tr>
    <tr style="border: 0">
        <td colspan="8" style="text-align: center">....</td>
    </tr>
     <tr style="border: 0">
        <td colspan="2">首部字段名</td>
        <td>sp</td>
        <td colspan="2">值</td>
        <td>cr</td>
        <td>lf</td>
    </tr>   
    <tr style="border: 0">
        <th rowspan="1" style="border-width: 1px 0 0 0;">空行</th>
        <td>cr</td>
        <td>lf</td>
    </tr>
    <tr style="border: 0">
        <th rowspan="2" style="border-width: 1px 0 1px 0;">实体体</th>
        <td colspan="10" style="text-align: center">实体体</td>
    </tr>
    <tr style="border: 0">
        <td colspan="10" style="text-align: center">...</td>
    </tr>
</table>

HTTP响应报文:
```http request
HTTP/1.1 200 OK
Connection: close
Date: Tue, 18 Aug 2015 15:44:04 GMT
Server: Apache/2.2.3 (CentOS)
Last-Modified: Tue, 18 Aug 2015 15:11:03 GMT
Content-Length: 6821
Content-Type: text/html

(data data data data data)
```
> lf: line feed (换行) 的缩写
> 
> sp: space (空格)  缩写
> 
> cr: carriage return (回车)的缩写
---
##  三、WebSocket请求和响应信息:
WebSocket请求信息:
```http request
GET /xxx HTTP/1.1
Host: server.example.com
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
Sec-WebSocket-Protocol: chat, superchat
Sec-WebSocket-Version: 13
```
WebSocket响应信息:
```http request
HTTP/1.1 101 Switching Protocols
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=
Sec-WebSocket-Protocol: chat
```
常用状态码: 
* 101：HTTP协议切换为WebSocket协议。
* 1000：正常断开连接。
* 1001：服务器断开连接。
* 1002：websocket协议错误。
* 1003：客户端接受了不支持数据格式（只允许接受文本消息，不允许接受二进制数据，是客户端限制不接受二进制数据，而不是websocket协议不支持二进制数据）。
* 1006：异常关闭。
* 1007：客户端接受了无效数据格式（文本消息编码不是utf-8）。
* 1009：传输数据量过大。
* 1010：客户端终止接。
* 1011：服务器终止连接。
* 1012：服务端正在重新启动。
* 1013：服务端临时终止。
* 1014：通过网关或代理请求服务器，服务器无法及时响应。
* 1015：TLS握手失败。

---
## TODO:
1. 进入项目目录, 使用cmake生成Makefile文件(可选)
```bash
cmake build .
```
2. 使用make构建
```shell
make all
```
3. 启动服务器
```shell
./websocket-server/websocket-server
```
4. 启动客户端
```shell
./websocket-client/websocket-client
```
## 建议
可以使用clion打开进行调试学习

参考:
* [Easywsclient](https://github.com/core1011/websocket) (使用c++编写的简单强大的WebSocket客户端)
* [Http-parser](http://github.com/joyent/http-parser) (使用c编写的HTTP解析器)
* [RFC6455](https://www.rfc-editor.org/rfc/rfc6455) (WebSocket请求评论)
* [RFC2616](https://www.rfc-editor.org/rfc/rfc2616) (HTTP协议请求评论)
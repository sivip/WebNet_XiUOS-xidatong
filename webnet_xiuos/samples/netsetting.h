#ifndef _NETSETTING_H
#define _NETSETTING_H
#include <webnet.h>
#include <wn_module.h>
#include<cJSON.h>
#include<transform.h>

#define cgi_head()                       \
    ;                                    \
    const char *mimetype;                \
    struct webnet_request *request;      \
    static char *body = NULL;            \
    request = session->request;          \
    mimetype = mime_get_type(".html");   \
    session->request->result_code = 200; \
    webnet_session_set_header(session, mimetype, 200, "Ok", -1);

/*
mqtt platform macro
*/
#define ALIYUN_SERVER_ADDR  "hf6mzwdVnJg.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define ALIYUN_SERVER_PORT  "1883"
#define ALIYUN_SERVER_TOPIC "/broadcast/hf6mzwdVnJg/989898"
#define ALIYUN_USERNAME     "test1&hf6mzwdVnJg"
#define ALIYUN_PASSWORD     "F08C59D320BB72830B9ECC5ACF132BC22B55861B"
#define ALIYUN_CLIENTID     "123|securemode=3,signmethod=hmacsha1|"

#define LOCAL_IP_ADDR       "192.168.131.29"
#define LOCAL_NETMASK_ADDR  "255.255.255.0"
#define LOCAL_GATEWAY_MASK  "192.168.130.1"
#define LOCAL_DNS_SERVER0   "0.0.0.0"
#define LOCAL_DNS_SERVER1   "0.0.0.0"

#define PRIVATE_SERVER_ADDR "192.168.131.30"
#define PRIVATE_SERVER_PORt "9898"
#define PRIVATE_USERNAME    "admin"
#define PRIVATE_PASSWORD    "admin"

typedef struct 
{

    char topic[100];        //topic 
    char server_addr[100]; //服务器地址
    char server_port[12];  //服务器端口
    char username[50];     //用户名
    char password[100];     //密码
    char clientid[100];    //client id

}mqttsetting;


typedef struct
{
    char local_ipaddr[16];       //本地ip
    char netmask_addr[16];       //子网掩码
    char gateway_addr[16];      //网关
    char dns_server0[16];
    char dns_server1[16];
}local_tcpip;


typedef struct
{
    char server_addr[100];      //私有协议服务器地址
    char server_port[12];      //端口号
    char username[16];          //用户名
    char passward[16];          //密码确认
}private_prt;

void mqttweb_default();
void local_tcpipweb_default();
void private_prtweb_default();
void cgi_mqtt_get_data(struct webnet_session *session);
void cgi_mqtt_save_data(struct webnet_session *session);
void cgi_tcpip_get_data(struct webnet_session *session);
void cgi_tcpip_save_data(struct webnet_session *session);
void cgi_private_prt_get_data(struct webnet_session *session);
void cgi_private_prt_save_data(struct webnet_session *session);

#endif
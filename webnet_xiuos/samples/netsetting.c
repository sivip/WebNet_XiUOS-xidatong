#include "netsetting.h"


static mqttsetting mqttweb;
static local_tcpip local_tcpipweb;
static private_prt private_prtweb;


void mqttweb_default()
{
    strcpy(mqttweb.server_addr,ALIYUN_SERVER_ADDR);
    strcpy(mqttweb.server_port,ALIYUN_SERVER_PORT);
    strcpy(mqttweb.topic,ALIYUN_SERVER_TOPIC);
    strcpy(mqttweb.username,ALIYUN_USERNAME);
    strcpy(mqttweb.password,ALIYUN_PASSWORD);
    strcpy(mqttweb.clientid,ALIYUN_CLIENTID);
}

void local_tcpipweb_default()
{
    strcpy(local_tcpipweb.local_ipaddr,LOCAL_IP_ADDR);
    strcpy(local_tcpipweb.netmask_addr,LOCAL_NETMASK_ADDR);
    strcpy(local_tcpipweb.gateway_addr,LOCAL_GATEWAY_MASK);
    strcpy(local_tcpipweb.dns_server0,LOCAL_DNS_SERVER0);
    strcpy(local_tcpipweb.dns_server1,LOCAL_DNS_SERVER1);
}

void private_prtweb_default()
{
    strcpy(private_prtweb.server_addr,PRIVATE_SERVER_ADDR);
    strcpy(private_prtweb.server_port,PRIVATE_SERVER_PORt);
    strcpy(private_prtweb.username,PRIVATE_USERNAME);
    strcpy(private_prtweb.passward,PRIVATE_PASSWORD);
}


char *json_create_mqtt_data(void)
{
    char *json_data = RT_NULL;
    cJSON *root = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "pub_topic", cJSON_CreateString(mqttweb.topic));
    cJSON_AddItemToObject(root, "server_addr", cJSON_CreateString(mqttweb.server_addr));
    cJSON_AddItemToObject(root, "server_port", cJSON_CreateString(mqttweb.server_port));
    cJSON_AddItemToObject(root, "username", cJSON_CreateString(mqttweb.username));
    cJSON_AddItemToObject(root, "password", cJSON_CreateString(mqttweb.password));
    cJSON_AddItemToObject(root, "clientID", cJSON_CreateString(mqttweb.clientid));
    json_data = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json_data;
}

void cgi_mqtt_get_data(struct webnet_session *session)
{
    cgi_head();
    request = request;
    body = json_create_mqtt_data();
    webnet_session_printf(session, body);
    free(body);
}

void cgi_mqtt_save_data(struct webnet_session *session)
{
    cgi_head();
    const char *response = "{\"code\":0}";
    const char *tpub_topic = webnet_request_get_query(request, "pub_topic");
    const char *tserver_addr = webnet_request_get_query(request, "server_addr");
    const char *tserver_port = webnet_request_get_query(request, "server_port");
    const char *tusername = webnet_request_get_query(request, "username");
    const char *tpassword = webnet_request_get_query(request, "password");
    const char *tclientID = webnet_request_get_query(request, "clientID");
    /*configuration*/
    memset((char*)(&mqttweb),0,sizeof(mqttweb));
    strcpy(mqttweb.server_addr,tserver_addr);
    strcpy(mqttweb.server_port,tserver_port);
    strcpy(mqttweb.topic,tpub_topic);
    strcpy(mqttweb.username,tusername);
    strcpy(mqttweb.password,tpassword);
    strcpy(mqttweb.clientid,tclientID);

    printf("\n\r    \
    mqtt serveraddr: %s           \n  \
    mqtt server_port: %s          \n  \
    mqtt topic: %s                \n  \
    mqtt username: %s             \n  \
    mqtt password: %s             \n  \
    mqtt clientid: %s             \n  \
    ",mqttweb.server_addr,mqttweb.server_port,mqttweb.topic,      \
    mqttweb.username,mqttweb.password,mqttweb.clientid);
    webnet_session_printf(session, response);
}


static void device_get_tcpip_parameter()
{
    #ifdef  ADD_XIZI_FETURES
    struct netdev *netdev_device = netdev_get_by_name("e0");
    /*
    printf("ip address: %s\n", inet_ntoa(netdev_device->ip_addr));
    printf("netmask address: %s\n", inet_ntoa(netdev_device->netmask));
    printf("gw address: %s\n", inet_ntoa(netdev_device->gw));
    printf("dns0 address: %s\n", inet_ntoa(netdev_device->dns_servers[0]));
    printf("dns1 address: %s\n", inet_ntoa(netdev_device->dns_servers[1]));
    */
    strcpy(local_tcpipweb.local_ipaddr,inet_ntoa(netdev_device->ip_addr));
    strcpy(local_tcpipweb.netmask_addr,inet_ntoa(netdev_device->netmask));
    strcpy(local_tcpipweb.gateway_addr,inet_ntoa(netdev_device->gw));
    strcpy(local_tcpipweb.dns_server0,inet_ntoa(netdev_device->dns_servers[0]));
    strcpy(local_tcpipweb.dns_server1,inet_ntoa(netdev_device->dns_servers[1]));
    #elif defined ADD_XIZI_FETURES
    #endif
}

char *json_create_tcpip_data(void)
{
    char *json_data = RT_NULL;
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "local_ipaddr", cJSON_CreateString(local_tcpipweb.local_ipaddr));
    cJSON_AddItemToObject(root, "netmask_addr", cJSON_CreateString(local_tcpipweb.netmask_addr));
    cJSON_AddItemToObject(root, "gateway_addr", cJSON_CreateString(local_tcpipweb.gateway_addr));
    cJSON_AddItemToObject(root, "dns_server0", cJSON_CreateString(local_tcpipweb.dns_server0));
    cJSON_AddItemToObject(root, "dns_server1", cJSON_CreateString(local_tcpipweb.dns_server1));
    json_data = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json_data;

}
void cgi_tcpip_get_data(struct webnet_session *session)
{
    cgi_head();
    request = request;
    device_get_tcpip_parameter();
    body = json_create_tcpip_data();
    webnet_session_printf(session, body);
    free(body);
}

void cgi_tcpip_save_data(struct webnet_session *session)
{
    cgi_head();
    ip_addr_t addr;
    const char *response = "{\"code\":0}";
    const char *local_ipaddr = webnet_request_get_query(request, "local_ipaddr");
    const char *netmask_addr = webnet_request_get_query(request, "netmask_addr");
    const char *gateway_addr = webnet_request_get_query(request, "gateway_addr");
    const char *dns_server0 = webnet_request_get_query(request, "dns_server0");
    const char *dns_server1 = webnet_request_get_query(request, "dns_server1");
    #ifdef   ADD_XIZI_FETURES
    struct netdev *netdev_device = netdev_get_by_name("e0");
    inet_aton(local_ipaddr, &addr);
    netdev_set_ipaddr(netdev_device, &addr);
    inet_aton(netmask_addr, &addr);
    netdev_set_netmask(netdev_device, &addr);
    inet_aton(gateway_addr, &addr);
    netdev_set_gw(netdev_device, &addr);
    inet_aton(dns_server0, &addr);
    netdev_set_dns_server(netdev_device,0, &addr);
    inet_aton(dns_server1, &addr);
    netdev_set_dns_server(netdev_device,0, &addr);
    #elif defined ADD_XIZI_FETURES
    #endif
    /*configuration*/
    memset((char*)(&local_tcpipweb),0,sizeof(local_tcpipweb));
    strcpy(local_tcpipweb.local_ipaddr,local_ipaddr);
    strcpy(local_tcpipweb.netmask_addr,netmask_addr);
    strcpy(local_tcpipweb.gateway_addr,gateway_addr);
    strcpy(local_tcpipweb.dns_server0,dns_server0);
    strcpy(local_tcpipweb.dns_server1,dns_server1);
    webnet_session_printf(session, response);
}



char *json_create_private_prt_data()
{
    char *json_data = RT_NULL;
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "server_addr", cJSON_CreateString(private_prtweb.server_addr));
    cJSON_AddItemToObject(root, "server_port", cJSON_CreateString(private_prtweb.server_port));
    cJSON_AddItemToObject(root, "username", cJSON_CreateString(private_prtweb.username));
    cJSON_AddItemToObject(root, "passward", cJSON_CreateString(private_prtweb.passward));
    json_data = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json_data;
}

void cgi_private_prt_get_data(struct webnet_session *session)
{
    cgi_head();
    request = request;
    body = json_create_private_prt_data();
    webnet_session_printf(session, body);
    free(body);
}

void cgi_private_prt_save_data(struct webnet_session *session)
{
    cgi_head();
    ip_addr_t addr;
    const char *response = "{\"code\":0}";
    const char *server_addr = webnet_request_get_query(request, "server_addr");
    const char *server_port = webnet_request_get_query(request, "server_port");
    const char *username = webnet_request_get_query(request, "username");
    const char *passward = webnet_request_get_query(request, "passward");

    /*configuration*/
    memset((char*)(&private_prtweb),0,sizeof(private_prtweb));
    strcpy(private_prtweb.server_addr,server_addr);
    strcpy(private_prtweb.server_port,server_port);
    strcpy(private_prtweb.username,username);
    strcpy(private_prtweb.passward,passward);
    webnet_session_printf(session, response);
}

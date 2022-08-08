#include "uploaddata.h"
char msg[] = "/mq_upload_web";
sensor_msg eg_temperature;
sensor_msg web_show;

static  mqd_t mq_web;
void upload_receive_web_msg_thread()
{
    int nbytes =  0;
    while(1)
    {
        nbytes = PrivMqueueReceive(mq_web,(char*)(&eg_temperature), sizeof(eg_temperature), NULL);
        if (nbytes < 0)
        {
		    printf("mq_receive error: %d \n",nbytes);
	    }
        else
        {
		    printf("=============mq_receive success:==============\n");
            printf("        \
                name:%s\n          \
                brand %s\n        \
                unit %s\n        \
                value %s\n",      \
        eg_temperature.name,eg_temperature.brand,eg_temperature.unit,eg_temperature.value);
        memcpy(&web_show,&eg_temperature,sizeof(web_show));
	    }
    }

}
int uploaddata_init()
{
    
    struct mq_attr webmq_attr;
    int result = 0;
    pthread_t tid = 0;
    pthread_attr_t attr;
    struct sched_param prio;
    prio.sched_priority = 8;
    size_t stack_size = 1024 * 11;
    webmq_attr.mq_flags = 0;
	webmq_attr.mq_maxmsg = 20;
	webmq_attr.mq_msgsize = 512;
	webmq_attr.mq_curmsgs = 0;
    mq_web = PrivMqueueCreate("/mq_web", O_RDONLY|O_CREAT,0666,&webmq_attr); 
	if (mq_web < 0)
    {
		printf("mq_open error: %d \n",mq_web);
	}else
    {
		printf("mq_open success: %d \n",mq_web);
	}
    pthread_attr_init(&attr);
    pthread_attr_setschedparam(&attr, &prio); 
    pthread_attr_setstacksize(&attr, stack_size);
    result = pthread_create(&tid, &attr,upload_receive_web_msg_thread, NULL);
    if (0 == result) 
    {
      printf("thread_detect_entry successfully!\n");
    } 
    else 
    {
      printf("thread_detect_entry failed! error code is %d.\n", result);
    }
    /***********demo sensor set parameters***************/
    strcpy(eg_temperature.name,"temperature");
    strcpy(eg_temperature.brand,"hs300x");
    strcpy(eg_temperature.unit,"°C");
}


void upload_send_web_msg()
{
    static int seed_t = 20;
    float temp = 25;
    float tem_decimals = 0;
    int nbytes =  0;
    memset((char*)eg_temperature.value,0,sizeof(eg_temperature.value));
    srand(seed_t);
    tem_decimals = ((float)(rand() % 100))/100.0;
    temp = temp + tem_decimals;
    sprintf(eg_temperature.value,"%f",temp);
    printf("rand generate temperature %s \n\r",eg_temperature.value);

    nbytes = PrivMqueueSend(mq_web, (char *)(&eg_temperature), sizeof(eg_temperature), 0);
	if (nbytes < 0)
    {
		printf("mq_send error: %d \n",nbytes);
	}
    else
    {
		printf("mq_send success: times%d \n",seed_t);
	}
    seed_t++;
}
#ifdef  ADD_XIZI_FETURES
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN) | SHELL_CMD_PARAM_NUM(0),
     upload_send_web_msg, upload_send_web_msg, upload_send_web_msg);
#endif
char *json_create_datashow_data()
{
    char *json_data = RT_NULL;
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "name", cJSON_CreateString(web_show.name));
    cJSON_AddItemToObject(root, "brand", cJSON_CreateString(web_show.brand));
    cJSON_AddItemToObject(root, "unit", cJSON_CreateString(web_show.unit));
    cJSON_AddItemToObject(root, "value", cJSON_CreateString(web_show.value));
    json_data = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json_data;
}

 void cgi_dateshow_get_data(struct webnet_session *session)
 {
    cgi_head();
    request = request;
    body = json_create_datashow_data();
    webnet_session_printf(session, body);
    free(body);
 }

#ifndef _UPLOADDATA_
#define _UPLOADDATA_
#include "netsetting.h"
typedef struct 
{
    char name[32];   //sensor  name
    char brand[32];  //sensor  brand;
    char unit[12];   //sensor  unit
    char value[12];  //sensor value
}sensor_msg;


int uploaddata_init();
void upload_send_web_msg();
void cgi_dateshow_get_data(struct webnet_session *session);
#endif
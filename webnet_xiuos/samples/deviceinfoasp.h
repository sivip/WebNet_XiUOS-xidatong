#ifndef _DEVICEINFO_H
#define _DEVICEINFO_H
#include <webnet.h>
#include <wn_module.h>

#define RT_THREAD_KERNEL        "rt-thread kenel"
#define NUTTX_OS_KERNEL         "nuttx kenel"
#define XIZI_OS_KERNEL          "xizi kenel"
#define DEVICE_NAME_DEFUALT     "xidatong"
#define DEVICE_TYPE_DEFUALT     "gateway"
#define DEVICE_SERIAL_DEFUALT   "12345678910"
#define DEVICE_NUM_DEFUALT      (1)
#define WEB_VERSION             "1.0.0"
#define SYSTEM_VERSION          "1.1.1"



typedef struct 
{
    int number;
    char name[16];
    char type[16];
    char serial[16];
    char ostype[16];
    char system_firmware[8];
    char webversion[8];
}deviceinfo;

void deviceinfo_default();
void asp_var_device_name(struct webnet_session* session);
void asp_var_device_number(struct webnet_session* session);
void asp_var_device_type(struct webnet_session* session);
void asp_var_device_serial(struct webnet_session* session);
void asp_var_os_type(struct webnet_session* session);
void asp_var_web_version(struct webnet_session* session);
void asp_var_system_firmware(struct webnet_session* session);
void cgi_device_reboot();
void cgi_device_recovery();
#endif
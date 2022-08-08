#include "deviceinfoasp.h"
deviceinfo xidatong_deviceinfo =
{
    DEVICE_NUM_DEFUALT,
    DEVICE_NAME_DEFUALT,
    DEVICE_TYPE_DEFUALT,
    DEVICE_SERIAL_DEFUALT,
    RT_THREAD_KERNEL,
    SYSTEM_VERSION,
    WEB_VERSION
};

void deviceinfo_default()
{
    /*
    目前认为这个是不变的变量
    */
    //memset((char *)(&xidatong_deviceinfo),0,sizeof(xidatong_deviceinfo));
}

 void asp_var_device_name(struct webnet_session* session)
{
    assert(session != NULL);
    static const char *temp = "<html><body>%s";
    webnet_session_printf(session, temp, xidatong_deviceinfo.name);
}

 void asp_var_device_number(struct webnet_session* session)
{
    assert(session != NULL);
    static const char *temp = "<html><body>%d" ;      
    webnet_session_printf(session, temp,xidatong_deviceinfo.number);
}

 void asp_var_device_type(struct webnet_session* session)
{
    assert(session != NULL);
    static const char *temp = "<html><body>%s";
    webnet_session_printf(session, temp, xidatong_deviceinfo.type);
}


 void asp_var_device_serial(struct webnet_session* session)
{
    assert(session != NULL);
    static const char *temp = "<html><body>%s";
    webnet_session_printf(session, temp, xidatong_deviceinfo.serial);
}

 void asp_var_os_type(struct webnet_session* session)
{
    assert(session != NULL);
    static const char *temp = "<html><body>%s";
    webnet_session_printf(session, temp, xidatong_deviceinfo.ostype);
}
 void asp_var_web_version(struct webnet_session* session)
{
    assert(session != NULL);
    static const char *temp = "<html><body>%s";
    webnet_session_printf(session, temp,xidatong_deviceinfo.webversion);
}

 void asp_var_system_firmware(struct webnet_session* session)
{
    assert(session != NULL);
    static const char *temp = "<html><body><font size=\"+2\">系统固件 %s</font><br><br>";
    webnet_session_printf(session, temp, xidatong_deviceinfo.system_firmware);
}



void cgi_device_reboot(struct webnet_session* session)
{
    const char* mimetype;
    const char *response = "{\"code\":0}";
    static char order_sh[] = "reboot";
    mimetype = mime_get_type(".html");
    session->request->result_code = 200;
    webnet_session_set_header(session, mimetype, 200, "Ok", -1);
    webnet_session_printf(session, response);
    #ifdef  ADD_XIZI_FETURES
        extern int msh_exec(char *cmd, rt_size_t length);
        printf("reboot ！！！！！ \n\r");
        msh_exec(order_sh,rt_strlen(order_sh));
    #elif defined ADD_XIZI_FETURES
    #endif
   
}

extern void mqttweb_default();
extern void private_prtweb_default();
void cgi_device_recovery(struct webnet_session* session)
{
    const char* mimetype;
    const char *response = "{\"code\":0}";
    mimetype = mime_get_type(".html");
    session->request->result_code = 200;
    webnet_session_set_header(session, mimetype, 200, "Ok", -1);
    webnet_session_printf(session, response);
    mqttweb_default();
    private_prtweb_default();

}
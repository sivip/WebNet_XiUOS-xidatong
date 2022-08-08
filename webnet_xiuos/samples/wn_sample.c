/*
 * File      : wn_sample.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 * This software is dual-licensed: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation. For the terms of this
 * license, see <http://www.gnu.org/licenses/>.
 *
 * You are free to use this software under the terms of the GNU General
 * Public License, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * Alternatively for commercial application, you can contact us
 * by email <business@rt-thread.com> for commercial license.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-09     chunyexixiaoyu      the version transplanted from rt-thread  
 */
#include <transform.h>
#include <webnet.h>
#include <wn_module.h>
#include "deviceinfoasp.h"
#include "netsetting.h"
#include "uploaddata.h"
#define XiUOS_VERSION       (1)
#define XiUOS_SUBVERSION    (0)
#define XiUOS_REVERSION     (0)



void webnet_start(void)
{
#ifdef WEBNET_USING_CGI
    webnet_cgi_register("mqtt_get", cgi_mqtt_get_data);
    webnet_cgi_register("mqtt_save", cgi_mqtt_save_data);
    webnet_cgi_register("tcpip_get", cgi_tcpip_get_data);
    webnet_cgi_register("tcpip_save", cgi_tcpip_save_data);
    webnet_cgi_register("private_prt_get", cgi_private_prt_get_data);
    webnet_cgi_register("private_prt_save", cgi_private_prt_save_data);
    webnet_cgi_register("device_reboot", cgi_device_reboot);
    webnet_cgi_register("device_recovery", cgi_device_recovery);
    webnet_cgi_register("datashow", cgi_dateshow_get_data);
#endif

#ifdef WEBNET_USING_ASP
    webnet_asp_add_var("device_name", asp_var_device_name);
    webnet_asp_add_var("device_number", asp_var_device_number);
    webnet_asp_add_var("device_type", asp_var_device_type);
    webnet_asp_add_var("device_serial", asp_var_device_serial);
    webnet_asp_add_var("os_type", asp_var_os_type);
    webnet_asp_add_var("system_firmware", asp_var_system_firmware);
    webnet_asp_add_var("web_version", asp_var_web_version);
#endif

#ifdef WEBNET_USING_ALIAS
    webnet_alias_set("/test", "/admin");
#endif

#ifdef WEBNET_USING_AUTH
    webnet_auth_set("/", "admin:admin");
#endif

#ifdef WEBNET_USING_UPLOAD
    extern const struct webnet_module_upload_entry upload_entry_upload;

    webnet_upload_add(&upload_entry_upload);
#endif
    private_prtweb_default();
    mqttweb_default();
    uploaddata_init();
    webnet_init();
    

}
#ifdef  ADD_XIZI_FETURES
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN) | SHELL_CMD_PARAM_NUM(0),
     webnet_start, webnet_start, wenbet test);
#endif

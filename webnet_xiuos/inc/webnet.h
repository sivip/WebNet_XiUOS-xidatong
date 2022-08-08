/*
 * File      : webnet.h
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
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-10     chunyexixiaoyu      the version transplanted from rt-thread 
 */

#ifndef __WEBNET_H__
#define __WEBNET_H__

#include <transform.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef wn_malloc
#define wn_malloc                      malloc
#endif

#ifndef wn_free
#define wn_free                        free
#endif

#ifndef wn_realloc
#define wn_realloc                     realloc
#endif

#ifndef wn_strdup
#define wn_strdup                      strdup
#endif

#ifndef WEBNET_USING_RANGE
#define WEBNET_USING_RANGE
#endif

#ifndef WEBNET_USING_KEEPALIVE
#define WEBNET_USING_KEEPALIVE
#endif

#ifndef WEBNET_USING_COOKIE
#define WEBNET_USING_COOKIE
#endif

#define WEBNET_VERSION                 "2.0.3"      /* webnet version string */
#define WEBNET_VERSION_NUM             0x20003      /* webnet version number */
#define WEBNET_THREAD_NAME             "webnet"     /* webnet thread name */

#define WEBNET_THREAD_STACKSIZE        (4 * 1024)   /* webnet thread stack size */
#define WEBNET_PRIORITY                20           /* webnet thread priority */
#define WEBNET_PATH_MAX                256          /* maxiaml path length in webnet */
#define WEBNET_SERVER                  "Server: webnet "WEBNET_VERSION"\r\n"

/* Pre-declaration */
struct webnet_session;
/* webnet query item definitions */
struct webnet_query_item
{
    char* name;
    char* value;
};

/* get mimetype according to URL */
const char* mime_get_type(const char* url);

/* set and get listen socket port */
void webnet_set_port(int port);
int webnet_get_port(void);

/* set and get root directory path */
void webnet_set_root(const char* webroot_path);
const char* webnet_get_root(void);

/* webnet initialize */
int webnet_init(void);

#ifdef  __cplusplus
    }
#endif

#endif /* __WEBNET_H__ */

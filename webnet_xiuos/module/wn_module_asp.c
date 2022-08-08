/*
 * File      : wn_module_asp.c
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

#include<transform.h>
#include <string.h>
#include <webnet.h>
#include <wn_module.h>
#include <wn_utils.h>

#ifdef WEBNET_USING_ASP

struct webnet_asp_variable
{
    char* name;
    void (*handler)(struct webnet_session* session);
};
static struct webnet_asp_variable* _webnet_asp_vars = NULL;
int32 _webnet_asp_vars_count = 0;

void webnet_asp_add_var(const char* name, void (*handler)(struct webnet_session* session))
{
    if (_webnet_asp_vars == NULL)
    {
        _webnet_asp_vars_count = 1;
        _webnet_asp_vars = (struct webnet_asp_variable*)wn_malloc (sizeof(struct webnet_asp_variable) *
                           _webnet_asp_vars_count);
    }
    else
    {
        _webnet_asp_vars_count += 1;
        _webnet_asp_vars = (struct webnet_asp_variable*) wn_realloc (_webnet_asp_vars, sizeof(struct webnet_asp_variable) *
                           _webnet_asp_vars_count);
    }

    assert(_webnet_asp_vars != NULL);

    _webnet_asp_vars[_webnet_asp_vars_count - 1].name = wn_strdup(name);
    _webnet_asp_vars[_webnet_asp_vars_count - 1].handler = handler;
}

static void _default_asp_handler(struct webnet_session* session, const char* name)
{
    if (strncmp(name, "VERION", 6) == 0)
    {
        webnet_session_printf(session, "WebNet 1.0.0");
    }
    else if (strncmp(name, "REMOTE_ADDR", 11) == 0)
    {
        webnet_session_printf(session, "%s", inet_ntoa(session->cliaddr.sin_addr));
    }
    else if (strncmp(name, "REMOTE_PORT", 11) == 0)
    {
        webnet_session_printf(session, "%d", ntohs(session->cliaddr.sin_port));
    }
    else if (strncmp(name, "SERVER_PORT", 11) == 0)
    {
        webnet_session_printf(session, "%d", WEBNET_PORT);
    }
    else if (strncmp(name, "DOCUMENT_ROOT", 13) == 0)
    {
        webnet_session_printf(session, "%s", webnet_get_root());
    }
    else if (strncmp(name, "SERVER", 6) == 0)
    {
        webnet_session_printf(session, "RT-Thread/WebNet");
    }
    else if (strncmp(name, "HOST", 4) == 0)
    {
        webnet_session_printf(session, "WebNet");
    }
    else if (strncmp(name, "DATE", 4) == 0)
    {
        webnet_session_printf(session, "2011/08/01");
    }
    else if (strncmp(name, "USER_AGENT", 10) == 0)
    {
        webnet_session_printf(session, "%s", session->request->user_agent);
    }
    else if (strncmp(name, "COOKIE", 6) == 0)
    {
        webnet_session_printf(session, "%s", session->request->cookie);
    }
    else if (strncmp(name, "MEMUSAGE", 8) == 0)
    {
        int32 total, used, max_used;
        total = 1024*32;
        used = 1024*16;
        max_used = 1024*24;

        webnet_session_printf(session, "current %d/maximal used %d/total %d", used, max_used, total);
    }
    else if (strncmp(name, "TICK", 4) == 0)
    {
        int32 tick;//这里定义的tick是多少秒的意思，并不是正常意义上的tick（个人感觉定义为：sum_time更好）
        int32 hour, min, second;
        #ifdef  ADD_XIZI_FETURES
        //tick = rt_tick_get()/RT_TICK_PER_SECOND;
        tick = CurrentTicksGain()/TICK_PER_SECOND;
        #endif
        second = tick % 60;
        min    = (tick/60) % 60;
        hour   = tick / (60 * 60);

        webnet_session_printf(session, "%02d:%02d:%02d", hour, min, second);
    }
}

static void _webnet_asp_dofile(struct webnet_session* session, int fd)
{
    char *asp_begin, *asp_end;
    char *offset, *end;
    char *buffer;
    int32 length, index;

    /* get file length */
    length = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    /* allocate read buffer */
    buffer = (char*) wn_malloc (length);
    if (buffer == NULL)
    {
        session->request->result_code = 500;
        return;
    }

    /* write page header */
    webnet_session_set_header(session, "text/html", 200, "OK", -1);
    /* read file to buffer */
    if (read(fd, buffer, (uint32)length) != length) /* read failed */
    {
        wn_free(buffer);
        session->request->result_code = 500;
        return;
    }

    offset = buffer;
    end = buffer + length;
    while (offset < end)
    {
        /* get beginning of asp variable */
        asp_begin = strstr(offset, "<%");
        if (asp_begin == NULL)
        {
            /* write content directly */
            webnet_session_write(session, (const uint8*)offset, end - offset);
            break;
        }

        /* get end of aps variable */
        asp_end = strstr(asp_begin, "%>");
        if (asp_end == NULL)
        {
            /* write content directly */
            webnet_session_write(session, (const uint8*)offset, end - offset);
            break;
        }
        else
        {
            /* write content */
            webnet_session_write(session, (const uint8*)offset, asp_begin - offset);

            offset = asp_begin + 2;
            while ((*offset == ' ') || (*offset == '\t')) offset ++;

            /* extrace asp variable */
            for (index = 0; index < _webnet_asp_vars_count; index ++)
            {
                if (str_begin_with(offset, _webnet_asp_vars[index].name))
                {
                    /* found asp variable */
                    _webnet_asp_vars[index].handler(session);
                    break;
                }
            }
            if (index == _webnet_asp_vars_count)
            {
                /* use default handler */
                _default_asp_handler(session, offset);
            }

            /* move to the end of asp varaialbe */
            offset = asp_end + 2;
        }
    }

    /* release read buffer */
    wn_free(buffer);
}

int webnet_module_asp(struct webnet_session* session, int event)
{
    struct webnet_request* request;

    assert(session != NULL);
    request = session->request;
    assert(request != NULL);

    if (event == WEBNET_EVENT_URI_POST)
    {
        int fd;

        /* check whether a asp file */
        if ((strstr(request->path, ".asp") != NULL) ||
                (strstr(request->path, ".ASP") != NULL))
        {
            /* try to open this file */

            fd = open(request->path, O_RDONLY, 0);
            if ( fd >= 0)
            {
                _webnet_asp_dofile(session, fd);
                close(fd);
                return WEBNET_MODULE_FINISHED;
            }
            else
            {
                /* no this file */
                request->result_code = 404;
                return WEBNET_MODULE_FINISHED;
            }
        }
        else
        {
            /* try index.asp */
            char *asp_filename;

            asp_filename = (char*) wn_malloc (WEBNET_PATH_MAX);
            if (asp_filename != NULL)
            {
                snprintf(asp_filename, WEBNET_PATH_MAX, "%s/index.asp", request->path);
                fd = open(asp_filename, O_RDONLY, 0);

                if (fd >= 0)
                {
                    wn_free(asp_filename);
                    _webnet_asp_dofile(session, fd);
                    close(fd);
                    return WEBNET_MODULE_FINISHED;
                }
            }
            wn_free(asp_filename);
        }
    }

    return WEBNET_MODULE_CONTINUE;
}

#endif /* WEBNET_USING_ASP */

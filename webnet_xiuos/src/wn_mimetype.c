/*
 * File      : wn_mimetype.c
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
 * 2022-05-09     chunyexixiaoyu      the version from rt-thread 

 */

#include <transform.h>
#include <wn_utils.h>

struct webnet_mime_entry
{
    const char* name;
    const char* type;
};

static const struct webnet_mime_entry mime_tables[] =
{
    { "any",    "application/binary" }, /* default. */
    { "html",   "text/html" },
    { "htm",    "text/html" },
    { "css",    "text/css" },
    { "txt",    "text/plain" },
    { "pdf",    "application/pdf" },
    { "gif",    "image/gif" },
    { "png",    "image/png" },
    { "jpeg",   "image/jpeg" },
    { "jpg",    "image/jpeg" },
    { "svg",    "image/svg+xml" },
    { "avi",    "video/x-msvideo" },
    { "mp3",    "audio/mpeg" },
    { "ogg",    "audio/x-oggvorbis" },
    { "wav",    "audio/x-wav" },
    { "class",  "application/octet-stream" },
    { "js",     "application/x-javascript" },
    { "tar",    "application/x-tar" },
    { "zip",    "application/zip" },
    { "xml",    "text/xml" },
    { "json",   "application/json" },
    { NULL,      NULL }
};

/**
 * get mime type according to URL
 */
const char* mime_get_type(const char* url)
{
    uint32 index;

    index = 0;
    if (url == NULL)
    {
        return mime_tables[0].type;
    }

    while (mime_tables[index].name != NULL)
    {
        if (str_end_with(url, mime_tables[index].name))
        {
            return mime_tables[index].type;
        }

        index++;
    }

    /* return text/html as default */
    return mime_tables[1].type;
}

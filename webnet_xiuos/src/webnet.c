/*
 * File      : webnet.c
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
 * Date           Author                    Notes
 * 2022-05-09     chunyexixiaoyu      the version from rt-thread 
 */


#include <transform.h>
#include <stdint.h>
#include <webnet.h>
#include <wn_module.h>

#ifdef  ADD_XIZI_FETURES
//#if defined(RT_USING_LWIP) && (RT_LWIP_TCPTHREAD_STACKSIZE < 1408)
//#error The lwIP tcpip thread stack size(RT_LWIP_TCPTHREAD_STACKSIZE) must more than 1408
//#endif  //defined(RT_USING_LWIP) && (RT_LWIP_TCPTHREAD_STACKSIZE < 1408)

#if defined(BSP_USING_LWIP) && (LWIP_TASK_STACK_SIZE < 1408)
#error The lwIP tcpip thread stack size() can not less than 4096
#endif  //defined(RT_USING_LWIP) && (LWIP_TASK_STACK_SIZE < 1408)


#endif //ADD_XIZI_FETURES



/*
other os kernel need to notice the point about lwip thread stack.
*/

static uint8 webnet_port = WEBNET_PORT;
static char webnet_root[64] = WEBNET_ROOT;
static bool init_ok = FALSE;

void webnet_set_port(int port)
{
    assert(init_ok == FALSE);
    webnet_port = port;
}

int webnet_get_port(void)
{
    return webnet_port;
}

void webnet_set_root(const char* webroot_path)
{
    strncpy(webnet_root, webroot_path, sizeof(webnet_root) - 1);
    webnet_root[sizeof(webnet_root) - 1] = '\0';
}

const char* webnet_get_root(void)
{
    return webnet_root;
}

/**
 * webnet thread entry
 */
static void webnet_thread(void *parameter)
{
    int listenfd = -1;
    fd_set readset, tempfds;
    fd_set writeset, tempwrtfds;
    int sock_fd, maxfdp1;
    struct sockaddr_in webnet_saddr;
    struct timeval rcv_to = {0, 50000};

    /* First acquire our socket for listening for connections */
    listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenfd < 0)
    {
        printf("Create socket failed.");
        goto __exit;
    }

    memset(&webnet_saddr, 0, sizeof(webnet_saddr));
    webnet_saddr.sin_family = AF_INET;
    webnet_saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    webnet_saddr.sin_port = htons(webnet_port); /* webnet server port */

    /* Set receive timeout for accept() */
    if(setsockopt(listenfd, SOL_SOCKET, SO_RCVTIMEO, (void*)&rcv_to, sizeof(rcv_to)) == -1)
    {
        printf("Set SO_RCVTIMEO failed, errno=%d\n", errno);
        goto __exit;
    }

    if (bind(listenfd, (struct sockaddr *) &webnet_saddr, sizeof(webnet_saddr)) == -1)
    {
        printf("Bind socket failed, errno=%d\n", errno);
        goto __exit;
    }

    /* Put socket into listening mode */
    if (listen(listenfd, WEBNET_CONN_MAX) == -1)
    {
        printf("Socket listen(%d) failed.", WEBNET_CONN_MAX);
        goto __exit;
    }

    /* initialize module (no session at present) */
    webnet_module_handle_event(NULL, WEBNET_EVENT_INIT);

    /* Wait forever for network input: This could be connections or data */
    for (;;)
    {
        /* Determine what sockets need to be in readset */
        FD_ZERO(&readset);
        FD_ZERO(&writeset);
        FD_SET(listenfd, &readset);

        /* set fds in each sessions */
        maxfdp1 = webnet_sessions_set_fds(&readset, &writeset);
        if (maxfdp1 < listenfd + 1)
        {
            maxfdp1 = listenfd + 1;
        }

        /* use temporary fd set in select */
        tempfds = readset;
        tempwrtfds = writeset;
        /* Wait for data or a new connection */
        sock_fd = select(maxfdp1, &tempfds, &tempwrtfds, 0, 0);
        if (sock_fd == 0)
        {
            continue;
        }

        /* At least one descriptor is ready */
        if (FD_ISSET(listenfd, &tempfds))
        {
            struct webnet_session* accept_session;
            /* We have a new connection request */
            accept_session = webnet_session_create(listenfd);
            if (accept_session == NULL)
            {
                /* create session failed, just accept and then close */
                int sock;
                struct sockaddr cliaddr;
                socklen_t clilen;

                clilen = sizeof(struct sockaddr_in);
                sock = accept(listenfd, &cliaddr, &clilen);
                if (sock >= 0)
                {
                    closesocket(sock);
                }
            }
            else
            {
                /* add read fdset */
                FD_SET(accept_session->socket, &readset);
            }
        }

        webnet_sessions_handle_fds(&tempfds, &writeset);
    }

__exit:
    if (listenfd >= 0)
    {
        closesocket(listenfd);
    }
}

int webnet_init(void)
{
    int result = 0;
    pthread_t tid;
    pthread_attr_t attr;
    struct sched_param prio;
    prio.sched_priority = WEBNET_PRIORITY;
    size_t stack_size = WEBNET_THREAD_STACKSIZE;
    pthread_attr_init(&attr);
    pthread_attr_setschedparam(&attr, &prio); 
    pthread_attr_setstacksize(&attr, stack_size);
    if (init_ok == TRUE)
    {
        printf("XiUOS webnet package is already initialized.");
        return 0;
    }
    result = pthread_create(&tid, &attr, webnet_thread, NULL);
    if (0 == result)
    {
        init_ok = TRUE;
        printf("XiUOS webnet initialize success.");
    }
    else
    {
        printf("XiUOS webnet  initialize failed.");
        return -1;
    }

    return 0;
}

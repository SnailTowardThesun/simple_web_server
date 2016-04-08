/*
The MIT License (MIT)

Copyright (c) 2016 ME_Kun_Han

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "simple_web_core.h"
#include "../kernel/simple_web_kernel_sources_control.h"
#include <st.h>
#include <signal.h>
#include <cstdlib>

static st_netfd_t sig_pipe[2];

std::string get_version()
{
    return SIMPLE_WEB_SERVER_NAME;
}

static void Signal(int sig, void (*handler)(int))
{
  struct sigaction sa;

  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(sig, &sa, NULL);
}

static void child_sighandler(int signo)
{
    int err, fd;

    err = errno;
    fd = st_netfd_fileno(sig_pipe[1]);

    /* write() is async-safe */
    if (write(fd, &signo, sizeof(int)) != sizeof(int)) {
        simple_web_app_log::log("error", "simple_web_core.cpp", "write failed");
        exit(0);
    }
    errno = err;
}
static void install_sighandlers(void)
{
    sigset_t mask;
    int p[2];

    /* Create signal pipe */
    if (pipe(p) < 0)
        simple_web_app_log::log("error", "simple_web_core.cpp", "create signal pip failed");
    if ((sig_pipe[0] = st_netfd_open(p[0])) == NULL ||
        (sig_pipe[1] = st_netfd_open(p[1])) == NULL) {
        simple_web_app_log::log("error", "simple_web_core.cpp", "create signal pip failed");
        exit(0);
    }

    /* Install signal handlers */
    Signal(SIGTERM, child_sighandler);  /* terminate */
    Signal(SIGHUP,  child_sighandler);  /* restart   */
    Signal(SIGUSR1, child_sighandler);  /* dump info */

    /* Unblock signals */
    sigemptyset(&mask);
    sigaddset(&mask, SIGTERM);
    sigaddset(&mask, SIGHUP);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
}

long simple_web_initialize(std::string base_folder_path)
{
    // initialize the source control
    if (SimpleWebKernelSourcesCtl::getInstance()->initialize(base_folder_path) != RESULT_OK) {
        simple_web_app_log::log("help", "simple_web_core.cpp", "SimpleWebKernelSourcesCtl initialize failed");
        return RESULT_ERROR;
    }
    // initialize the st library
    st_set_eventsys(ST_EVENTSYS_ALT);
    if (st_init() < 0) {
        simple_web_app_log::log("help", "simple_web_core.cpp", "state thread initialize failed");
        return RESULT_ERROR;
    }
    std::cout<<"get event's name "<<st_get_eventsys_name()<<std::endl;
    //initialize the signal
    install_sighandlers();
    return RESULT_OK;
}

void *process_signals(void *arg)
{
    int signo;

    for ( ; ; ) {
        /* Read the next signal from the signal pipe */
        if (st_read(sig_pipe[0], &signo, sizeof(int),
                    ST_UTIME_NO_TIMEOUT) != sizeof(int)) {
            simple_web_app_log::log("error", "simple_web_core.cpp", "st_read failed");
            exit(0);
        }
        switch (signo) {
            case SIGHUP:
                break;
            case SIGTERM:
                /*
                 * Terminate ungracefully since it is generally not known how long
                 * it will take to gracefully complete all client sessions.
                 */
                exit(0);
            case SIGUSR1:
                break;
            default:
                break;
        }
    }
    return NULL;
}

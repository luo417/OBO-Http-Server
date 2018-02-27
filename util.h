#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     //for getopt, fork
#include <string.h>     //for strcat
//for struct evkeyvalq
#include <sys/queue.h>
#include <event.h>
//for http
//#include <evhttp.h>
#include <event2/http.h>
#include <event2/http_struct.h>
#include <event2/http_compat.h>
#include <event2/util.h>
#include <signal.h>
#include <cJSON.h>

#define MYHTTPD_SIGNATURE   "MoCarHttpd v0.1"

//登录模块
void login_handler(struct evhttp_request *req, void *arg);

//注册模块
void reg_handler(struct evhttp_request *req, void *arg);

#endif

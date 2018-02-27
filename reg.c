#include "util.h"

//处理reg登陆模块
void reg_handler(struct evhttp_request *req, void *arg) 
{
    printf("get connection!\n");

    //获取客户端请求的URI(使用evhttp_request_uri或直接req->uri)
    const char *uri;
    uri = evhttp_request_uri(req);
    printf("[uri]=%s\n", uri);


    //获取POST方法的数据
    size_t post_size = EVBUFFER_LENGTH(req->input_buffer);
    char *request_data = (char *) EVBUFFER_DATA(req->input_buffer);
    char request_data_buf[4096] = {0};
    memcpy(request_data_buf, request_data, post_size);
    printf("[post_data]=\n%s\n", request_data_buf);


    /*
     * json:
     *
     * {
     *   "username" : "gailun",
     *   "psd" :"123",
     *   "driver" : "yes"
     * }
     * */

    cJSON *root = cJSON_Parse(request_data_buf);

    printf("username = %s\n", cJSON_GetObjectItem(root, "username")->valuestring);
    printf("psd = %s\n", cJSON_GetObjectItem(root, "psd")->valuestring);
    printf("isDriver = %s\n", cJSON_GetObjectItem(root, "isDriver")->valuestring);

    
    //写入数据库 ...

    //注册成功 返回ok

    /*
       {
            "result" :"ok"
       } 

       {
            "result" :"error",
            "reason" :"...."
       } 
     
     
     */
    cJSON *response_root = cJSON_CreateObject();

    cJSON_AddStringToObject(response_root, "result", "ok");


    cJSON_Delete(root);

    char *response_data = NULL;

    response_data = cJSON_Print(response_root);

    /* 输出到客户端 */
    //HTTP header
    evhttp_add_header(req->output_headers, "Server", MYHTTPD_SIGNATURE);
    evhttp_add_header(req->output_headers, "Content-Type", "text/plain; charset=UTF-8");
    evhttp_add_header(req->output_headers, "Connection", "close");

    //输出的内容
    struct evbuffer *buf;
    buf = evbuffer_new();
    evbuffer_add_printf(buf, "%s", response_data);

    //将封装好的evbuffer 发送给客户端
    evhttp_send_reply(req, HTTP_OK, "OK", buf);

    evbuffer_free(buf);

    printf("[response]:\n");
    printf("%s\n", response_data);

    free(response_data);
    cJSON_Delete(response_root);
}


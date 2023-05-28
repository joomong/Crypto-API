#ifndef API_EXCHANGE_H
#define API_EXCHANGE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "curl/curl.h"
#include "openssl/hmac.h"
#include "openssl/sha.h"
#include "libwebsockets.h"
#include "json/json.h"


typedef int (*CB)(Json::Value &json_value);

class Exchange {
    static CURL *curl_;

public:
//    Exchange()
//    {curl_ = curl_easy_init();
//    curl_global_init(CURL_GLOBAL_ALL);
//
//    struct lws_context_creation_info info{};
//    memset(&info,0,sizeof(info));
//
//    info.port = CONTEXT_PORT_NO_LISTEN;
//    info.protocols = protocols;
//    info.gid = -1;
//    info.uid = -1;
//    info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
//
//    context = lws_create_context( &info );
//    }
    static void init();

    static void CurlApi(std::string &url, std::string &result_json);
    static void CurlApiWithHeader(std::string &url,
                                  std::string &result_json,
                                  std::vector<std::string> &extra_http_header,
                                  std::string &post_data,
                                  std::string &action);

    static std::size_t CurlCB(void *content,
                              std::size_t size,
                              std::size_t nmemb,
                              std::string *buffer);
    static void Cleanup();
    static std::string sha256(const char *data);
    static std::string hmac_sha256(const char *data, const char *key);
    static std::string b2a_hex(char *byte_arr, int n);
    static long long GetCurrentMsEpoch();

    // libwebsockets
    static struct lws_context *context;
    static struct lws_protocols protocols[];

    static std::map <struct lws *,CB> handles ;
    static int  event_cb( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len );
    static void connect_endpoint(CB user_cb,const std::string &host,int port,const char* path);
    static void enter_event_loop();
};

#endif//API_EXCHANGE_H

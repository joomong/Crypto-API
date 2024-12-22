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
    // 웹소켓 핸들
    static struct lws_context *context;
    static struct lws_protocols protocols[];

    // wsi -> callback
    static std::map<struct lws*, CB> handles;

    // wsi -> subscribe message (연결 후 전송할 구독 메시지)
    static std::map<struct lws*, std::string> subscribe_messages;

    static void init();
    static void Cleanup();

    // ------- REST -------
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
    
    // ----------- Crypto ----------
    static std::string sha256(const char *data);
    static std::string hmac_sha256(const char *data, const char *key);
    static std::string b2a_hex(char *byte_arr, int n);
    static long long GetCurrentMsEpoch();

    // ------------- Websocket -------
    static int  event_cb( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len );
    static void connect_endpoint(CB user_cb,const std::string &host,int port,const char* path);
    static void connect_endpoint_with_sub(CB user_cb,
                                          const std::string &host,
                                          int port,
                                          const char* path,
                                          const std::string &subscribe_message);
    static void enter_event_loop();
};

#endif//API_EXCHANGE_H

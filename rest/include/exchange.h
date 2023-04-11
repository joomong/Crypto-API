#ifndef API_EXCHANGE_H
#define API_EXCHANGE_H

#include <iostream>
#include <string>
#include <vector>

#include "curl/curl.h"
#include "openssl/hmac.h"
#include "openssl/sha.h"

class Exchange {
    static CURL *curl_;

public:
    Exchange(){curl_global_init(CURL_GLOBAL_ALL);
        curl_ = curl_easy_init();}

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
};

#endif//API_EXCHANGE_H

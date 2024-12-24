// HttpClient.h
#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "json/json.h"

#include <string>
#include <vector>
#include <curl/curl.h>

class HttpClient {
public:
    HttpClient();
    ~HttpClient();

    // GET 요청 수행
    bool Get(const std::string& url, Json::Value& result_json, const std::vector<std::string>& headers = {});

    // POST 요청 수행
    bool Post(const std::string& url, const std::string& post_data, Json::Value& result_json, const std::vector<std::string>& headers = {});

    // DELETE 요청 수행
    bool Delete(const std::string& url, const std::string& delete_data, Json::Value& result_json, const std::vector<std::string>& headers = {});

private:
    CURL* curl_;

    // 응답 데이터를 저장할 콜백 함수
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

    // 요청 수행을 위한 헬퍼 메서드
    bool PerformRequest(const std::string& url, const std::string& method, const std::string& data, Json::Value& result_json, const std::vector<std::string>& headers);
};

#endif // HTTPCLIENT_H

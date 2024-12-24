#include "HttpClient.h"
#include <iostream>
#include <sstream>

HttpClient::HttpClient() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_ = curl_easy_init();
    if (!curl_) {
        std::cerr << "Failed to initialize CURL." << std::endl;
    }
}

HttpClient::~HttpClient() {
    if (curl_) {
        curl_easy_cleanup(curl_);
    }
    curl_global_cleanup();
}

size_t HttpClient::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* str = static_cast<std::string*>(userp);
    if (str) {
        str->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    }
    return 0; // 실패를 나타내기 위해 0 반환
}

bool HttpClient::PerformRequest(const std::string& url, const std::string& method, const std::string& data, Json::Value& result_json, const std::vector<std::string>& headers) {
    if (!curl_) {
        std::cerr << "CURL not initialized." << std::endl;
        return false;
    }

    CURLcode res;
    std::string readBuffer;
    struct curl_slist* chunk = NULL;

    // URL 설정
    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());

    // 메서드별 옵션 설정
    if (method == "POST") {
        curl_easy_setopt(curl_, CURLOPT_POST, 1L);
        curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, data.c_str());
    }
    else if (method == "DELETE") {
        curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, data.c_str());
    }
    else {
        curl_easy_setopt(curl_, CURLOPT_HTTPGET, 1L);
    }

    // 헤더 설정
    for (const auto& header : headers) {
        chunk = curl_slist_append(chunk, header.c_str());
    }
    if (!headers.empty()) {
        curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, chunk);
    }

    // 응답 콜백 함수 설정
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &readBuffer);

    // 요청 수행
    res = curl_easy_perform(curl_);

    // 헤더 정리
    if (chunk) {
        curl_slist_free_all(chunk);
    }

    if (res != CURLE_OK) {
        std::cerr << "CURL request failed: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    // JSON 응답 파싱
    Json::CharReaderBuilder readerBuilder;
    std::string errs;
    std::istringstream ss(readBuffer);
    if (!Json::parseFromStream(readerBuilder, ss, &result_json, &errs)) {
        std::cerr << "JSON Parsing Error: " << errs << std::endl;
        return false;
    }

    return true;
}

bool HttpClient::Get(const std::string& url, Json::Value& result_json, const std::vector<std::string>& headers) {
    return PerformRequest(url, "GET", "", result_json, headers);
}

bool HttpClient::Post(const std::string& url, const std::string& post_data, Json::Value& result_json, const std::vector<std::string>& headers) {
    return PerformRequest(url, "POST", post_data, result_json, headers);
}

bool HttpClient::Delete(const std::string& url, const std::string& delete_data, Json::Value& result_json, const std::vector<std::string>& headers) {
    return PerformRequest(url, "DELETE", delete_data, result_json, headers);
}

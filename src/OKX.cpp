// OKX.cpp
#include "OKX.h"
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iostream>

// Sandbox 및 Production URL 상수
#define OKX_PRODUCTION_REST_URL "https://www.okx.com"
#define OKX_SANDBOX_REST_URL "https://aws.okx.com"

// 생성자
OKX::OKX(const std::string &api_key,
         const std::string &api_secret,
         const std::string &passphrase,
         bool sandbox)
    : api_key_(api_key), api_secret_(api_secret), passphrase_(passphrase), use_sandbox_(sandbox), http_client_() {}

// 소멸자
OKX::~OKX() {}

// 헬퍼 메서드
std::string OKX::getHost() const {
    return use_sandbox_ ? OKX_SANDBOX_REST_URL : OKX_PRODUCTION_REST_URL;
}

// 공개 API 메서드 구현

void OKX::GetServerTime(Json::Value &result_json) {
    std::string url = getHost() + "/api/v5/public/time";
    http_client_.Get(url, result_json);
}

void OKX::GetExchangeInfo(const std::string &instrument_id, Json::Value &result_json) {
    std::string url = getHost() + "/api/v5/public/instruments?instId=" + instrument_id;
    http_client_.Get(url, result_json);
}

void OKX::GetOrderBook(const std::string &instrument_id, int size, Json::Value &result_json) {
    std::string url = getHost() + "/api/v5/market/books?instId=" + instrument_id + "&sz=" + std::to_string(size);
    http_client_.Get(url, result_json);
}

void OKX::GetRecentTrades(const std::string &instrument_id, int limit, Json::Value &result_json) {
    std::string url = getHost() + "/api/v5/market/trades?instId=" + instrument_id + "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void OKX::GetKlines(const std::string &instrument_id, const std::string &granularity, int limit, Json::Value &result_json) {
    std::string url = getHost() + "/api/v5/market/candles?instId=" + instrument_id +
                      "&bar=" + granularity + "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

// Private API 메서드 구현

void OKX::PostLimitOrder(const std::string &instrument_id,
                         const std::string &side,
                         const std::string &type,
                         double size,
                         double price,
                         Json::Value &json_result,
                         const std::string &client_order_id)
{
    std::string url = getHost() + "/api/v5/trade/order";
    std::string method = "POST";
    std::string request_path = "/api/v5/trade/order";

    // JSON 바디 생성
    Json::Value order;
    order["instId"] = instrument_id;
    order["side"] = side; // "buy" 또는 "sell"
    order["ordType"] = type; // "limit"
    order["sz"] = std::to_string(size);
    order["px"] = std::to_string(price);
    order["clOrdId"] = client_order_id;
    order["tdMode"] = "cash"; // "cross" 등
    order["tag"] = "api_order"; // 선택적

    // JSON을 문자열로 변환
    Json::StreamWriterBuilder writer;
    std::string body = Json::writeString(writer, order);

    // 타임스탬프 및 서명 생성
    std::string timestamp = Utils::GetCurrentMsEpoch();
    std::string signature = Utils::hmac_sha256(method + request_path + body + timestamp, api_secret_);

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);
    extra_http_header.emplace_back("Content-Type: application/json");

    // POST 요청 수행
    http_client_.Post(url, body, json_result, extra_http_header);
}

void OKX::PostMarketOrder(const std::string &instrument_id,
                          const std::string &side,
                          const std::string &type,
                          double size,
                          Json::Value &json_result,
                          const std::string &client_order_id)
{
    std::string url = getHost() + "/api/v5/trade/order";
    std::string method = "POST";
    std::string request_path = "/api/v5/trade/order";

    // JSON 바디 생성
    Json::Value order;
    order["instId"] = instrument_id;
    order["side"] = side; // "buy" 또는 "sell"
    order["ordType"] = type; // "market"
    order["sz"] = std::to_string(size);
    order["clOrdId"] = client_order_id;
    order["tdMode"] = "cash"; // "cross" 등
    order["tag"] = "api_order"; // 선택적

    // JSON을 문자열로 변환
    Json::StreamWriterBuilder writer;
    std::string body = Json::writeString(writer, order);

    // 타임스탬프 및 서명 생성
    std::string timestamp = Utils::GetCurrentMsEpoch(); // OKX는 ISO 8601 형식을 요구할 수 있음. 필요시 수정
    std::string signature = Utils::hmac_sha256(method + request_path + body + timestamp, api_secret_);

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);
    extra_http_header.emplace_back("Content-Type: application/json");

    // POST 요청 수행
    http_client_.Post(url, body, json_result, extra_http_header);
}

void OKX::CancelOrder(const std::string &instrument_id,
                      const std::string &order_id,
                      Json::Value &json_result)
{
    std::string url = getHost() + "/api/v5/trade/cancel-order";
    std::string method = "POST";
    std::string request_path = "/api/v5/trade/cancel-order";

    // JSON 바디 생성
    Json::Value cancel_order;
    cancel_order["instId"] = instrument_id;
    cancel_order["ordId"] = order_id;
    // "clOrdId" 사용 시 아래와 같이 설정
    // cancel_order["clOrdId"] = client_order_id;

    // JSON을 문자열로 변환
    Json::StreamWriterBuilder writer;
    std::string body = Json::writeString(writer, cancel_order);

    // 타임스탬프 및 서명 생성
    std::string timestamp = Utils::GetCurrentMsEpoch(); // OKX는 ISO 8601 형식을 요구할 수 있음. 필요시 수정
    std::string signature = Utils::hmac_sha256(method + request_path + body + timestamp, api_secret_);

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);
    extra_http_header.emplace_back("Content-Type: application/json");

    // POST 요청 수행
    http_client_.Post(url, body, json_result, extra_http_header);
}

void OKX::CancelAllOrders(const std::string &instrument_id,
                           Json::Value &json_result)
{
    std::string url = getHost() + "/api/v5/trade/cancel-all-orders";
    std::string method = "POST";
    std::string request_path = "/api/v5/trade/cancel-all-orders";

    // JSON 바디 생성
    Json::Value cancel_all;
    cancel_all["instId"] = instrument_id;
    // "ordType" 등 추가 필드 설정 가능

    // JSON을 문자열로 변환
    Json::StreamWriterBuilder writer;
    std::string body = Json::writeString(writer, cancel_all);

    // 타임스탬프 및 서명 생성
    std::string timestamp = Utils::GetCurrentMsEpoch(); // OKX는 ISO 8601 형식을 요구할 수 있음. 필요시 수정
    std::string signature = Utils::hmac_sha256(method + request_path + body + timestamp, api_secret_);

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);
    extra_http_header.emplace_back("Content-Type: application/json");

    // POST 요청 수행
    http_client_.Post(url, body, json_result, extra_http_header);
}

void OKX::GetCurrentOpenOrders(const std::string &instrument_id, Json::Value &json_result) {
    std::string url = getHost() + "/api/v5/trade/orders-pending?instId=" + instrument_id;
    std::string method = "GET";
    std::string request_path = "/api/v5/trade/orders-pending?instId=" + instrument_id;
    std::string body = ""; // GET 요청에는 바디가 없음

    // 타임스탬프 및 서명 생성
    std::string timestamp = Utils::GetCurrentMsEpoch(); // OKX는 ISO 8601 형식을 요구할 수 있음. 필요시 수정
    std::string signature = Utils::hmac_sha256(method + request_path + body + timestamp, api_secret_);

    // 서명을 URL에 추가
    url += "&signature=" + signature;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);

    // GET 요청 수행
    http_client_.Get(url, json_result, extra_http_header);
}

void OKX::GetOrders(const std::string &instrument_id,
                   Json::Value &result_json,
                   long orderId,
                   long startTime,
                   long endTime,
                   long limit,
                   long recvWindow)
{
    std::string url = getHost() + "/api/v5/trade/orders-history?instId=" + instrument_id;
    std::string method = "GET";
    std::string request_path = "/api/v5/trade/orders-history?instId=" + instrument_id;
    std::string body = ""; // GET 요청에는 바디가 없음

    // 선택적 쿼리 파라미터 추가
    std::string querystring = "";
    if (orderId > 0) {
        querystring += "&ordId=" + std::to_string(orderId);
    }
    if (startTime > 0) {
        querystring += "&after=" + std::to_string(startTime);
    }
    if (endTime > 0) {
        querystring += "&before=" + std::to_string(endTime);
    }
    if (limit > 0) {
        querystring += "&limit=" + std::to_string(limit);
    }
    if (recvWindow > 0) {
        querystring += "&recvWindow=" + std::to_string(recvWindow);
    }

    request_path += querystring;
    url += querystring;

    // 타임스탬프 및 서명 생성
    std::string timestamp = Utils::GetCurrentMsEpoch(); // OKX는 ISO 8601 형식을 요구할 수 있음. 필요시 수정
    std::string signature = Utils::hmac_sha256(method + request_path + body + timestamp, api_secret_);

    // 서명을 URL에 추가
    url += "&signature=" + signature;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);

    // GET 요청 수행
    http_client_.Get(url, result_json, extra_http_header);
}

void OKX::GetAccountInfo(Json::Value &result_json) {
    std::string url = getHost() + "/api/v5/account/balance";
    std::string method = "GET";
    std::string request_path = "/api/v5/account/balance";
    std::string body = ""; // GET 요청에는 바디가 없음

    // 타임스탬프 및 서명 생성
    std::string timestamp = Utils::GetCurrentMsEpoch(); // OKX는 ISO 8601 형식을 요구할 수 있음. 필요시 수정
    std::string signature = Utils::hmac_sha256(method + request_path + body + timestamp, api_secret_);

    // 서명을 URL에 추가
    url += "?signature=" + signature;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);

    // GET 요청 수행
    http_client_.Get(url, result_json, extra_http_header);
}

void OKX::GetUserStreamKey(Json::Value &json_result) {
    std::string url = getHost() + "/api/v5/userDataStream";
    std::string method = "POST";
    std::string request_path = "/api/v5/userDataStream";
    std::string body = ""; // 일부 엔드포인트는 바디가 필요할 수 있음. 문서 참조

    // 타임스탬프 및 서명 생성
    std::string timestamp = Utils::GetCurrentMsEpoch(); // OKX는 ISO 8601 형식을 요구할 수 있음. 필요시 수정
    std::string signature = Utils::hmac_sha256(method + request_path + body + timestamp, api_secret_);

    // 서명을 URL에 추가 (API 문서에 따라 다를 수 있음)
    url += "?signature=" + signature;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);
    extra_http_header.emplace_back("Content-Type: application/json");

    // POST 요청 수행
    http_client_.Post(url, body, json_result, extra_http_header);
}

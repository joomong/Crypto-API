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

void OKX::GetExchangeInfo(const std::string &instType,Json::Value &result_json, const std::string &instId) {
    std::string url = getHost() + "/api/v5/public/instruments?instType=" + instType;
    if (!instId.empty()) {
        url += "&instId=" + instId;
    }

    if (!http_client_.Get(url, result_json)) {
        std::cerr << "Failed to retrieve exchange info for instType: " << instType;
        if (!instId.empty()) {
            std::cerr << ", instId: " << instId;
        }
        std::cerr << std::endl;
    }
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


// Private methods
void OKX::PostLimitOrder(const std::string &instId,
                         const std::string &side,
                         const std::string &ordType,
                         const std::string &sz,
                         const std::string &px,
                         Json::Value &json_result,
                         const std::string &clOrdId,
                         const std::string &posSide,
                         const std::string &tdMode)
{
    std::string url = getHost() + "/api/v5/trade/order";
    std::string method = "POST";
    std::string request_path = "/api/v5/trade/order";

    // JSON 바디 생성
    Json::Value order;
    order["instId"] = instId;
    order["side"] = side;
    order["ordType"] = ordType;
    order["sz"] = sz;
    order["px"] = px;
    if (!clOrdId.empty()) {
        order["clOrdId"] = clOrdId;
    }
    order["posSide"] = posSide;
    order["tdMode"] = tdMode;

    // JSON을 문자열로 변환
    Json::StreamWriterBuilder writer;
    std::string body = Json::writeString(writer, order);

    // 타임스탬프 생성 (ISO 8601 형식)
    std::string timestamp = Utils::GetCurrentTimestamp();

    // 서명 생성: timestamp + method + request_path + body
    std::string to_sign = timestamp + method + request_path + body;
    std::string signature = Utils::hmac_sha256(to_sign, api_secret_);

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);
    extra_http_header.emplace_back("Content-Type: application/json");

    // POST 요청 수행
    if (!http_client_.Post(url, body, json_result, extra_http_header)) {
        std::cerr << "Failed to place limit order for instrument: " << instId << std::endl;
    }
}

// PostBatchOrders 함수
void OKX::PostBatchOrders(const std::vector<std::vector<std::string>> &orders, Json::Value &json_result)
{
    if (orders.empty() || orders.size() > 20) {
        std::cerr << "Batch orders must contain between 1 and 20 orders." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v5/trade/batch-orders";
    std::string method = "POST";
    std::string request_path = "/api/v5/trade/batch-orders";

    // JSON 바디 생성
    Json::Value orders_json(Json::arrayValue);
    for (const auto &order : orders) {
        if (order.size() < 5) {
            std::cerr << "Each order must have at least 5 parameters: instId, side, ordType, sz, px." << std::endl;
            continue;
        }
        Json::Value order_json;
        order_json["instId"] = order[0];
        order_json["side"] = order[1];
        order_json["ordType"] = order[2];
        order_json["sz"] = order[3];
        order_json["px"] = order[4];
        if (order.size() >= 6 && !order[5].empty()) {
            order_json["clOrdId"] = order[5];
        }
        if (order.size() >= 7 && !order[6].empty()) {
            order_json["posSide"] = order[6];
        }
        if (order.size() >= 8 && !order[7].empty()) {
            order_json["tdMode"] = order[7];
        }
        orders_json.append(order_json);
    }

    // JSON을 문자열로 변환
    Json::StreamWriterBuilder writer;
    std::string body = Json::writeString(writer, orders_json);

    // 타임스탬프 생성 (ISO 8601 형식)
    std::string timestamp = Utils::GetCurrentTimestamp();

    // 서명 생성: timestamp + method + request_path + body
    std::string to_sign = timestamp + method + request_path + body;
    std::string signature = Utils::hmac_sha256(to_sign, api_secret_);

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);
    extra_http_header.emplace_back("Content-Type: application/json");

    // POST 요청 수행
    if (!http_client_.Post(url, body, json_result, extra_http_header)) {
        std::cerr << "Failed to place batch orders." << std::endl;
    }
}

// CancelOrder 함수
void OKX::CancelOrder(const std::string &instId,
                    Json::Value &json_result,
                    const std::string &ordId,
                    const std::string &clOrdId)
{
    if (ordId.empty() && clOrdId.empty()) {
        std::cerr << "Either ordId or clOrdId must be provided to cancel an order." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v5/trade/cancel-order";
    std::string method = "POST";
    std::string request_path = "/api/v5/trade/cancel-order";

    // JSON 바디 생성
    Json::Value cancel_json;
    cancel_json["instId"] = instId;
    if (!ordId.empty()) {
        cancel_json["ordId"] = ordId;
    }
    if (!clOrdId.empty()) {
        cancel_json["clOrdId"] = clOrdId;
    }

    // JSON을 문자열로 변환
    Json::StreamWriterBuilder writer;
    std::string body = Json::writeString(writer, cancel_json);

    // 타임스탬프 생성 (ISO 8601 형식)
    std::string timestamp = Utils::GetCurrentTimestamp();

    // 서명 생성: timestamp + method + request_path + body
    std::string to_sign = timestamp + method + request_path + body;
    std::string signature = Utils::hmac_sha256(to_sign, api_secret_);

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);
    extra_http_header.emplace_back("Content-Type: application/json");

    // POST 요청 수행
    if (!http_client_.Post(url, body, json_result, extra_http_header)) {
        std::cerr << "Failed to cancel order for instrument: " << instId << std::endl;
    }
}

// CancelBatchOrders 함수
void OKX::CancelBatchOrders(const std::vector<std::vector<std::string>> &orders, Json::Value &json_result)
{
    if (orders.empty() || orders.size() > 20) {
        std::cerr << "Batch cancel orders must contain between 1 and 20 orders." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v5/trade/cancel-batch-orders";
    std::string method = "POST";
    std::string request_path = "/api/v5/trade/cancel-batch-orders";

    // JSON 바디 생성
    Json::Value cancels_json(Json::arrayValue);
    for (const auto &order : orders) {
        if (order.size() < 2) {
            std::cerr << "Each cancel order must have at least 2 parameters: instId, ordId." << std::endl;
            continue;
        }
        Json::Value cancel_json;
        cancel_json["instId"] = order[0];
        cancel_json["ordId"] = order[1];
        if (order.size() >= 3 && !order[2].empty()) {
            cancel_json["clOrdId"] = order[2];
        }
        cancels_json.append(cancel_json);
    }

    // JSON을 문자열로 변환
    Json::StreamWriterBuilder writer;
    std::string body = Json::writeString(writer, cancels_json);

    // 타임스탬프 생성 (ISO 8601 형식)
    std::string timestamp = Utils::GetCurrentTimestamp();

    // 서명 생성: timestamp + method + request_path + body
    std::string to_sign = timestamp + method + request_path + body;
    std::string signature = Utils::hmac_sha256(to_sign, api_secret_);

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);
    extra_http_header.emplace_back("Content-Type: application/json");

    // POST 요청 수행
    if (!http_client_.Post(url, body, json_result, extra_http_header)) {
        std::cerr << "Failed to cancel batch orders." << std::endl;
    }
}

// AmendOrder 함수
void OKX::AmendOrder(const std::string &instId,
                     const std::string &ordId,
                     const std::string &newSz,
                     const std::string &newPx,
                     Json::Value &json_result,
                     const std::string &clOrdId,
                     bool cxlOnFail)
{
    if (ordId.empty()) {
        std::cerr << "ordId must be provided to amend an order." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v5/trade/amend-order";
    std::string method = "POST";
    std::string request_path = "/api/v5/trade/amend-order";

    // JSON 바디 생성
    Json::Value amend_json;
    amend_json["instId"] = instId;
    amend_json["ordId"] = ordId;
    amend_json["newSz"] = newSz;
    amend_json["newPx"] = newPx;
    if (!clOrdId.empty()) {
        amend_json["clOrdId"] = clOrdId;
    }
    amend_json["cxlOnFail"] = cxlOnFail ? "true" : "false";

    // JSON을 문자열로 변환
    Json::StreamWriterBuilder writer;
    std::string body = Json::writeString(writer, amend_json);

    // 타임스탬프 생성 (ISO 8601 형식)
    std::string timestamp = Utils::GetCurrentTimestamp();

    // 서명 생성: timestamp + method + request_path + body
    std::string to_sign = timestamp + method + request_path + body;
    std::string signature = Utils::hmac_sha256(to_sign, api_secret_);

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);
    extra_http_header.emplace_back("Content-Type: application/json");

    // POST 요청 수행
    if (!http_client_.Post(url, body, json_result, extra_http_header)) {
        std::cerr << "Failed to amend order for instrument: " << instId << std::endl;
    }
}

// AmendBatchOrders 함수
void OKX::AmendBatchOrders(const std::vector<std::vector<std::string>> &orders, Json::Value &json_result)
{
    if (orders.empty() || orders.size() > 20) {
        std::cerr << "Batch amend orders must contain between 1 and 20 orders." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v5/trade/amend-batch-orders";
    std::string method = "POST";
    std::string request_path = "/api/v5/trade/amend-batch-orders";

    // JSON 바디 생성
    Json::Value amends_json(Json::arrayValue);
    for (const auto &order : orders) {
        if (order.size() < 4) {
            std::cerr << "Each amend order must have at least 4 parameters: instId, ordId, newSz, newPx." << std::endl;
            continue;
        }
        Json::Value amend_json;
        amend_json["instId"] = order[0];
        amend_json["ordId"] = order[1];
        amend_json["newSz"] = order[2];
        amend_json["newPx"] = order[3];
        if (order.size() >= 5 && !order[4].empty()) {
            amend_json["clOrdId"] = order[4];
        }
        if (order.size() >= 6) {
            bool cxlOnFail = (order[5] == "true") ? true : false;
            amend_json["cxlOnFail"] = cxlOnFail ? "true" : "false";
        }
        amends_json.append(amend_json);
    }

    // JSON을 문자열로 변환
    Json::StreamWriterBuilder writer;
    std::string body = Json::writeString(writer, amends_json);

    // 타임스탬프 생성 (ISO 8601 형식)
    std::string timestamp = Utils::GetCurrentTimestamp();

    // 서명 생성: timestamp + method + request_path + body
    std::string to_sign = timestamp + method + request_path + body;
    std::string signature = Utils::hmac_sha256(to_sign, api_secret_);

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("OK-ACCESS-KEY: " + api_key_);
    extra_http_header.emplace_back("OK-ACCESS-SIGN: " + signature);
    extra_http_header.emplace_back("OK-ACCESS-TIMESTAMP: " + timestamp);
    extra_http_header.emplace_back("OK-ACCESS-PASSPHRASE: " + passphrase_);
    extra_http_header.emplace_back("Content-Type: application/json");

    // POST 요청 수행
    if (!http_client_.Post(url, body, json_result, extra_http_header)) {
        std::cerr << "Failed to amend batch orders." << std::endl;
    }
}

void OKX::GetCurrentOpenOrders(const std::string &instrument_id, Json::Value &json_result) {
    std::string url = getHost() + "/api/v5/trade/orders-pending?instId=" + instrument_id;
    std::string method = "GET";
    std::string request_path = "/api/v5/trade/orders-pending?instId=" + instrument_id;
    std::string body = ""; // GET 요청에는 바디가 없음

    // 타임스탬프 및 서명 생성
    std::string timestamp = Utils::GetCurrentTimestamp();
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

void OKX::GetAccountInfo(Json::Value &result_json) {
    std::string url = getHost() + "/api/v5/account/balance";
    std::string method = "GET";
    std::string request_path = "/api/v5/account/balance";
    std::string body = ""; // GET 요청에는 바디가 없음

    // 타임스탬프 및 서명 생성
    std::string timestamp = Utils::GetCurrentTimestamp();
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
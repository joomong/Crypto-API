// Hashkey.cpp
#include "Hashkey.h"
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iostream>

// 생성자
Hashkey::Hashkey(const std::string &api_key, const std::string &api_secret)
    : api_key_(api_key), api_secret_(api_secret), http_client_() {}

// 소멸자
Hashkey::~Hashkey() {}

// 공개 API 메서드 구현
void Hashkey::GetServerTime(Json::Value &result_json) {
    std::string url = PRODUCTION_REST_URL + "/api/v1/time";
    http_client_.Get(url, result_json);
}

void Hashkey::GetExchangeInfo(const std::string &symbol, Json::Value &result_json) {
    std::string url = PRODUCTION_REST_URL + "/api/v1/exchangeInfo?symbol=" + symbol;
    http_client_.Get(url, result_json);
}

void Hashkey::GetOrderBook(const std::string &symbol, int limit, Json::Value &result_json) {
    std::string url = PRODUCTION_REST_URL + "/quote/v1/depth?symbol=" + symbol + "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Hashkey::GetRecentTrades(const std::string &symbol, int limit, Json::Value &result_json) {
    std::string url = PRODUCTION_REST_URL + "/quote/v1/trades?symbol=" + symbol + "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Hashkey::GetKlines(const std::string &symbol, const std::string &interval, int limit, Json::Value &result_json) {
    std::string url = PRODUCTION_REST_URL + "/quote/v1/klines?symbol=" + symbol +
                      "&interval=" + interval + "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

// Private API 메서드 구현
void Hashkey::PostLimitOrder(const std::string &symbol,
                             const std::string &side,
                             double quantity,
                             double price,
                             Json::Value &json_result,
                             const std::string &time_in_force,
                             const std::string &client_order_id)
{
    std::string url = PRODUCTION_REST_URL + "/api/v1/futures/order?";
    
    std::string querystring = "symbol=" + symbol +
                               "&side=" + side +
                               "&timeInForce=" + time_in_force +
                               "&priceType=INPUT" +
                               "&type=LIMIT" +
                               "&quantity=" + std::to_string(quantity) +
                               "&price=" + std::to_string(price) +
                               "&clientOrderId=" + client_order_id +
                               "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("X-HK-APIKEY: " + api_key_);

    std::string post_data = ""; // POST와 함께 쿼리 파라미터 사용

    http_client_.Post(url, post_data, json_result, extra_http_header);
}

void Hashkey::PostMarketOrder(const std::string &symbol,
                              const std::string &side,
                              double quantity,
                              Json::Value &json_result,
                              const std::string &client_order_id)
{
    std::string url = PRODUCTION_REST_URL + "/api/v1/futures/order?";
    
    std::string querystring = "symbol=" + symbol +
                               "&side=" + side +
                               "&type=MARKET" +
                               "&timeInForce=GTC" +
                               "&priceType=MARKET" +
                               "&quantity=" + std::to_string(quantity) +
                               "&clientOrderId=" + client_order_id +
                               "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("X-HK-APIKEY: " + api_key_);

    std::string post_data = ""; // POST와 함께 쿼리 파라미터 사용

    http_client_.Post(url, post_data, json_result, extra_http_header);
}

void Hashkey::CancelOrder(const std::string &symbol,
                          const std::string &order_id,
                          Json::Value &json_result,
                          const std::string &client_order_id)
{
    std::string url = PRODUCTION_REST_URL + "/api/v1/futures/order?";
    
    std::string post_data = "symbol=" + symbol +
                             "&orderId=" + order_id +
                             "&orgClientOrderId=" + client_order_id +
                             "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("X-HK-APIKEY: " + api_key_);

    http_client_.Delete(url, post_data, json_result, extra_http_header);
}

void Hashkey::CancelAllOrders(const std::string &symbol,
                              const std::string &side,
                              Json::Value &json_result)
{
    std::string url = PRODUCTION_REST_URL + "/api/v1/futures/batchOrders?";
    
    std::string post_data = "symbol=" + symbol +
                             "&side=" + side +
                             "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("X-HK-APIKEY: " + api_key_);

    http_client_.Delete(url, post_data, json_result, extra_http_header);
}

void Hashkey::GetCurrentOpenOrders(const std::string &symbol, Json::Value &json_result) {
    std::string url = PRODUCTION_REST_URL + "/api/v1/futures/openOrders?";
    
    std::string querystring = "symbol=" + symbol +
                               "&type=LIMIT" +
                               "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("X-HK-APIKEY: " + api_key_);

    http_client_.Get(url, json_result, extra_http_header);
}

void Hashkey::GetOrders(const std::string &symbol,
                        Json::Value &json_result,
                        long orderId,
                        long startTime,
                        long endTime,
                        long limit,
                        long recvWindow)
{
    std::string url = PRODUCTION_REST_URL + "/api/v1/futures/orders?";
    
    std::string querystring = "symbol=" + symbol +
                               "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (orderId > 0) {
        querystring += "&orderId=" + std::to_string(orderId);
    }
    if (startTime > 0) {
        querystring += "&startTime=" + std::to_string(startTime);
    }
    if (endTime > 0) {
        querystring += "&endTime=" + std::to_string(endTime);
    }
    if (limit > 0) {
        querystring += "&limit=" + std::to_string(limit);
    }
    if (recvWindow > 0) {
        querystring += "&recvWindow=" + std::to_string(recvWindow);
    }

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("X-HK-APIKEY: " + api_key_);

    http_client_.Get(url, json_result, extra_http_header);
}

void Hashkey::GetAccountInfo(Json::Value &json_result) {
    std::string url = PRODUCTION_REST_URL + "/api/v1/account?";
    
    std::string querystring = "timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("X-HK-APIKEY: " + api_key_);

    http_client_.Get(url, json_result, extra_http_header);
}

void Hashkey::GetUserStreamKey(Json::Value &json_result) {
    std::string url = PRODUCTION_REST_URL + "/api/v1/userDataStream?";
    
    std::string querystring = "timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("X-HK-APIKEY: " + api_key_);

    std::string post_data = ""; // POST와 함께 쿼리 파라미터 사용

    http_client_.Post(url, post_data, json_result, extra_http_header);
}

// **추가된 주문 수정 및 배치 주문 관련 메서드 구현**

void Hashkey::AmendOrder(const std::string &symbol,
                         const std::string &order_id,
                         const std::string &new_quantity,
                         const std::string &new_price,
                         Json::Value &json_result,
                         const std::string &client_order_id,
                         bool cancel_on_fail)
{
    if (order_id.empty()) {
        std::cerr << "order_id must be provided to amend an order." << std::endl;
        return;
    }

    std::string url = PRODUCTION_REST_URL + "/api/v1/futures/order/amend?";
    
    std::string post_data = "symbol=" + symbol +
                             "&orderId=" + order_id +
                             "&newQuantity=" + new_quantity +
                             "&newPrice=" + new_price +
                             "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (!client_order_id.empty()) {
        post_data += "&orgClientOrderId=" + client_order_id;
    }

    post_data += "&cancelOnFail=" + std::string(cancel_on_fail ? "true" : "false");

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("X-HK-APIKEY: " + api_key_);

    // POST 요청 수행
    http_client_.Post(url, "", json_result, extra_http_header);
}

void Hashkey::PostBatchOrders(const std::vector<std::vector<std::string>> &orders, Json::Value &json_result)
{
    if (orders.empty() || orders.size() > 20) {
        std::cerr << "Batch orders must contain between 1 and 20 orders." << std::endl;
        return;
    }

    std::string url = PRODUCTION_REST_URL + "/api/v1/futures/batchOrders?";
    std::string post_data = "";

    for (const auto &order : orders) {
        if (order.size() < 5) {
            std::cerr << "Each batch order must have at least 5 parameters: symbol, side, ordType, sz, px." << std::endl;
            continue;
        }
        post_data += "symbol=" + order[0] +
                     "&side=" + order[1] +
                     "&type=" + order[2] +
                     "&quantity=" + order[3] +
                     "&price=" + order[4];
        if (order.size() >= 6 && !order[5].empty()) {
            post_data += "&clientOrderId=" + order[5];
        }
        // posSide 및 tdMode는 기본값으로 설정
        post_data += "&posSide=net&tdMode=isolated&";
    }

    // Remove the trailing '&' if exists
    if (!post_data.empty() && post_data.back() == '&') {
        post_data.pop_back();
    }

    // 서명 생성
    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("X-HK-APIKEY: " + api_key_);

    // POST 요청 수행
    http_client_.Post(url, "", json_result, extra_http_header);
}

void Hashkey::AmendBatchOrders(const std::vector<std::vector<std::string>> &orders, Json::Value &json_result)
{
    if (orders.empty() || orders.size() > 20) {
        std::cerr << "Batch amend orders must contain between 1 and 20 orders." << std::endl;
        return;
    }

    std::string url = PRODUCTION_REST_URL + "/api/v1/futures/batchOrders/amend?";
    std::string post_data = "";

    for (const auto &order : orders) {
        if (order.size() < 4) {
            std::cerr << "Each batch amend order must have at least 4 parameters: symbol, order_id, new_quantity, new_price." << std::endl;
            continue;
        }
        post_data += "symbol=" + order[0] +
                     "&orderId=" + order[1] +
                     "&newQuantity=" + order[2] +
                     "&newPrice=" + order[3];
        if (order.size() >= 5 && !order[4].empty()) {
            post_data += "&orgClientOrderId=" + order[4];
        }
        if (order.size() >= 6) {
            bool cancel_on_fail = (order[5] == "true") ? true : false;
            post_data += "&cancelOnFail=" + std::string(cancel_on_fail ? "true" : "false");
        }
        post_data += "&";
    }

    // Remove the trailing '&' if exists
    if (!post_data.empty() && post_data.back() == '&') {
        post_data.pop_back();
    }

    // 서명 생성
    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    // 헤더 설정
    std::vector<std::string> extra_http_header;
    extra_http_header.emplace_back("X-HK-APIKEY: " + api_key_);

    // POST 요청 수행
    http_client_.Post(url, "", json_result, extra_http_header);
}

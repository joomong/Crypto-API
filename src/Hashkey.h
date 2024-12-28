#ifndef HASHKEY_H
#define HASHKEY_H

#include <string>
#include <vector>
#include <json/json.h>
#include "HttpClient.h"
#include "Utils.h"

class Hashkey {
private:
    std::string api_key_;
    std::string api_secret_;
    inline static const std::string PRODUCTION_REST_URL = "https://api-glb.hashkey.com";

    // HttpClient 객체를 직접 포함
    HttpClient http_client_;

public:
    // 생성자
    Hashkey(const std::string &api_key, const std::string &api_secret);
    
    // 소멸자
    ~Hashkey();

    // 공개 API 메서드
    void GetServerTime(Json::Value &result_json);
    void GetExchangeInfo(const std::string &symbol, Json::Value &result_json);
    void GetOrderBook(const std::string &symbol, int limit, Json::Value &result_json);
    void GetRecentTrades(const std::string &symbol, int limit, Json::Value &result_json);
    void GetKlines(const std::string &symbol, const std::string &interval, int limit, Json::Value &result_json);

    // 주문 관련 메서드
    void PostLimitOrder(const std::string &symbol,
                        const std::string &side,
                        double quantity,
                        double price,
                        Json::Value &json_result,
                        const std::string &time_in_force = "GTC",
                        const std::string &client_order_id = "99999999980001");
    
    void PostMarketOrder(const std::string &symbol,
                         const std::string &side,
                         double quantity,
                         Json::Value &json_result,
                         const std::string &client_order_id = "99999999980001");

    void CancelOrder(const std::string &symbol,
                     const std::string &order_id,
                     Json::Value &json_result,
                     const std::string &client_order_id = "99999999980001");

    void CancelAllOrders(const std::string &symbol,
                         const std::string &side,
                         Json::Value &json_result);

    void GetCurrentOpenOrders(const std::string &symbol, Json::Value &json_result);
    void GetOrders(const std::string &symbol,
                   Json::Value &json_result,
                   long orderId = 0,
                   long startTime = 0,
                   long endTime = 0,
                   long limit = 0,
                   long recvWindow = 0);

    void GetAccountInfo(Json::Value &json_result);
    void GetUserStreamKey(Json::Value &json_result);

    // **추가된 주문 수정 및 배치 주문 관련 메서드**
    
    // 주문 수정
    void AmendOrder(const std::string &symbol,
                   const std::string &order_id,
                   const std::string &new_quantity,
                   const std::string &new_price,
                   Json::Value &json_result,
                   const std::string &client_order_id = "",
                   bool cancel_on_fail = false);
    
    // 배치 주문
    void PostBatchOrders(const std::vector<std::vector<std::string>> &orders, Json::Value &json_result);
    
    // 배치 주문 수정
    void AmendBatchOrders(const std::vector<std::vector<std::string>> &orders, Json::Value &json_result);
};

#endif /* HASHKEY_H */

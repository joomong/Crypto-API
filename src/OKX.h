// OKX.h
#ifndef OKX_H
#define OKX_H

#include <string>
#include "HttpClient.h"
#include "Utils.h"
#include "json/json.h"

class OKX {
private:
    std::string api_key_;
    std::string api_secret_;
    std::string passphrase_;
    bool use_sandbox_; // Sandbox 모드 플래그

    // HttpClient 객체를 직접 포함
    HttpClient http_client_;

    // 헬퍼 메서드
    std::string getHost() const;

public:
    OKX(const std::string &api_key,
        const std::string &api_secret,
        const std::string &passphrase,
        bool sandbox = false);
    ~OKX();

    // 공개 API 메서드
    void GetServerTime(Json::Value &result_json);
    void GetExchangeInfo(const std::string &instrument_id, Json::Value &result_json);
    void GetOrderBook(const std::string &instrument_id, int size, Json::Value &result_json);
    void GetRecentTrades(const std::string &instrument_id, int limit, Json::Value &result_json);
    void GetKlines(const std::string &instrument_id, const std::string &granularity, int limit, Json::Value &result_json);

    // Private API 메서드
    void PostLimitOrder(const std::string &instrument_id,
                        const std::string &side,
                        const std::string &type,
                        double size,
                        double price,
                        Json::Value &json_result,
                        const std::string &client_order_id = "client_order_001");

    void PostMarketOrder(const std::string &instrument_id,
                         const std::string &side,
                         const std::string &type,
                         double size,
                         Json::Value &json_result,
                         const std::string &client_order_id = "client_order_001");

    void CancelOrder(const std::string &instrument_id,
                    const std::string &order_id,
                    Json::Value &json_result);

    void CancelAllOrders(const std::string &instrument_id,
                         Json::Value &json_result);

    void GetCurrentOpenOrders(const std::string &instrument_id, Json::Value &json_result);
    void GetOrders(const std::string &instrument_id,
                  Json::Value &result_json,
                  long orderId = 0,
                  long startTime = 0,
                  long endTime = 0,
                  long limit = 0,
                  long recvWindow = 0);

    void GetAccountInfo(Json::Value &result_json);
    void GetUserStreamKey(Json::Value &json_result);
};

#endif /* OKX_H */

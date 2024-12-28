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
    void GetExchangeInfo(const std::string &instType, Json::Value &result_json, const std::string &instId = "");
    void GetOrderBook(const std::string &instrument_id, int size, Json::Value &result_json);
    void GetRecentTrades(const std::string &instrument_id, int limit, Json::Value &result_json);
    void GetKlines(const std::string &instrument_id, const std::string &granularity, int limit, Json::Value &result_json);

    // Private API 메서드
     void PostLimitOrder(const std::string &instId,
                        const std::string &side,
                        const std::string &ordType,
                        const std::string &sz,
                        const std::string &px,
                        Json::Value &json_result,
                        const std::string &clOrdId = "",
                        const std::string &posSide = "net",
                        const std::string &tdMode = "isolated");

    void PostBatchOrders(const std::vector<std::vector<std::string>> &orders, Json::Value &json_result);

    void CancelOrder(const std::string &instId,
                    Json::Value &json_result,
                     const std::string &ordId = "",
                     const std::string &clOrdId = "");

    void CancelBatchOrders(const std::vector<std::vector<std::string>> &orders, Json::Value &json_result);

    void AmendOrder(const std::string &instId,
                   const std::string &ordId,
                   const std::string &newSz,
                   const std::string &newPx,
                   Json::Value &json_result,
                   const std::string &clOrdId = "",
                   bool cxlOnFail = false);

    void AmendBatchOrders(const std::vector<std::vector<std::string>> &orders, Json::Value &json_result);

    void GetCurrentOpenOrders(const std::string &instrument_id, Json::Value &json_result);

    void GetAccountInfo(Json::Value &result_json);
};

#endif /* OKX_H */

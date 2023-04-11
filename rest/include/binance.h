#ifndef BINANCE_H
#define BINANCE_H

#include <string>

#include "exchange.h"
#include "json/json.h"

#define BINANCE_HOST "https://api.binance.com"

class Binance : public Exchange {
public:
    Binance(std::string &api_key, std::string &api_secret)
        :Exchange(), API_KEY(api_key), API_SECRET(api_secret){};

    //Public API
    static void GetServerTime(Json::Value &result_json);

    static void GetExchangeInfo(Json::Value &result_json);

    static void GetOrderBook(std::string &symbol,
                             int limit,
                             Json::Value &result_json);

    static void GetRecentTrades(std::string &symbol,
                                int limit,
                                Json::Value &result_json);

    static void GetAggTrades(std::string &symbol,
                             int limit,
                             Json::Value &result_json);

    static void GetKlines(std::string &symbol,
                          std::string &interval,
                          int limit,
                          Json::Value &result_json);

    static void GetAvgPrice(std::string &symbol,
                            Json::Value &result_json);

    static void Get24hrTicker(std::string &symbol,
                              Json::Value &result_json);

    static void GetPriceTicker(Json::Value &result_json);

    static void GetBookTicker(Json::Value &result_json);

    static void GetRolling24hrTicker(Json::Value &result_json);


    //Private API
    void PostOrders(const char *symbol,
                    const char *side,
                    const char *type,
                    const char *timeInForce,
                    double quantity,
                    double price,
                    const char *newClientOrderId,
                    double stopPrice,
                    double icebergQty,
                    long recvWindow,
                    Json::Value &json_result);

    void CancelOrder(const char *symbol,
                    const char *origClientOrderId,
                    const char *orderId,
                    const char *newClientOrderId,
                    long recvWindow,
                    Json::Value &json_result);

    void CancelAllOrders(const char *symbol,
                        long recvWindow,
                        Json::Value &json_result);

    void ReplaceOrder(const char *symbol,
                      const char *origClientOrderId,
                      const char *orderId,
                      const char *side,
                      const char *type,
                      const char *timeInForce,
                      double quantity,
                      double price,
                      const char *newClientOrderId,
                      double stopPrice,
                      double icebergQty,
                      long recvWindow,
                      Json::Value &json_result);

    void GetCurrentOpenOrders(const char *symbol,
                       long recvWindow,
                       Json::Value &json_result);

    void GetOrders(const char *symbol,
                          long recvWindow,
                          Json::Value &json_result);

    void GetAccountInfo(long recvWindow,
                        Json::Value &json_result);

    void GetTradeList(const char *symbol,
                      long fromId,
                      long startTime,
                      long endTime,
                      int limit,
                      long recvWindow,
                      Json::Value &json_result);

    void GetUserStreamKey(long recvWindow,
                          Json::Value &json_result);

    void CloseUserStreamKey(const char *listenKey,
                            long recvWindow,
                            Json::Value &json_result);

    void KeepAliveUserStreamKey(const char *listenKey,
                                long recvWindow,
                                Json::Value &json_result);

private:
    std::string API_KEY;
    std::string API_SECRET;
};

#endif// BINANCE_H

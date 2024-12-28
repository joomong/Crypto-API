#ifndef BINANCE_H
#define BINANCE_H

#include "HttpClient.h"
#include "Utils.h"
#include <string>
#include <vector>
#include <json/json.h>

class Binance {
private:
    std::string api_key_;
    std::string api_secret_;
    bool use_sandbox_; // Optional: Flag for sandbox mode

    HttpClient http_client_;

    // Helper method to get the Binance API host
    std::string getHost() const;

public:
    // Constructor
    Binance(const std::string &api_key,
            const std::string &api_secret,
            bool sandbox = false);

    // Destructor
    ~Binance();

    // ----- Public (Market) API Methods -----
    void GetServerTime(Json::Value &result_json);
    void GetExchangeInfo(Json::Value &result_json);

    // depth endpoint
    void GetOrderBook(const std::string &symbol,
                      int limit,
                      Json::Value &result_json);

    // trades
    void GetRecentTrades(const std::string &symbol,
                         int limit,
                         Json::Value &result_json);

    // aggTrades
    void GetAggTrades(const std::string &symbol,
                      int limit,
                      Json::Value &result_json);

    // klines
    void GetKlines(const std::string &symbol,
                   const std::string &interval,
                   int limit,
                   Json::Value &result_json);

    // ticker/price
    void GetAvgPrice(const std::string &symbol,
                     Json::Value &result_json);

    // 24hr Ticker
    void Get24hrTicker(const std::string &symbol,
                       Json::Value &result_json);

    void GetPriceTicker(Json::Value &result_json);
    void GetBookTicker(Json::Value &result_json);
    void GetRolling24hrTicker(Json::Value &result_json);

    // ----- Private (Signed) API Methods -----
    // Limit orders
    void PostLimitSell(const std::string &symbol,
                       double quantity,
                       double price,
                       Json::Value &json_result);

    void PostLimitBuy(const std::string &symbol,
                      double quantity,
                      double price,
                      Json::Value &json_result);

    // Market orders
    void PostMarketBuy(const std::string &symbol,
                       double quantity,
                       Json::Value &json_result);

    void PostMarketSell(const std::string &symbol,
                        double quantity,
                        Json::Value &json_result);

    // Advanced order
    void PostOrders(const std::string &symbol,
                    const std::string &side,
                    const std::string &type,
                    double quantity,
                    double price,
                    Json::Value &json_result,
                    const std::string &time_in_force = "",
                    const std::string &new_client_order_id = "",
                    double stop_price = 0.0,
                    double iceberg_qty = 0.0,
                    long recv_window = 0);

    // Cancel
    void CancelOrder(const std::string &symbol,
                     const std::string &order_id,
                     Json::Value &json_result,
                     long recv_window = 0);

    void CancelAllOrders(const std::string &symbol,
                         Json::Value &json_result,
                         long recv_window = 0);

    // Replace order
    void ReplaceOrder(const std::string &symbol,
                      const std::string &side,
                      const std::string &type,
                      const std::string &cancel_replace_mode,
                      double quantity,
                      double price,
                      Json::Value &json_result,
                      const std::string &time_in_force = "",
                      double quote_order_qty = 0.0,
                      const std::string &cancel_new_client_order_id = "",
                      const std::string &cancel_orig_client_order_id = "",
                      long cancel_order_id = 0,
                      const std::string &new_client_order_id = "",
                      int strategy_id = 0,
                      int strategy_type = 0,
                      double stop_price = 0.0,
                      double trailing_delta = 0.0,
                      double iceberg_qty = 0.0,
                      const std::string &new_order_resp_type = "",
                      const std::string &self_trade_prevention_mode = "",
                      const std::string &cancel_restrictions = "",
                      long recv_window = 0);

    // Get orders
    void GetCurrentOpenOrders(const std::string &symbol,
                              Json::Value &json_result);

    void GetOrders(const std::string &symbol,
                   Json::Value &json_result,
                   long orderId = 0,
                   long startTime = 0,
                   long endTime = 0,
                   long limit = 0,
                   long recvWindow = 0);

    void GetAccountInfo(Json::Value &json_result);

    void GetAccountTradeList(const std::string &symbol,
                             Json::Value &json_result,
                             long orderId = 0,
                             long startTime = 0,
                             long endTime = 0,
                             long fromId = 0,
                             int limit = 0,
                             long recvWindow = 0);

    // User Stream
    void GetUserStreamKey(Json::Value &json_result);
    void KeepAliveUserStreamKey(const std::string &listenKey);
    void CloseUserStreamKey(const std::string &listenKey);
};

#endif // BINANCE_H

#ifndef BINANCEUSDM_H
#define BINANCEUSDM_H

#include "HttpClient.h"
#include "Utils.h"
#include <string>
#include <vector>
#include <json/json.h>

class Binanceusdm {
private:
    std::string api_key_;
    std::string api_secret_;
    bool use_sandbox_; // Flag for sandbox mode if needed

    HttpClient http_client_;

    // Helper method to get the Binance USDM API host
    std::string getHost() const;

public:
    // Constructor
    Binanceusdm(const std::string &api_key,
                const std::string &api_secret,
                bool sandbox = false);

    // Destructor
    ~Binanceusdm();

    // --------------------
    // Public Market Endpoints
    // --------------------
    void GetServerTime(Json::Value &result_json);
    void GetExchangeInfo(Json::Value &result_json);
    void GetOrderBook(const std::string &symbol, int limit, Json::Value &result_json);
    void GetRecentTrades(const std::string &symbol, int limit, Json::Value &result_json);
    void GetOldTradeLookup(const std::string &symbol, int limit, Json::Value &result_json);
    void GetAggTrades(const std::string &symbol, int limit, Json::Value &result_json);
    void GetKlines(const std::string &symbol, const std::string &interval, int limit, Json::Value &result_json);

    void GetContinuousKlines(const std::string &symbol,
                             const std::string &contractType,
                             const std::string &interval,
                             int limit,
                             Json::Value &result_json);

    void GetIndexPriceKlines(const std::string &symbol,
                             const std::string &interval,
                             int limit,
                             Json::Value &result_json);

    void GetMarkPriceKlines(const std::string &symbol,
                            const std::string &interval,
                            int limit,
                            Json::Value &result_json);

    void GetFundRate(const std::string &symbol, Json::Value &result_json);
    void Get24hrTicker(const std::string &symbol, Json::Value &result_json);
    void GetMarkPrice(const std::string &symbol, Json::Value &result_json);
    void GetPriceTicker(Json::Value &result_json);
    void GetOrderBookTicker(const std::string &symbol, Json::Value &result_json);
    void GetOpenInterest(const std::string &symbol, Json::Value &result_json);

    void GetOpenInterestStatistics(const std::string &symbol,
                                   const std::string &period,
                                   int limit,
                                   Json::Value &result_json);

    void GetTopTraderLongShortAccount(const std::string &symbol,
                                      const std::string &period,
                                      int limit,
                                      Json::Value &result_json);

    void GetTopTraderLongShortPosition(const std::string &symbol,
                                       const std::string &period,
                                       int limit,
                                       Json::Value &result_json);

    void GetLongShortRatio(const std::string &symbol,
                           const std::string &period,
                           int limit,
                           Json::Value &result_json);

    void GetBuySellVolume(const std::string &symbol,
                          const std::string &period,
                          int limit,
                          Json::Value &result_json);

    void GetLvtKlines(const std::string &symbol,
                      const std::string &interval,
                      int limit,
                      Json::Value &result_json);

    void GetIndexInfo(const std::string &symbol, Json::Value &result_json);
    void GetMultiModeAssetIndex(const std::string &symbol, Json::Value &result_json);

    // --------------------
    // Private (Signed) Endpoints
    // --------------------
    // Basic Orders
    void PostLimitSell(const std::string &symbol,
                       double quantity,
                       double price,
                       Json::Value &json_result);

    void PostLimitBuy(const std::string &symbol,
                      double quantity,
                      double price,
                      Json::Value &json_result);

    void PostMarketBuy(const std::string &symbol,
                       double quantity,
                       Json::Value &json_result);

    void PostMarketSell(const std::string &symbol,
                        double quantity,
                        Json::Value &json_result);

    // Advanced Orders
    void PostOrders(const std::string &symbol,
                    const std::string &side,
                    const std::string &type,
                    double quantity,
                    double price,
                    Json::Value &json_result,
                    const std::string &time_in_force = "",
                    const std::string &position_side = "",
                    const std::string &reduce_only = "",
                    const std::string &new_client_order_id = "",
                    double stop_price = 0.0,
                    const std::string &close_position = "",
                    double activation_price = 0.0,
                    double callback_rate = 0.0,
                    const std::string &working_type = "",
                    const std::string &price_protect = "",
                    const std::string &new_order_resp_type = "",
                    double iceberg_qty = 0.0,
                    long recv_window = 0);

    // Modify Orders (PUT)
    void ModifyOrder(const std::string &order_id,
                     const std::string &symbol,
                     const std::string &side,
                     double quantity,
                     double price,
                     Json::Value &json_result,
                     double recv_window = 0.0,
                     const std::string &orig_client_order_id = "");

    // Query Orders
    void GetOrder(const std::string &symbol,
                  const std::string &order_id,
                  Json::Value &json_result,
                  long recv_window = 0);

    // Cancel Orders
    void CancelOrder(const std::string &symbol,
                     const std::string &order_id,
                     Json::Value &json_result,
                     long recv_window = 0);

    void CancelAllOrders(const std::string &symbol,
                         Json::Value &json_result,
                         long recvWindow = 0);

    void AutoCancelALLOpenOrders(const std::string &symbol,
                                 int countdownTime,
                                 Json::Value &json_result);

    // Get Open Order
    void GetOpenOrder(const std::string &symbol,
                      long order_id,
                      Json::Value &json_result,
                      long recv_window = 0);

    void GetOpenOrders(const std::string &symbol,
                       Json::Value &json_result,
                       long recv_window = 0);

    // Account / Position
    void ChangeLeverage(const std::string &symbol,
                        int leverage,
                        Json::Value &json_result);

    void ChangeMarginType(const std::string &symbol,
                          const std::string &marginType,
                          Json::Value &json_result);

    // User Stream
    void GetUserStreamKey(Json::Value &json_result);
    void KeepAliveUserStreamKey(const std::string &listenKey);
    void CloseUserStreamKey(const std::string &listenKey);
};

#endif // BINANCEUSDM_H

#ifndef BINANCEUSDM_H
#define BINANCEUSDM_H
#include "exchange.h"

#define BINANCE_HOST "https://api.binance.com"
#define BINANCE_WS_HOST "stream.binance.com"
#define BINANCE_WS_PORT 9443

class Binanceusdm : public Exchange {
private:
    std::string API_KEY;
    std::string API_SECRET;
public:
    Binanceusdm(std::string &api_key, std::string &api_secret)
        : Exchange(), API_KEY(api_key), API_SECRET(api_secret){};

    //Public API
    static void GetServerTime(Json::Value &result_json);

    static void GetExchangeInfo(Json::Value &result_json);

    static void GetOrderBook(std::string &symbol, int limit,
                             Json::Value &result_json);

    static void GetRecentTrades(std::string &symbol, int limit,
                                Json::Value &result_json);

    static void GetOldTradeLookup(std::string &symbol, int limit,
                                Json::Value &result_json);

    static void GetAggTrades(std::string &symbol, int limit,
                             Json::Value &result_json);

    static void GetKlines(std::string &symbol, std::string &interval, int limit,
                          Json::Value &result_json);

    static void GetContinuousKlines(std::string &symbol, std::string &contractType,
                                    std::string &interval, int limit,
                                  Json::Value &result_json);

    static void GetIndexPriceKlines(std::string &symbol, std::string &interval, int limit,
                          Json::Value &result_json);

    static void GetMarkPriceKlines(std::string &symbol, std::string &interval, int limit,
                          Json::Value &result_json);

    static void GetFundRate(std::string &symbol, Json::Value &result_json);

    static void Get24hrTicker(std::string &symbol, Json::Value &result_json);

    static void GetMarkPrice(std::string &symbol, Json::Value &result_json);

    static void GetPriceTicker(Json::Value &result_json);

    static void GetOrderBookTicker(std::string &symbol, Json::Value &result_json);

    static void GetOpenInterest(std::string &symbol, Json::Value &result_json);

    static void GetOpenInterestStatistics(std::string &symbol, std::string &period, int limit,
                                       Json::Value &result_json);

    static void GetTopTraderLongShortAccount(std::string &symbol, std::string &period, int limit,
                                       Json::Value &result_json);

    static void GetTopTraderLongShortPosition(std::string &symbol, std::string &period, int limit,
                                       Json::Value &result_json);

    static void GetLongShortRatio(std::string &symbol, std::string &period, int limit,
                                       Json::Value &result_json);

    static void GetBuySellVolume(std::string &symbol, std::string &period, int limit,
                                       Json::Value &result_json);

    static void GetLvtKlines(std::string &symbol, std::string &interval, int limit,
                          Json::Value &result_json);

    static void GetIndexInfo(std::string &symbol, Json::Value &result_json);

    static void GetMultiModeAssetIndex(std::string &symbol, Json::Value &result_json);


    //Private API
    void PostLimitSell(const std::string &symbol,
                       const double &quantity,
                       const double &price,
                       Json::Value &json_result);

    void PostLimitBuy(const std::string &symbol,
                      const double &quantity,
                      const double &price,
                      Json::Value &json_result);

    void PostMarketBuy(const std::string &symbol,
                       const double &quantity,
                       Json::Value &json_result);

    void PostMarketSell(const std::string &symbol,
                        const double &quantity,
                        Json::Value &json_result);

    void PostOrders(const std::string &symbol,
                    const std::string &side,
                    const std::string &type,
                    const std::string &time_in_force,
                    const double &quantity,
                    const double &price,
                    Json::Value &json_result,
                    const std::string &new_client_order_id = "",
                    const double &stop_price = 0.0,
                    const double &iceberg_qty = 0.0,
                    const long &recv_window = 0);

    void CancelOrder(const std::string &symbol,
                     const std::string &order_id,
                     Json::Value &json_result,
                     const long &recv_window = 0);

    void CancelAllOrders(const std::string &symbol,
                         Json::Value &json_result,
                         const long &recvWindow = 0);

    void ReplaceOrder(
            const std::string &symbol,
            const std::string &side,
            const std::string &type,
            const std::string &cancel_replace_mode, // must STOP_ON_FAILURE , ALLOW_FAILURE
            const double &quantity,
            const double &price,
            Json::Value &json_result,

            const std::string &time_in_force = "",// GTC, IOC, FOK
            const double &quote_order_qty = 0.0,   //ex usdt
            const std::string &cancel_new_client_order_id = "",//Used to uniquely identify this cancel. Automatically generated by default.
            const std::string &cancel_orig_client_order_id = "",//Either the cancelOrigClientOrderId or cancelOrderId must be provided. If both are provided, cancelOrderId takes precedence.
            const long &cancel_order_id = 0,//Either the cancelOrigClientOrderId or cancelOrderId must be provided. If both are provided, cancelOrderId takes precedence.
            const std::string &new_client_order_id = "",//A unique id for the order. Automatically generated if not sent.
            const int &strategy_id = 0,
            const int &strategy_type = 0,
            const double &stop_price = 0.0,
            const double &trailing_delta = 0.0,
            const double &iceberg_qty = 0.0,
            const std::string &new_order_resp_type = "",// ACK, RESULT, FULL?
            const std::string &self_trade_prevention_mode = "",
            const std::string &cancel_restrictions = "",
            const long &recv_window = 0);

    void GetCurrentOpenOrders(const std::string &symbol,
                              Json::Value &json_result);

    void GetOrders(const std::string &symbol,
                   Json::Value &json_result,
                   const long &orderId = 0,
                   const long &startTime = 0,
                   const long &endTime = 0,
                   const long &limit = 0,
                   const long &recvWindow = 0);

    void GetAccountInfo(Json::Value &json_result);

    void GetAccountTradeList(const std::string &symbol,
                             Json::Value &json_result,
                             const long &orderId = 0,
                             const long &startTime = 0,
                             const long &endTime = 0,
                             const long &fromId = 0,
                             const int &limit = 0,
                             const long &recvWindow = 0);


    void GetUserStreamKey(Json::Value &json_result);

    void CloseUserStreamKey(const std::string &listenKey);

    void KeepAliveUserStreamKey(const std::string &listenKey);

};

#endif//BINANCEUSDM_H

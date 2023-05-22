#ifndef BINANCEUSDM_H
#define BINANCEUSDM_H
#include "exchange.h"

#define BINANCEUSDM_HOST "https://fapi.binance.com"
#define BINANCEUSDM_WS_HOST "fstream.binance.com"
#define BINANCE_WS_PORT 9443

class Binanceusdm : public Exchange {
private:
    static std::string API_KEY;
    static std::string API_SECRET;
public:
//    Binanceusdm(std::string &api_key, std::string &api_secret)
//        : Exchange(), API_KEY(api_key), API_SECRET(api_secret){};

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
    static void PostLimitSell(const std::string &symbol,
                       const double &quantity,
                       const double &price,
                       Json::Value &json_result);

    static void PostLimitBuy(const std::string &symbol,
                      const double &quantity,
                      const double &price,
                      Json::Value &json_result);

    static void PostMarketBuy(const std::string &symbol,
                       const double &quantity,
                       Json::Value &json_result);

    static void PostMarketSell(const std::string &symbol,
                        const double &quantity,
                        Json::Value &json_result);

    static void PostOrders(const std::string &symbol,
                    const std::string &side,
                    const std::string &type,
                    const double &quantity,
                    Json::Value &json_result,
                    const double &price = 0.0,
                    const std::string &time_in_force = "",
                    const std::string &position_side = "",
                    const std::string &reduce_only = "",
                    const std::string &new_client_order_id = "",
                    const double &stop_price = 0.0,
                    const std::string &close_position = "",
                    const double &activation_price = 0.0,
                    const double &callback_rate = 0.0,
                    const std::string &working_type = "",
                    const std::string &price_protect = "",
                    const std::string &new_order_resp_type = "",
                    const double &iceberg_qty = 0.0,
                    const long &recv_window = 0);

    static void ModifyOrder(const std::string &order_id,
                     const std::string &symbol,
                     const std::string &side,
                     const double &quantity,
                     const double &price,
                     Json::Value &json_result,
                     const double &recv_window = 0.0,
                     const std::string &orig_client_order_id = "");

    static void GetOrder(const std::string &symbol,
                  const std::string &order_id,
                  Json::Value &json_result,
                  const long &recv_window = 0);

    static void CancelOrder(const std::string &symbol,
                     const std::string &order_id,
                     Json::Value &json_result,
                     const long &recv_window = 0);

    static void CancelAllOrders(const std::string &symbol,
                         Json::Value &json_result,
                         const long &recvWindow = 0);

    static void AutoCancelALLOpenOrders(const std::string &symbol,
                                  const int &countdownTime,
                                  Json::Value &json_result);

    static void GetOpenOrder(const std::string &symbol,
                      const long &order_id,
                       Json::Value &json_result,
                       const long &recv_window = 0);

    static void GetOpenOrders(const std::string &symbol,
                       Json::Value &json_result,
                       const long &recv_window = 0);

    static void ChangeLeverage(const std::string &symbol,
                        const int &leverage,
                        Json::Value &json_result);

    static void ChangeMarginType(const std::string &symbol,
                          const std::string &marginType,
                          Json::Value &json_result);

//    void GetCurrentOpenOrders(const std::string &symbol,
//                              Json::Value &json_result);

//    void GetAccountInfo(Json::Value &json_result);

//    void GetAccountTradeList(const std::string &symbol,
//                             Json::Value &json_result,
//                             const long &orderId = 0,
//                             const long &startTime = 0,
//                             const long &endTime = 0,
//                             const long &fromId = 0,
//                             const int &limit = 0,
//                             const long &recvWindow = 0);


    static void GetUserStreamKey(Json::Value &json_result);

    static void CloseUserStreamKey(const std::string &listenKey);

    static void KeepAliveUserStreamKey(const std::string &listenKey);

};

#endif//BINANCEUSDM_H

#ifndef HASHKEY_H
#define HASHKEY_H

#include "exchange.h"
#include "json/json.h"
#include <string>

#define HASHKEY_HOST "https://api-glb.hashkey.com"
#define HASHKEY_WS_HOST "wss://stream-glb.hashkey.com"
#define HASHKEY_WS_PORT ""

class Hashkey : public Exchange {
public:
    static std::string API_KEY;
    static std::string API_SECRET;
    static void init(std::string &api_key, std::string &api_secret);

    //Public API
    static void GetServerTime(Json::Value &result_json);

    static void GetExchangeInfo(Json::Value &result_json);
    
    static void GetOrderBook(std::string &symbol , int limit,
                             Json::Value &result_json);

    static void GetRecentTrades(std::string &symbol , int limit,
                            Json::Value &result_json);
    
    static void GetKlines(std::string &symbol, std::string &interval, int limit,
                          Json::Value &result_json);

    // static void Get24hrTicker(std::string &symbol, Json::Value &result_json);

    // static void GetPriceTicker(Json::Value &result_json);

    // static void GetBookTicker(Json::Value &result_json);

    // static void GetRolling24hrTicker(Json::Value &result_json);


    //Private API
    // static void PostLimitSell(const std::string &symbol,
    //                         const double &quantity,
    //                         const double &price, 
    //                         Json::Value &json_result);

    // static void PostLimitBuy(const std::string &symbol,
    //                        const double &quantity,
    //                        const double &price, 
    //                        Json::Value &json_result);

    static void PostLimitOrder(const std::string &symbol,
                            const std::string &side,
                            const double &quantity,
                            const double &price, 
                            Json::Value &json_result,
                            const std::string &client_order_id = "99999999980001");
    
    static void PostMarketOrder(const std::string &symbol,
                            const std::string &side,
                            const double &quantity,
                            Json::Value &json_result,
                            const std::string &client_order_id = "99999999980001");

    

    // TODO: If market order, price is not required
    // TODO: If market order, time_in_force is not required
    // TODO: Batch order 

    static void CancelOrder(const std::string &symbol,
                     const std::string &order_id,
                     Json::Value &json_result,
                     const std::string &client_order_id = "99999999980001");

    static void CancelAllOrders(const std::string &symbol,
                         const std::string &side,
                         Json::Value &json_result);

    static void GetCurrentOpenOrders(const std::string &symbol,
                            Json::Value &json_result);

    static void GetOrders(const std::string &symbol,
                  Json::Value &json_result,
                  const long &orderId = 0,
                  const long &startTime = 0,
                  const long &endTime = 0,
                  const long &limit = 0,
                  const long &recvWindow = 0);

    static void GetAccountInfo(Json::Value &json_result);

    static void GetUserStreamKey(Json::Value &json_result);

    // static void CloseUserStreamKey(const std::string &listenKey);

    // static void KeepAliveUserStreamKey(const std::string &listenKey);


};
#endif /* HASHKEY_H */

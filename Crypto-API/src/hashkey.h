#ifndef HASHKEY_H
#define HASHKEY_H

#include "exchange.h"

#define HASHKEY_HOST "https://api-glb.hashkey.com"
#define HASHKEY_WS_HOST "stream-glb.hashkey.com"

class Hashkey : public Exchange {
public:
    static std::string API_KEY;
    static std::string API_SECRET;
    static void init(std::string &api_key, std::string &api_secret);

    //Public API
    static void GetServerTime(Json::Value &result_json);

    static void GetExchangeInfo(std::string &symbol,Json::Value &result_json);
    
    static void GetOrderBook(std::string &symbol , int limit,
                             Json::Value &result_json);

    static void GetRecentTrades(std::string &symbol , int limit,
                            Json::Value &result_json);
    
    static void GetKlines(std::string &symbol, std::string &interval, int limit,
                          Json::Value &result_json);



    //Private
    static void PostLimitOrder(const std::string &symbol,
                            const std::string &side,
                            const double &quantity,
                            const double &price, 
                            Json::Value &json_result,
                            const std::string &time_in_force = "GTC",
                            const std::string &client_order_id = "99999999980001");
    
    static void PostMarketOrder(const std::string &symbol,
                            const std::string &side,
                            const double &quantity,
                            Json::Value &json_result,
                            const std::string &client_order_id = "99999999980001");

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

};
#endif /* HASHKEY_H */

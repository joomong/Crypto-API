#include "Hashkey.h"
#include <json/json.h>
#include <iostream>

int main() {
    // Initialize Hashkey with your API credentials
    std::string api_key("");
    std::string api_secret("");
    std::string symbol("BTCUSDT-PERPETUAL") ;

    Hashkey hashkey(api_key, api_secret);

    Json::Value result;

    // Public example
    // hashkey.GetServerTime(result);
    // std::cout << "Server Time: " << result.toStyledString() << std::endl;

    // hashkey.GetExchangeInfo("BTCUSDT-PERPETUAL",result);
    // std::cout << "Info: " << result.toStyledString() << std::endl;

    // hashkey.GetOrderBook("BTCUSDT-PERPETUAL",5,result);
    // std::cout << "order book: " << result.toStyledString() << std::endl;

    // hashkey.GetRecentTrades("BTCUSDT-PERPETUAL",5,result);
    // std::cout << "recent trades: " << result.toStyledString() << std::endl;

    // hashkey.GetKlines("BTCUSDT-PERPETUAL","1m",5,result);
    // std::cout << "klines: " << result.toStyledString() << std::endl;


    // Example: Place a Limit Buy Order
    hashkey.PostLimitOrder(symbol, "BUY", 0.001, 90000.00, result);
    std::cout << "Limit Order Response: " << result.toStyledString() << std::endl;


    // Example: Cancel an Order
    // hashkey.CancelOrder(symbol, "order_id_here", result);
    // std::cout << "Cancel Order Response: " << result.toStyledString() << std::endl;

    return 0;
}

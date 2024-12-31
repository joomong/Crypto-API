#include "OKX.h"
#include <json/json.h>
#include <iostream>

int main() {
    // Initialize Hashkey with your API credentials
    std::string api_key(""
);
    std::string api_secret("");
    std::string passphrase("");

    std::string symbol("BTC-USDT-SWAP") ;
    OKX okx(api_key,api_secret,passphrase);


    Json::Value result;

    // Public example
    // okx.GetServerTime(result);
    // std::cout << "Server Time: " << result.toStyledString() << std::endl;

    // okx.GetExchangeInfo("SWAP",result);
    // std::cout << "Info: " << result.toStyledString() << std::endl;

    // okx.GetOrderBook(symbol,5,result);
    // std::cout << "order book: " << result.toStyledString() << std::endl;

    // okx.GetRecentTrades(symbol,5,result);
    // std::cout << "recent trades: " << result.toStyledString() << std::endl;

    // okx.GetKlines(symbol,"1m",5,result);
    // std::cout << "klines: " << result.toStyledString() << std::endl;


    // Example: Place a Limit Buy Order
    okx.PostLimitOrder(symbol, "BUY", 0.001, 90000.00, result);
    std::cout << "Limit Order Response: " << result.toStyledString() << std::endl;

    // Example: Cancel an Order
    okx.CancelOrder(symbol, "order_id_here", result);
    std::cout << "Cancel Order Response: " << result.toStyledString() << std::endl;

    return 0;
}

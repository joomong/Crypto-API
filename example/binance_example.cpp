#include <iostream>
#include <string>

#include "binance.h"

int main(){
    std::string api_key;
    std::string api_secret;

    Binance binance(api_key, api_secret);
    Json::Value result_json;
    std::string ticker = "BTCUSDT";

//    //Public API
//    // sever time
//    Binance::GetServerTime(result_json);
//    std::cout << result_json << std::endl;
//
//    // exchange info
//    Binance::GetExchangeInfo(result_json);
//    std::cout << result_json << std::endl;
//
//    // order book
//    Binance::GetOrderBook(ticker, 5, result_json);
//    std::cout << result_json << std::endl;
//
//    // recent trades
//    Binance::GetRecentTrades(ticker, 5, result_json);
//    std::cout << result_json << std::endl;
//
//    // agg trades
//    Binance::GetAggTrades(ticker, 5, result_json);
//    std::cout << result_json << std::endl;
//
//    // klines
//    std::string interval = "1m";
//    Binance::GetKlines(ticker, interval, 5, result_json);
//    std::cout << result_json << std::endl;
//
//    // avg price
//    Binance::GetAvgPrice(ticker, result_json);
//    std::cout << result_json << std::endl;
//
//    // 24hr ticker
//    Binance::Get24hrTicker(ticker, result_json);
//    std::cout << result_json << std::endl;
//
//    // price ticker
//    Binance::GetPriceTicker(result_json);
//    std::cout << result_json << std::endl;
//
//    // book ticker
//    Binance::GetBookTicker(result_json);
//    std::cout << result_json << std::endl;
//
//    // rolling 24hr ticker
//    Binance::GetRolling24hrTicker(result_json);
//    std::cout << result_json << std::endl;




    // Private API
    // limit sell
    double quantity = 0.001;
    double price = 10000;

    binance.PostLimitSell(ticker, quantity, price, result_json);
    std::cout << result_json << std::endl;

    // limit buy
    binance.PostLimitBuy(ticker, quantity, price, result_json);
    std::cout << result_json << std::endl;

    // market buy
    binance.PostMarketBuy(ticker, quantity, result_json);
    std::cout << result_json << std::endl;

    // market sell
    binance.PostMarketSell(ticker, quantity, result_json);
    std::cout << result_json << std::endl;












































    return 0;
}
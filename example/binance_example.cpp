#include <string>
#include <future>
#include <thread>
#include "../src/binanceusdm.h"

int on_message(Json::Value &result_json){
    std::cout << result_json << std::endl;
};

std::string api_key = "rqUkbaF9xvMrRJQs9m87g2GlgxMKkaHQUiMHFInTTBoJxzFG8hM9tdXpSN0fj0PY";
std::string api_secret = "JSy54Uaw62k898J17mRPmC8ptL2VBdBTTORr4x3pOflH6dFDa0NeIFw279Pzyvex";

int main(){
    Json::Value result_json;
    Json::Value user_data_key;

    Binanceusdm::init(api_key, api_secret);

    std::string symbol("BTCUSDT");
    std::string interval("1m");

//    Binanceusdm::connect_endpoint(on_message,
//                                  BINANCE_WS_HOST,
//                                  BINANCE_WS_PORT,
//                                  "/ws/btcusdt@aggTrade");
//    Binanceusdm::enter_event_loop();

    Binanceusdm::PostLimitSell(symbol, 0.001, 50000, result_json);
    std::cout << result_json << std::endl;

//    std::string order_id = result_json["orderId"].asString();

    Binanceusdm::CancelAllOrders(symbol,result_json);
    std::cout << result_json << std::endl;

    Binanceusdm::PostLimitSell(symbol, 0.001, 50000, result_json);
    std::cout << result_json << std::endl;

    return 0;
}

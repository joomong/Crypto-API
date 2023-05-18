#include <string>
#include <future>
#include "../src/binance.h"

int on_message(Json::Value &result_json){
    std::cout << result_json << std::endl;
};

std::string api_key("rqUkbaF9xvMrRJQs9m87g2GlgxMKkaHQUiMHFInTTBoJxzFG8hM9tdXpSN0fj0PY");
std::string api_secret("JSy54Uaw62k898J17mRPmC8ptL2VBdBTTORr4x3pOflH6dFDa0NeIFw279Pzyvex");

int main(){
    Binance binance(api_key, api_secret);
    Json::Value result_json;
    Json::Value user_data_key;
    binance.PostLimitBuy("BTCUSDT", 0.001, 10000.0, result_json);
    std::cout << result_json << std::endl;
//    binance.GetUserStreamKey(user_data_key);

//    std::string user_data_key_path = "/ws/" + user_data_key["listenKey"].asString();
//    Binance::connect_endpoint(on_message,
//                              BINANCE_WS_HOST,
//                              BINANCE_WS_PORT,
//                              user_data_key_path.c_str());
//    auto f = std::async(std::launch::async, &Binance::enter_event_loop);

//    binance.PostOrders("BTCUSDT",
//                       "BUY",
//                       "MARKET",
//                       "GTC",
//                       0.001,
//                       0.0,
//                       result_json);
//    //TODO: if market order price is not needed and time in force is not needed also
//    std::cout << result_json << std::endl;

//    binance.PostOrders("BTCUSDT",
//                       "BUY",
//                       "LIMIT",
//                       "GTC",
//                       0.001,
//                       10000.0,
//                       result_json);
//    std::cout << result_json << std::endl;
//    std::string order_id = result_json["orderId"].asString();

//    binance.GetCurrentOpenOrders("BTCUSDT", result_json);
//    std::cout << result_json << std::endl;
//
//    binance.GetOrders("BTCUSDT",result_json);
//    std::cout << result_json << std::endl;

//    binance.GetAccountInfo(result_json);
//    std::cout << result_json << std::endl;

//    binance.CancelOrder("BTCUSDT", order_id, result_json);
//    std::cout << result_json << std::endl;
//
//    binance.CancelAllOrders("BTCUSDT", result_json);
//    std::cout << result_json << std::endl;

    return 0;
}

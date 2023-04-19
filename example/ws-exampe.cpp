#include "../src/binance.h"

int on_message(Json::Value &result_json){
    std::cout << result_json << std::endl;
};

std::string api_key;
std::string api_secret;

int main(){
    Binance binance(api_key, api_secret);
    Json::Value result_json;

    Binance::connect_endpoint(on_message,
                              BINANCE_WS_HOST,
                              BINANCE_WS_PORT,
                              "/ws/btcusdt@aggTrade");
    Binance::enter_event_loop();
};
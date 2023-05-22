#include <string>
#include <future>
#include "../src/binance.h"
#include "../src/binanceusdm.h"

int on_message(Json::Value &result_json){
    std::cout << result_json << std::endl;
};

std::string api_key("Your api key");
std::string api_secret("Your api secret");

int main(){
    Binanceusdm binanceusdm(api_key, api_secret);

    Json::Value result_json;
    Json::Value user_data_key;

    std::string symbol("BTCUSDT");
    std::string interval("5m");
    std::string contractType("PERPETUAL");

    std::string side("BUY");
    std::string type("LIMIT");

//    binanceusdm.PostOrders(symbol, side, type, 0.01, result_json,10000,"GTC");
//    std::cout << result_json << std::endl;
    std::string order_id = "151846605101";

//    binanceusdm.ModifyOrder(order_id, "BTCUSDT","BUY",0.01,15000,result_json);
//    std::cout << result_json << std::endl;

//    binanceusdm.GetOrder(symbol, order_id, result_json);
//    std::cout << result_json << std::endl;

//    binanceusdm.CancelOrder(symbol, order_id, result_json);
//    std::cout << result_json << std::endl;


//    binanceusdm.CancelAllOrders(symbol, result_json);
//    std::cout << result_json << std::endl;

//    binanceusdm.AutoCancelALLOpenOrders(symbol, 3000, result_json);
//    std::cout << result_json << std::endl;

//    binanceusdm.GetOpenOrders(symbol, result_json);
//    std::cout << result_json << std::endl;

//    binanceusdm.ChangeLeverage(symbol, 10, result_json);
//    std::cout << result_json << std::endl;

    binanceusdm.GetUserStreamKey(user_data_key);
    std::cout << user_data_key << std::endl;

    return 0;
}

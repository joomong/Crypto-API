#include <string>
#include <future>
#include "../src/binance.h"
#include "../src/binanceusdm.h"

int on_message(Json::Value &result_json){
    std::cout << result_json << std::endl;
};

std::string api_key = "api_key";
std::string api_secret = "api_secret";

int main(){
    Json::Value result_json;
    Json::Value user_data_key;

    Binanceusdm::init(api_key, api_secret);

    std::string symbol("BTCUSDT");
    std::string interval("1m");

    Binanceusdm::GetKlines(symbol, interval, 10, result_json);
    std::cout << result_json << std::endl;

    return 0;
}

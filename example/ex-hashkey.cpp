#include "../src/hashkey.h"

#include "exchange.h"
#include <json/json.h>
#include <iostream>
#include <csignal>

// 웹소켓으로부터 데이터를 수신하면 호출되는 콜백
int on_message(Json::Value &result_json)
{
    std::cout << "[on_message] Received: " << result_json << std::endl;
    return 0;
}

int main()
{
    Exchange::init();

    // 3) 예시: Hashkey 실시간 구독 예제 (JSON sub 메시지)
    // {
    //   "symbol": "BTCUSDT",
    //   "topic": "realtimes",
    //   "event": "sub",
    //   "params": { "binary": false },
    //   "id": 1
    // }
    Json::Value root;
    root["symbol"] = "BTCUSDT-PERPETUAL";
    root["topic"]  = "realtimes";
    root["event"]  = "sub";
    root["params"]["binary"] = false;
    root["id"] = 1;

    Json::StreamWriterBuilder wbuilder;
    std::string subscribe_message = Json::writeString(wbuilder, root);

    std::string host = "stream-glb.hashkey.com";
    int port = 443;
    char* path = "/quote/ws/v1";

    Exchange::connect_endpoint_with_sub(
        on_message,
        host,
        port,
        path,
        subscribe_message
    );

    Exchange::enter_event_loop();

    std::cout << "[main] Exiting normally." << std::endl;
    return 0;
}
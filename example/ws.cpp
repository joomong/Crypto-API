#include <libwebsockets.h>
#include <string>
#include <iostream>
#include <cstring>
#include "json/json.h" 

static int interrupted = 0;

static int callback_function(struct lws *wsi, enum lws_callback_reasons reason,
                             void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            std::cout << "WebSocket connection established." << std::endl;

            // 실시간 데이터 구독 메시지 전송
            {
                Json::Value root;
                root["symbol"] = "BTCUSDT";
                root["topic"] = "realtimes";
                root["event"] = "sub";
                root["params"]["binary"] = false;
                root["id"] = 1;

                Json::StreamWriterBuilder writer;
                std::string message = Json::writeString(writer, root);

                unsigned char buffer[LWS_PRE + 512];
                std::memcpy(&buffer[LWS_PRE], message.c_str(), message.size());
                lws_write(wsi, &buffer[LWS_PRE], message.size(), LWS_WRITE_TEXT);

                std::cout << "Sent subscription message: " << message << std::endl;
            }
            break;

        case LWS_CALLBACK_CLIENT_RECEIVE:
            // 서버로부터 메시지 수신
            std::cout << "Received: " << std::string((const char *)in, len) << std::endl;
            break;

        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            std::cerr << "Connection error: " << (in ? (const char *)in : "") << std::endl;
            interrupted = 1;
            break;

        case LWS_CALLBACK_CLIENT_CLOSED:
            std::cout << "Connection closed." << std::endl;
            interrupted = 1;
            break;

        default:
            break;
    }
    return 0;
}

int main() {
    struct lws_context_creation_info info;
    struct lws_client_connect_info ccinfo = {0};
    struct lws_protocols protocols[] = {
        {"example-protocol", callback_function, 0, 128},
        {NULL, NULL, 0, 0}
    };

    // LWS 컨텍스트 생성 정보 초기화
    memset(&info, 0, sizeof info);
    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = protocols;
    info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

    struct lws_context *context = lws_create_context(&info);
    if (!context) {
        std::cerr << "Failed to create lws context" << std::endl;
        return -1;
    }

    // WebSocket 연결 정보 설정
    ccinfo.context = context;
    ccinfo.address = "stream-glb.sim.hashkeydev.com";
    ccinfo.port = 443;
    ccinfo.path = "/quote/ws/v1";
    ccinfo.host = ccinfo.address;
    ccinfo.origin = ccinfo.address;
    ccinfo.ssl_connection = LCCSCF_USE_SSL;
    ccinfo.protocol = protocols[0].name;

    // 연결 시도
    struct lws *wsi = lws_client_connect_via_info(&ccinfo);
    if (!wsi) {
        std::cerr << "Failed to connect to server" << std::endl;
        lws_context_destroy(context);
        return -1;
    }

    // 이벤트 루프
    while (!interrupted) {
        lws_service(context, 1000);
    }

    lws_context_destroy(context);
    return 0;
}

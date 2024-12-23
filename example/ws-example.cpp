#include <libwebsockets.h>
#include <iostream>
#include <cstring>
#include <string>
#include <signal.h>

static int interrupted = 0;
static struct lws *client_wsi = nullptr;

// 메시지를 서버로 보내는 콜백 함수
static int callback(struct lws *wsi, enum lws_callback_reasons reason,
                    void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            std::cout << "Connected to OKX WebSocket server" << std::endl;
            lws_callback_on_writable(wsi);  // 쓰기 가능 신호
            break;

        case LWS_CALLBACK_CLIENT_RECEIVE:
            // 서버로부터 메시지를 수신
            std::cout << "Received: " << std::string(static_cast<char *>(in), len) << std::endl;
            break;

        case LWS_CALLBACK_CLIENT_WRITEABLE: {
            // 메시지 전송 (OKX API 티커 구독 요청 예제)
            const std::string msg = R"({"op": "subscribe", "args": [{"channel": "tickers", "instId": "BTC-USDT"}]})";
            unsigned char buf[LWS_PRE + 1024];
            std::memset(buf, 0, sizeof(buf));
            std::memcpy(&buf[LWS_PRE], msg.c_str(), msg.size());
            lws_write(wsi, &buf[LWS_PRE], msg.size(), LWS_WRITE_TEXT);
            std::cout << "Message sent: " << msg << std::endl;
            break;
        }

        case LWS_CALLBACK_CLOSED:
            std::cout << "Connection closed" << std::endl;
            client_wsi = nullptr;
            interrupted = 1;
            break;

        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            std::cerr << "Connection error" << std::endl;
            interrupted = 1;
            break;

        default:
            break;
    }
    return 0;
}

// WebSocket 프로토콜 정의
static struct lws_protocols protocols[] = {
    {
        "okx-protocol",  // 프로토콜 이름
        callback,        // 콜백 함수
        0,               // 사용자 데이터 크기
        1024,            // 메시지 버퍼 크기
    },
    {nullptr, nullptr, 0, 0}  // 종료를 나타냄
};

int main() {
    struct lws_context_creation_info info;
    struct lws_client_connect_info conn_info;
    struct lws_context *context;

    // lws_context 생성 정보 초기화
    std::memset(&info, 0, sizeof(info));
    info.port = CONTEXT_PORT_NO_LISTEN;  // 서버 모드가 아님
    info.protocols = protocols;
    info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;  // TLS 초기화


    // WebSocket 컨텍스트 생성
    context = lws_create_context(&info);
    if (!context) {
        std::cerr << "Failed to create context" << std::endl;
        return -1;
    }
    // main 함수 내 lws_context 생성 직후에 로그 레벨 설정 추가
    // lws_set_log_level(LLL_ERR | LLL_WARN | LLL_NOTICE | LLL_INFO | LLL_DEBUG, NULL);


    // lws_client_connect_info 초기화
    std::memset(&conn_info, 0, sizeof(conn_info));
    conn_info.context = context;
    conn_info.address = "104.18.43.174";        // OKX WebSocket 서버 IPv4 주소 직접 사용
    conn_info.port = 8443;                      // TLS 포트
    conn_info.path = "/ws/v5/public";           // OKX WebSocket 엔드포인트 (공개 채널)
    conn_info.host = "ws.okx.com";              // Host 헤더는 도메인 이름으로 설정
    conn_info.origin = "ws.okx.com";            // Origin 헤더도 도메인 이름으로 설정
    conn_info.ssl_connection = LCCSCF_USE_SSL;  // SSL 인증서 검증 활성화

    conn_info.protocol = protocols[0].name;     // 프로토콜 이름

    // conn_info.context = context;
    // conn_info.address = "ws.okx.com";        // OKX WebSocket 서버 주소
    // conn_info.port = 8443;                   // TLS 포트
    // conn_info.path = "/ws/v5/public";        // OKX WebSocket 엔드포인트
    // conn_info.host = "ws.okx.com";
    // conn_info.origin = "ws.okx.com";
    // conn_info.ssl_connection = LCCSCF_USE_SSL;  // TLS 연결 활성화
    // conn_info.protocol = protocols[0].name;     // 프로토콜 이름

    // WebSocket 서버에 연결
    client_wsi = lws_client_connect_via_info(&conn_info);
    if (!client_wsi) {
        std::cerr << "Failed to connect to OKX server" << std::endl;
        lws_context_destroy(context);
        return -1;
    }

    // 이벤트 루프 실행
    while (!interrupted) {
        lws_service(context, 1000);  // 이벤트 처리
    }

    // 정리
    lws_context_destroy(context);
    std::cout << "WebSocket client exited" << std::endl;
    return 0;
}

#include "exchange.h"
#include <chrono>

//static members
CURL *Exchange::curl_ = nullptr;
std::map <struct lws *,CB> Exchange::handles ;
struct lws_context *Exchange::context = nullptr;
std::map<struct lws*, std::string> Exchange::subscribe_messages;


//protocol table
struct lws_protocols Exchange::protocols[] = {
        {
                "http-only",
                Exchange::event_cb,
                0,
                65536,
        },
        {nullptr,nullptr,0,0 } /* terminator */
};


void Exchange::init() {
    curl_global_init(CURL_GLOBAL_ALL);
    curl_ = curl_easy_init();

    //libwebsockets context initalize
    struct lws_context_creation_info info{};
    memset(&info,0,sizeof(info));

    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = protocols;
    info.gid = -1;
    info.uid = -1;
    info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT; //| LWS_SERVER_OPTION_DISABLE_IPV6;
     lws_set_log_level(LLL_ERR | LLL_WARN | LLL_NOTICE | LLL_INFO | LLL_DEBUG | LLL_PARSER | LLL_LATENCY | LLL_EXT, nullptr);
    // CA 인증서 파일 경로 설정
    info.ssl_ca_filepath = "/etc/ssl/certs/ca-certificates.crt"; // 시스템에 맞게 경로 수정
    // 또는 CA 인증서 메모리 설정을 원할 경우:
    // info.ssl_ca_mem = <pointer to CA cert data>;
    // info.ssl_ca_mem_len = <length of CA cert data>;    

    context = lws_create_context( &info );
    if(!context) {
        std::cerr << "Failed to create lws context" << std::endl;
    }
}


void Exchange::Cleanup()
{
    if(curl_){
        curl_easy_cleanup(curl_);
    }
    curl_global_cleanup();
}

// ------------------------- REST -------------------------------
void Exchange::CurlApi(std::string &url, std::string &result_json) {
    std::vector<std::string> extra_http_header;
    std::string action = "GET";
    std::string post_data;
    Exchange::CurlApiWithHeader(url, result_json,
                                extra_http_header, post_data, action);
}


void Exchange::CurlApiWithHeader(std::string &url,
                                 std::string &result_json,
                                 std::vector<std::string> &extra_http_header,
                                 std::string &post_data,
                                 std::string &action) 
{
    CURLcode res;
    // note) exists in initfucntion
    // curl_global_init(CURL_GLOBAL_ALL);
    // curl_ = curl_easy_init();

    if (curl_) {
        curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, CurlCB);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &result_json);
        curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl_, CURLOPT_ENCODING, "gzip");

        if (!extra_http_header.empty())
        {
            struct curl_slist *chunk = nullptr;
            for (const auto &i: extra_http_header) {
                chunk = curl_slist_append(chunk, i.c_str());
            }
            curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, chunk);
        }
        if (!post_data.empty() || action == "POST" || action == "PUT" ||
            action == "DELETE")
        {
            if (action == "PUT" || action == "DELETE")
            {
                curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, action.c_str());
            }
            curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, post_data.c_str());
        }
        curl_easy_setopt(curl_,CURLOPT_CUSTOMREQUEST,action.c_str());
        res = curl_easy_perform(curl_);

        if (res != CURLE_OK)
        {
            std::cout << "<curl_api> curl_easy_perform() failed: "
                      << curl_easy_strerror(res) << std::endl;
        }
    }
}


std::size_t Exchange::CurlCB(void *content,
                             std::size_t size,
                             std::size_t nmemb,
                             std::string *buffer)
{
    buffer->append((char *) content, size * nmemb);
    return size * nmemb;
}



// ----------------- Crypto Util -------------------
std::string Exchange::b2a_hex(char *byte_arr, int n)
{
    const static std::string HexCodes = "0123456789abcdef";
    std::string HexString;
    HexString.reserve((size_t)n*2);

    for ( int i = 0; i < n ; ++i ) {
        unsigned char BinValue = byte_arr[i];
        HexString.push_back(HexCodes[( BinValue >> 4 ) & 0x0F]);
        HexString.push_back(HexCodes[BinValue & 0x0F]);
    }
    return HexString;
}


std::string Exchange::sha256(const char *data)
{
    unsigned char digest[32];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, strlen(data));
    SHA256_Final(digest, &sha256);
    return b2a_hex((char *) digest, 32);
}



std::string Exchange::hmac_sha256(const char *data, const char *key)
{
    unsigned char *digest;
    digest = HMAC(EVP_sha256(), key, strlen(key), (unsigned char *) data,
                  strlen(data), nullptr, nullptr);
    return b2a_hex((char *) digest, 32);
}


long long Exchange::GetCurrentMsEpoch()
{
    auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now()
        );
    return now.time_since_epoch().count();
}




// ------------------------- Websocket ----------------------------
// 기존 connect_endpoint
void Exchange::connect_endpoint(CB user_cb,
                                const std::string &host,
                                int port,
                                const char* path)
{
    std::cout << "Connecting to " << host << ":" << port << path << std::endl;

    char ws_path[1024];
    // 안전하게 복사
    strncpy(ws_path, path, sizeof(ws_path) - 1);
    ws_path[sizeof(ws_path) - 1] = '\0';

    struct lws_client_connect_info ccinfo;
    memset(&ccinfo, 0, sizeof(ccinfo));

    ccinfo.context = context;
    ccinfo.address = host.c_str();
    ccinfo.port = port;
    ccinfo.path = ws_path;
    ccinfo.host = lws_canonical_hostname(context);
    ccinfo.origin = "origin";
    ccinfo.protocol = protocols[0].name;
    ccinfo.ssl_connection =
        LCCSCF_USE_SSL | LCCSCF_ALLOW_SELFSIGNED | LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;

    struct lws* conn = lws_client_connect_via_info(&ccinfo);
    if (!conn) {
        std::cerr << "Failed to connect to server" << std::endl;
        return;
    }

    handles[conn] = user_cb;
}

// 새로 추가: 구독(sub) 메시지도 함께 보내고 싶을 때
void Exchange::connect_endpoint_with_sub(CB user_cb,
                                         const std::string &host,
                                         int port,
                                         const char* path,
                                         const std::string &subscribe_message)
{
    std::cout << "Connecting to " << host << ":" << port << path << std::endl;

    char ws_path[1024];
    // 안전하게 복사
    strncpy(ws_path, path, sizeof(ws_path) - 1);
    ws_path[sizeof(ws_path) - 1] = '\0';

    struct lws_client_connect_info ccinfo;
    memset(&ccinfo, 0, sizeof(ccinfo));

    ccinfo.context = context;
    ccinfo.address = host.c_str();
    ccinfo.port = port;
    ccinfo.path = ws_path;
    ccinfo.host = lws_canonical_hostname(context);
    ccinfo.origin = "origin";
    ccinfo.protocol = protocols[0].name;
    ccinfo.ssl_connection = LCCSCF_USE_SSL;



    // 연결 시도
    struct lws* conn = lws_client_connect_via_info(&ccinfo);
    if (!conn) {
        std::cerr << "Failed to connect to server" << std::endl;
        return;
    }

    handles[conn] = user_cb;
    subscribe_messages[conn] = subscribe_message;
}

int Exchange::event_cb(struct lws *wsi,
                       enum lws_callback_reasons reason,
                       void *user,
                       void *in,
                       size_t len)
{
    switch (reason)
    {
    case LWS_CALLBACK_CLIENT_ESTABLISHED:
        std::cout << "[event_cb] LWS_CALLBACK_CLIENT_ESTABLISHED" << std::endl;
        // 연결된 후에 구독 메시지 전송
        if (subscribe_messages.find(wsi) != subscribe_messages.end()) {
            std::string message = subscribe_messages[wsi];
            unsigned char buffer[LWS_PRE + 1024];
            memset(buffer, 0, sizeof(buffer));

            // payload를 LWS_PRE 뒤에 위치
            memcpy(&buffer[LWS_PRE], message.c_str(), message.size());

            // 텍스트 프레임 전송
            int ret = lws_write(wsi,
                                &buffer[LWS_PRE],
                                message.size(),
                                LWS_WRITE_TEXT);
            if (ret < 0) {
                std::cerr << "Failed to send subscribe message" << std::endl;
            } else {
                std::cout << "Sent subscription message: " << message << std::endl;
            }
        }
        break;

    case LWS_CALLBACK_CLIENT_RECEIVE:
        // 서버에서 메시지 수신
        if (in && len > 0) {
            try {
                std::string str_result((char*)in, len);
                Json::Value json_result;
                Json::Reader reader;

                if (!reader.parse(str_result, json_result)) {
                    std::cerr << "[event_cb] JSON parse error" << std::endl;
                } else {
                    if (handles.find(wsi) != handles.end()) {
                        handles[wsi](json_result);
                    }
                }
            } catch (std::exception &e) {
                std::cerr << "[event_cb] Exception: " << e.what() << std::endl;
            }
        }
        break;

    case LWS_CALLBACK_CLIENT_WRITEABLE:
        // 필요한 경우, 여기서 추가 전송 가능
        break;

    case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
        std::cerr << "[event_cb] Connection error" << std::endl;
        // fallthrough
    case LWS_CALLBACK_CLOSED:
        std::cout << "[event_cb] Connection closed" << std::endl;
        // 맵에서 제거
        if (handles.find(wsi) != handles.end()) {
            handles.erase(wsi);
        }
        if (subscribe_messages.find(wsi) != subscribe_messages.end()) {
            subscribe_messages.erase(wsi);
        }
        break;

    default:
        break;
    }

    return 0;
}


void Exchange::enter_event_loop()
{
    // 간단히 무한 루프 (Ctrl + C 등으로 종료)
    while(true) {
        int ret = lws_service(context, 500);
        if (ret < 0) {
            std::cerr << "<enter_event_loop> lws_service error: " << ret << std::endl;
            break;
        }
    }

    // 종료 시
    if (context) {
        lws_context_destroy(context);
        context = nullptr;
    }

    // 필요하다면 Cleanup() 호출 (curl, etc.)
    Cleanup();
}
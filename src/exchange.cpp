#include "exchange.h"

CURL *Exchange::curl_ = nullptr;


void Exchange::CurlApi(std::string &url, std::string &result_json) {
    std::vector<std::string> extra_http_header;
    std::string action = "GET";
    std::string post_data;
    Exchange::CurlApiWithHeader(url,
                                result_json,
                                extra_http_header,
                                post_data,
                                action);
}


void Exchange::CurlApiWithHeader(std::string &url,
                                 std::string &result_json,
                                 std::vector<std::string> &extra_http_header,
                                 std::string &post_data,
                                 std::string &action) {
    CURLcode res;

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
        res = curl_easy_perform(curl_);
        /* Check for errors */
        if (res != CURLE_OK)
        {
            std::cout << "<BinaCPP::curl_api> curl_easy_perform() failed: "
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


void Exchange::Cleanup()
{
    curl_easy_cleanup(curl_);
    curl_global_cleanup();
}


std::string Exchange::b2a_hex(char *byte_arr, int n)
{
    const static std::string HexCodes = "0123456789abcdef";
    std::string HexString;
    for ( int i = 0; i < n ; ++i ) {
        unsigned char BinValue = byte_arr[i];
        HexString += HexCodes[( BinValue >> 4 ) & 0x0F];
        HexString += HexCodes[BinValue & 0x0F];
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
    auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    return now.time_since_epoch().count();
}



struct lws_context *Exchange::context = nullptr;
struct lws_protocols Exchange::protocols[] = {
        {
                "example-protocol",
                Exchange::event_cb,
                0,
                65536,
        },
        {nullptr,nullptr,0,0 } /* terminator */
};

std::map <struct lws *,CB> Exchange::handles ;


int Exchange::event_cb(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len )
{
    switch(reason)
    {
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            lws_callback_on_writable( wsi );
            break;

        case LWS_CALLBACK_CLIENT_RECEIVE:

            /* Handle incomming messages here. */
            try {
                std::string str_result = std::string( (char*)in );
                Json::Reader reader;
                Json::Value json_result;
                reader.parse( str_result , json_result );

                if ( handles.find( wsi ) != handles.end() ) {
                    handles[wsi]( json_result );
                }

            } catch ( std::exception &e ) {
                std::cout <<  "<BinaCPP_websocket::event_cb> Error ! "
                             << e.what() << std::endl;
            }
            break;

        case LWS_CALLBACK_CLIENT_WRITEABLE:
        {
            break;
        }

        case LWS_CALLBACK_CLOSED:
        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            if ( handles.find( wsi ) != handles.end() ) {
                handles.erase(wsi);
            }
            break;

        default:
            break;
    }
    return 0;
}


void Exchange::connect_endpoint (CB cb,const std::string &host ,int port, const char *path)
{
    std::cout << host << port << path << std::endl;
    char ws_path[1024];
    strcpy( ws_path, path );

    /* Connect if we are not connected to the server. */
    struct lws_client_connect_info ccinfo = {};
    ccinfo.context 	= context;
    ccinfo.address 	= host.c_str();
    ccinfo.port 	= port;
    ccinfo.path 	= ws_path;
    ccinfo.host 	= lws_canonical_hostname(context);
    ccinfo.origin 	= "origin";
    ccinfo.protocol = protocols[0].name;
    ccinfo.ssl_connection = LCCSCF_USE_SSL | LCCSCF_ALLOW_SELFSIGNED | LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;

    struct lws* conn = lws_client_connect_via_info(&ccinfo);
    handles[conn] = cb;
}


void Exchange::enter_event_loop()
{
    while(true)
    {
        try {
            lws_service( context, 500 );
        } catch ( std::exception &e ) {
            std::cout <<  "<BinaCPP_websocket::enter_event_loop> Error ! %s"
                         << e.what();
            break;
        }
    }
    lws_context_destroy( context );
}













































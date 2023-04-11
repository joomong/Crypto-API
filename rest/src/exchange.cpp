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
    std::cout << "<BinaCPP::curl_api> done" << std::endl;
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


std::string Exchange::sha256(const char *data)
{
    unsigned char digest[32];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, strlen(data));
    SHA256_Final(digest, &sha256);
    return b2a_hex((char *) digest, 32);
}


std::string b2a_hex(char *byte_arr, int n)
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
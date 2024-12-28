#include "Utils.h"
#include <chrono>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
#include <ctime>

long long Utils::GetCurrentMsEpoch() {
    auto now = std::chrono::system_clock::now();
    auto epoch = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();
}

// HMAC-SHA256 서명 생성
std::string Utils::hmac_sha256(const std::string& data, const std::string& key) {
    unsigned char* digest;
    digest = HMAC(EVP_sha256(), key.c_str(), key.length(),
                 reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), NULL, NULL);
    
    std::ostringstream oss;
    for(int i = 0; i < 32; i++)
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    return oss.str();
}

// 현재 시간을 ISO 8601 형식으로 반환 (예: 2023-07-15T12:34:56.789Z)
std::string Utils::GetCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::ostringstream oss;
    oss << std::put_time(gmtime(&t), "%Y-%m-%dT%H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count() << 'Z';
    return oss.str();
}
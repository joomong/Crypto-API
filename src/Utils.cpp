#include "Utils.h"
#include <chrono>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>

std::string Utils::GetCurrentMsEpoch() {
    auto now = std::chrono::system_clock::now();
    auto epoch = now.time_since_epoch();
    return std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count());
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

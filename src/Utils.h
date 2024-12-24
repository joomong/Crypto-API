// Utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
public:
    // 현재 시간을 밀리초 단위로 반환
    static std::string GetCurrentMsEpoch();

    // HMAC-SHA256 서명 생성
    static std::string hmac_sha256(const std::string& data, const std::string& key);
};

#endif // UTILS_H

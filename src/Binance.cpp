#include "Binance.h"
#include <iostream>

// Constructor
Binance::Binance(const std::string &api_key,
                 const std::string &api_secret,
                 bool sandbox)
    : api_key_(api_key), api_secret_(api_secret), use_sandbox_(sandbox), http_client_() {}

// Destructor
Binance::~Binance() {}

// Helper method to determine the API host
std::string Binance::getHost() const {
    // If you have a sandbox URL, you can switch based on use_sandbox_.
    // For example:
    // return use_sandbox_ ? "https://testnet.binance.vision" : "https://api.binance.com";
    return "https://api.binance.com";
}

// ======================
// == Public API (Market)
// ======================
void Binance::GetServerTime(Json::Value &result_json) {
    std::string url = getHost() + "/api/v3/time";
    http_client_.Get(url, result_json);
}

void Binance::GetExchangeInfo(Json::Value &result_json) {
    std::string url = getHost() + "/api/v3/exchangeInfo";
    http_client_.Get(url, result_json);
}

void Binance::GetOrderBook(const std::string &symbol, int limit, Json::Value &result_json) {
    std::string url = getHost() + "/api/v3/depth?symbol=" + symbol +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binance::GetRecentTrades(const std::string &symbol, int limit, Json::Value &result_json) {
    std::string url = getHost() + "/api/v3/historicalTrades?symbol=" + symbol +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binance::GetAggTrades(const std::string &symbol, int limit, Json::Value &result_json) {
    std::string url = getHost() + "/api/v3/aggTrades?symbol=" + symbol +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binance::GetKlines(const std::string &symbol, const std::string &interval, int limit, Json::Value &result_json) {
    std::string url = getHost() + "/api/v3/klines?symbol=" + symbol +
                      "&interval=" + interval +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binance::GetAvgPrice(const std::string &symbol, Json::Value &result_json) {
    std::string url = getHost() + "/api/v3/avgPrice?symbol=" + symbol;
    http_client_.Get(url, result_json);
}

void Binance::Get24hrTicker(const std::string &symbol, Json::Value &result_json) {
    std::string url = getHost() + "/api/v3/ticker/24hr?symbol=" + symbol;
    http_client_.Get(url, result_json);
}

void Binance::GetPriceTicker(Json::Value &result_json) {
    std::string url = getHost() + "/api/v3/ticker/price";
    http_client_.Get(url, result_json);
}

void Binance::GetBookTicker(Json::Value &result_json) {
    std::string url = getHost() + "/api/v3/ticker/bookTicker";
    http_client_.Get(url, result_json);
}

void Binance::GetRolling24hrTicker(Json::Value &result_json) {
    std::string url = getHost() + "/api/v3/ticker/24hr";
    http_client_.Get(url, result_json);
}

// ======================
// == Private API (Signed)
// ======================

// -- Limit Orders --
void Binance::PostLimitSell(const std::string &symbol,
                            double quantity,
                            double price,
                            Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<PostLimitSell> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/order?";
    std::string post_data = "symbol=" + symbol +
                            "&side=SELL" +
                            "&type=LIMIT" +
                            "&timeInForce=GTC" +
                            "&quantity=" + std::to_string(quantity) +
                            "&price=" + std::to_string(price) +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    // Headers
    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Post(url, "", json_result, extra_http_header);
}

void Binance::PostLimitBuy(const std::string &symbol,
                           double quantity,
                           double price,
                           Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<PostLimitBuy> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/order?";
    std::string post_data = "symbol=" + symbol +
                            "&side=BUY" +
                            "&type=LIMIT" +
                            "&timeInForce=GTC" +
                            "&quantity=" + std::to_string(quantity) +
                            "&price=" + std::to_string(price) +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Post(url, "", json_result, extra_http_header);
}

// -- Market Orders --
void Binance::PostMarketBuy(const std::string &symbol,
                            double quantity,
                            Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<PostMarketBuy> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/order?";
    std::string post_data = "symbol=" + symbol +
                            "&side=BUY" +
                            "&type=MARKET" +
                            "&quantity=" + std::to_string(quantity) +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Post(url, "", json_result, extra_http_header);
}

void Binance::PostMarketSell(const std::string &symbol,
                             double quantity,
                             Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<PostMarketSell> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/order?";
    std::string post_data = "symbol=" + symbol +
                            "&side=SELL" +
                            "&type=MARKET" +
                            "&quantity=" + std::to_string(quantity) +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Post(url, "", json_result, extra_http_header);
}

// -- Advanced Orders --
void Binance::PostOrders(const std::string &symbol,
                         const std::string &side,
                         const std::string &type,
                         double quantity,
                         double price,
                         Json::Value &json_result,
                         const std::string &time_in_force,
                         const std::string &new_client_order_id,
                         double stop_price,
                         double iceberg_qty,
                         long recv_window) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<PostOrders> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/order?";
    // 필수 파라미터
    std::string post_data = "symbol=" + symbol +
                            "&side=" + side +
                            "&type=" + type +
                            "&quantity=" + std::to_string(quantity) +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    // LIMIT, STOP_LOSS 등 특정 타입에 따라 추가 파라미터 필요
    if (type != "MARKET") {
        if (!time_in_force.empty()) {
            post_data += "&timeInForce=" + time_in_force;
        }
        post_data += "&price=" + std::to_string(price);
    }

    if (!new_client_order_id.empty()) {
        post_data += "&newClientOrderId=" + new_client_order_id;
    }

    if (stop_price > 0.0) {
        post_data += "&stopPrice=" + std::to_string(stop_price);
    }

    if (iceberg_qty > 0.0) {
        post_data += "&icebergQty=" + std::to_string(iceberg_qty);
    }

    if (recv_window > 0) {
        post_data += "&recvWindow=" + std::to_string(recv_window);
    }

    // 서명 생성
    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;

    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Post(url, "", json_result, extra_http_header);
}

// -- Cancel Orders --
void Binance::CancelOrder(const std::string &symbol,
                          const std::string &order_id,
                          Json::Value &json_result,
                          long recv_window) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<CancelOrder> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/order?";
    std::string post_data = "symbol=" + symbol +
                            "&orderId=" + order_id +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (recv_window > 0) {
        post_data += "&recvWindow=" + std::to_string(recv_window);
    }

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;

    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Delete(url, "", json_result, extra_http_header);
}

void Binance::CancelAllOrders(const std::string &symbol,
                              Json::Value &json_result,
                              long recv_window) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<CancelAllOrders> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/openOrders?";
    std::string post_data = "symbol=" + symbol +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (recv_window > 0) {
        post_data += "&recvWindow=" + std::to_string(recv_window);
    }

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;

    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Delete(url, "", json_result, extra_http_header);
}

// -- Replace Order --
void Binance::ReplaceOrder(const std::string &symbol,
                           const std::string &side,
                           const std::string &type,
                           const std::string &cancel_replace_mode,
                           double quantity,
                           double price,
                           Json::Value &json_result,
                           const std::string &time_in_force,
                           double quote_order_qty,
                           const std::string &cancel_new_client_order_id,
                           const std::string &cancel_orig_client_order_id,
                           long cancel_order_id,
                           const std::string &new_client_order_id,
                           int strategy_id,
                           int strategy_type,
                           double stop_price,
                           double trailing_delta,
                           double iceberg_qty,
                           const std::string &new_order_resp_type,
                           const std::string &self_trade_prevention_mode,
                           const std::string &cancel_restrictions,
                           long recv_window) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<ReplaceOrder> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/cancelReplace?";
    std::string post_data = "symbol=" + symbol +
                            "&side=" + side +
                            "&type=" + type +
                            "&cancelReplaceMode=" + cancel_replace_mode +
                            "&quantity=" + std::to_string(quantity) +
                            "&price=" + std::to_string(price) +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (!time_in_force.empty()) {
        post_data += "&timeInForce=" + time_in_force;
    }

    if (quote_order_qty > 0.0) {
        post_data += "&quoteOrderQty=" + std::to_string(quote_order_qty);
    }

    if (!cancel_new_client_order_id.empty()) {
        post_data += "&cancelNewClientOrderId=" + cancel_new_client_order_id;
    }

    if (!cancel_orig_client_order_id.empty()) {
        post_data += "&cancelOrigClientOrderId=" + cancel_orig_client_order_id;
    }

    if (cancel_order_id > 0) {
        post_data += "&cancelOrderId=" + std::to_string(cancel_order_id);
    }

    if (!new_client_order_id.empty()) {
        post_data += "&newClientOrderId=" + new_client_order_id;
    }

    if (strategy_id > 0) {
        post_data += "&strategyId=" + std::to_string(strategy_id);
    }

    if (strategy_type > 0) {
        post_data += "&strategyType=" + std::to_string(strategy_type);
    }

    if (stop_price > 0.0) {
        post_data += "&stopPrice=" + std::to_string(stop_price);
    }

    if (trailing_delta > 0.0) {
        post_data += "&trailingDelta=" + std::to_string(trailing_delta);
    }

    if (iceberg_qty > 0.0) {
        post_data += "&icebergQty=" + std::to_string(iceberg_qty);
    }

    if (!new_order_resp_type.empty()) {
        post_data += "&newOrderRespType=" + new_order_resp_type;
    }

    if (!self_trade_prevention_mode.empty()) {
        post_data += "&selfTradePrevention=" + self_trade_prevention_mode;
    }

    if (!cancel_restrictions.empty()) {
        post_data += "&cancelRestrictions=" + cancel_restrictions;
    }

    if (recv_window > 0) {
        post_data += "&recvWindow=" + std::to_string(recv_window);
    }

    // 서명 생성
    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Post(url, "", json_result, extra_http_header);
}

// -- Orders Query --
void Binance::GetCurrentOpenOrders(const std::string &symbol,
                                   Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<GetCurrentOpenOrders> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/openOrders?";
    std::string querystring = "symbol=" + symbol +
                              "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Get(url, json_result, extra_http_header);
}

void Binance::GetOrders(const std::string &symbol,
                        Json::Value &json_result,
                        long orderId,
                        long startTime,
                        long endTime,
                        long limit,
                        long recvWindow) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<GetOrders> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/allOrders?";
    std::string querystring = "symbol=" + symbol +
                              "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (orderId > 0) {
        querystring += "&orderId=" + std::to_string(orderId);
    }

    if (startTime > 0) {
        querystring += "&startTime=" + std::to_string(startTime);
    }

    if (endTime > 0) {
        querystring += "&endTime=" + std::to_string(endTime);
    }

    if (limit > 0) {
        querystring += "&limit=" + std::to_string(limit);
    }

    if (recvWindow > 0) {
        querystring += "&recvWindow=" + std::to_string(recvWindow);
    }

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Get(url, json_result, extra_http_header);
}

void Binance::GetAccountInfo(Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<GetAccountInfo> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/account?";
    std::string querystring = "timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Get(url, json_result, extra_http_header);
}

void Binance::GetAccountTradeList(const std::string &symbol,
                                  Json::Value &json_result,
                                  long orderId,
                                  long startTime,
                                  long endTime,
                                  long fromId,
                                  int limit,
                                  long recvWindow) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<GetAccountTradeList> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/myTrades?";
    std::string querystring = "symbol=" + symbol +
                              "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (orderId > 0) {
        querystring += "&orderId=" + std::to_string(orderId);
    }

    if (startTime > 0) {
        querystring += "&startTime=" + std::to_string(startTime);
    }

    if (endTime > 0) {
        querystring += "&endTime=" + std::to_string(endTime);
    }

    if (fromId > 0) {
        querystring += "&fromId=" + std::to_string(fromId);
    }

    if (limit > 0) {
        querystring += "&limit=" + std::to_string(limit);
    }

    if (recvWindow > 0) {
        querystring += "&recvWindow=" + std::to_string(recvWindow);
    }

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Get(url, json_result, extra_http_header);
}

// -- User Stream Methods --
void Binance::GetUserStreamKey(Json::Value &json_result) {
    if (api_key_.empty()) {
        std::cerr << "<GetUserStreamKey> API Key has not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/userDataStream";
    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Post(url, "", json_result, extra_http_header);
}

void Binance::KeepAliveUserStreamKey(const std::string &listenKey) {
    if (api_key_.empty()) {
        std::cerr << "<KeepAliveUserStreamKey> API Key has not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/userDataStream";
    std::string post_data = "listenKey=" + listenKey;
    Json::Value dummy_json; // Not used

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    // 여기서는 PUT이 필요하지만, HttpClient에 PUT 함수가 있다고 가정
    http_client_.Put(url, post_data, dummy_json, extra_http_header);
}

void Binance::CloseUserStreamKey(const std::string &listenKey) {
    if (api_key_.empty()) {
        std::cerr << "<CloseUserStreamKey> API Key has not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/api/v3/userDataStream";
    std::string post_data = "listenKey=" + listenKey;
    Json::Value dummy_json; // Not used

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Delete(url, post_data, dummy_json, extra_http_header);
}

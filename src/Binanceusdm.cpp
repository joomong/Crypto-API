#include "Binanceusdm.h"
#include <iostream>

// Constructor
Binanceusdm::Binanceusdm(const std::string &api_key,
                         const std::string &api_secret,
                         bool sandbox)
    : api_key_(api_key),
      api_secret_(api_secret),
      use_sandbox_(sandbox),
      http_client_() {}

// Destructor
Binanceusdm::~Binanceusdm() {}

// Helper method to determine the Binance USDM API host
std::string Binanceusdm::getHost() const {
    // For sandbox usage, you can add:
    // if (use_sandbox_) return "https://testnet.binancefuture.com";
    return "https://fapi.binance.com";
}

// --------------------
// Public Market Endpoints
// --------------------
void Binanceusdm::GetServerTime(Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/time";
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetExchangeInfo(Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/exchangeInfo";
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetOrderBook(const std::string &symbol,
                               int limit,
                               Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/depth?symbol=" + symbol +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetRecentTrades(const std::string &symbol,
                                  int limit,
                                  Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/trades?symbol=" + symbol +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetOldTradeLookup(const std::string &symbol,
                                    int limit,
                                    Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/historicalTrades?symbol=" + symbol +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetAggTrades(const std::string &symbol,
                               int limit,
                               Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/aggTrades?symbol=" + symbol +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetKlines(const std::string &symbol,
                            const std::string &interval,
                            int limit,
                            Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/klines?symbol=" + symbol +
                      "&interval=" + interval +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetContinuousKlines(const std::string &symbol,
                                      const std::string &contractType,
                                      const std::string &interval,
                                      int limit,
                                      Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/continuousKlines?pair=" + symbol +
                      "&contractType=" + contractType +
                      "&interval=" + interval +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetIndexPriceKlines(const std::string &symbol,
                                      const std::string &interval,
                                      int limit,
                                      Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/indexPriceKlines?pair=" + symbol +
                      "&interval=" + interval +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetMarkPriceKlines(const std::string &symbol,
                                     const std::string &interval,
                                     int limit,
                                     Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/markPriceKlines?symbol=" + symbol +
                      "&interval=" + interval +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetFundRate(const std::string &symbol, Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/fundingRate?symbol=" + symbol;
    http_client_.Get(url, result_json);
}

void Binanceusdm::Get24hrTicker(const std::string &symbol, Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/ticker/24hr?symbol=" + symbol;
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetMarkPrice(const std::string &symbol, Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/premiumIndex?symbol=" + symbol;
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetPriceTicker(Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/ticker/price";
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetOrderBookTicker(const std::string &symbol,
                                     Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/ticker/bookTicker?symbol=" + symbol;
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetOpenInterest(const std::string &symbol,
                                  Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/openInterest?symbol=" + symbol;
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetOpenInterestStatistics(const std::string &symbol,
                                            const std::string &period,
                                            int limit,
                                            Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/openInterestHist?symbol=" + symbol +
                      "&period=" + period +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetTopTraderLongShortAccount(const std::string &symbol,
                                               const std::string &period,
                                               int limit,
                                               Json::Value &result_json) {
    std::string url = getHost() + "/futures/data/topLongShortAccountRatio?symbol=" + symbol +
                      "&period=" + period +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetTopTraderLongShortPosition(const std::string &symbol,
                                                const std::string &period,
                                                int limit,
                                                Json::Value &result_json) {
    std::string url = getHost() + "/futures/data/topLongShortPositionRatio?symbol=" + symbol +
                      "&period=" + period +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetLongShortRatio(const std::string &symbol,
                                    const std::string &period,
                                    int limit,
                                    Json::Value &result_json) {
    std::string url = getHost() + "/futures/data/globalLongShortAccountRatio?symbol=" + symbol +
                      "&period=" + period +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetBuySellVolume(const std::string &symbol,
                                   const std::string &period,
                                   int limit,
                                   Json::Value &result_json) {
    std::string url = getHost() + "/futures/data/takerlongshortRatio?symbol=" + symbol +
                      "&period=" + period +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetLvtKlines(const std::string &symbol,
                               const std::string &interval,
                               int limit,
                               Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/lvtKlines?symbol=" + symbol +
                      "&interval=" + interval +
                      "&limit=" + std::to_string(limit);
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetIndexInfo(const std::string &symbol,
                               Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/indexInfo?symbol=" + symbol;
    http_client_.Get(url, result_json);
}

void Binanceusdm::GetMultiModeAssetIndex(const std::string &symbol,
                                         Json::Value &result_json) {
    std::string url = getHost() + "/fapi/v1/assetIndex?symbol=" + symbol;
    http_client_.Get(url, result_json);
}

// --------------------
// Private (Signed) Endpoints
// --------------------

// Basic Limit Sell
void Binanceusdm::PostLimitSell(const std::string &symbol,
                                double quantity,
                                double price,
                                Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<PostLimitSell> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    // Create URL and query
    std::string url = getHost() + "/fapi/v1/order?";
    std::string post_data = "symbol=" + symbol +
                            "&side=SELL" +
                            "&type=LIMIT" +
                            "&timeInForce=GTC" +
                            "&quantity=" + std::to_string(quantity) +
                            "&price=" + std::to_string(price) +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    // Sign
    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    // Headers
    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    // Perform POST
    http_client_.Post(url, "", json_result, extra_http_header);
}

// Basic Limit Buy
void Binanceusdm::PostLimitBuy(const std::string &symbol,
                               double quantity,
                               double price,
                               Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<PostLimitBuy> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/fapi/v1/order?";
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

// Basic Market Buy
void Binanceusdm::PostMarketBuy(const std::string &symbol,
                                double quantity,
                                Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<PostMarketBuy> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/fapi/v1/order?";
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

// Basic Market Sell
void Binanceusdm::PostMarketSell(const std::string &symbol,
                                 double quantity,
                                 Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<PostMarketSell> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/fapi/v1/order?";
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

// Advanced Orders
void Binanceusdm::PostOrders(const std::string &symbol,
                             const std::string &side,
                             const std::string &type,
                             double quantity,
                             double price,
                             Json::Value &json_result,
                             const std::string &time_in_force,
                             const std::string &position_side,
                             const std::string &reduce_only,
                             const std::string &new_client_order_id,
                             double stop_price,
                             const std::string &close_position,
                             double activation_price,
                             double callback_rate,
                             const std::string &working_type,
                             const std::string &price_protect,
                             const std::string &new_order_resp_type,
                             double iceberg_qty,
                             long recv_window) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<PostOrders> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/fapi/v1/order?";
    // 필수
    std::string post_data = "symbol=" + symbol +
                            "&side=" + side +
                            "&type=" + type +
                            "&quantity=" + std::to_string(quantity) +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (!time_in_force.empty()) {
        post_data += "&timeInForce=" + time_in_force;
    }
    if (type != "MARKET") {
        post_data += "&price=" + std::to_string(price);
    }
    if (!position_side.empty()) {
        post_data += "&positionSide=" + position_side;
    }
    if (!reduce_only.empty()) {
        post_data += "&reduceOnly=" + reduce_only;
    }
    if (!new_client_order_id.empty()) {
        post_data += "&newClientOrderId=" + new_client_order_id;
    }
    if (stop_price > 0.0) {
        post_data += "&stopPrice=" + std::to_string(stop_price);
    }
    if (!close_position.empty()) {
        post_data += "&closePosition=" + close_position;
    }
    if (activation_price > 0.0) {
        post_data += "&activationPrice=" + std::to_string(activation_price);
    }
    if (callback_rate > 0.0) {
        post_data += "&callbackRate=" + std::to_string(callback_rate);
    }
    if (!working_type.empty()) {
        post_data += "&workingType=" + working_type;
    }
    if (!price_protect.empty()) {
        post_data += "&priceProtect=" + price_protect;
    }
    if (!new_order_resp_type.empty()) {
        post_data += "&newOrderRespType=" + new_order_resp_type;
    }
    if (iceberg_qty > 0.0) {
        post_data += "&icebergQty=" + std::to_string(iceberg_qty);
    }
    if (recv_window > 0) {
        post_data += "&recvWindow=" + std::to_string(recv_window);
    }

    // 서명
    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;

    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Post(url, "", json_result, extra_http_header);
}

// Modify Orders (PUT)
void Binanceusdm::ModifyOrder(const std::string &order_id,
                              const std::string &symbol,
                              const std::string &side,
                              double quantity,
                              double price,
                              Json::Value &json_result,
                              double recv_window,
                              const std::string &orig_client_order_id) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<ModifyOrder> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    // PUT Endpoint: /fapi/v1/order
    std::string url = getHost() + "/fapi/v1/order?";
    std::string post_data = "symbol=" + symbol +
                            "&side=" + side +
                            "&orderId=" + order_id +
                            "&price=" + std::to_string(price) +
                            "&quantity=" + std::to_string(quantity) +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (recv_window > 0) {
        post_data += "&recvWindow=" + std::to_string(static_cast<long>(recv_window));
    }
    if (!orig_client_order_id.empty()) {
        post_data += "&origClientOrderId=" + orig_client_order_id;
    }

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    // PUT request
    http_client_.Put(url, "", json_result, extra_http_header);
}

// Query Orders
void Binanceusdm::GetOrder(const std::string &symbol,
                           const std::string &order_id,
                           Json::Value &json_result,
                           long recv_window) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<GetOrder> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/fapi/v1/order?";
    std::string querystring = "symbol=" + symbol +
                              "&orderId=" + order_id +
                              "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (recv_window > 0) {
        querystring += "&recvWindow=" + std::to_string(recv_window);
    }

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Get(url, json_result, extra_http_header);
}

// Cancel
void Binanceusdm::CancelOrder(const std::string &symbol,
                              const std::string &order_id,
                              Json::Value &json_result,
                              long recv_window) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<CancelOrder> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/fapi/v1/order?";
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

void Binanceusdm::CancelAllOrders(const std::string &symbol,
                                  Json::Value &json_result,
                                  long recvWindow) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<CancelAllOrders> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/fapi/v1/allOpenOrders?";
    std::string post_data = "symbol=" + symbol +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (recvWindow > 0) {
        post_data += "&recvWindow=" + std::to_string(recvWindow);
    }

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Delete(url, "", json_result, extra_http_header);
}

void Binanceusdm::AutoCancelALLOpenOrders(const std::string &symbol,
                                          int countdownTime,
                                          Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<AutoCancelALLOpenOrders> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/fapi/v1/countdownCancelAll?";
    std::string post_data = "symbol=" + symbol +
                            "&countdownTime=" + std::to_string(countdownTime) +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Post(url, "", json_result, extra_http_header);
}

// Get Open Order
void Binanceusdm::GetOpenOrder(const std::string &symbol,
                               long order_id,
                               Json::Value &json_result,
                               long recv_window) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<GetOpenOrder> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/fapi/v1/openOrder?";
    std::string querystring = "symbol=" + symbol +
                              "&orderId=" + std::to_string(order_id) +
                              "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (recv_window > 0) {
        querystring += "&recvWindow=" + std::to_string(recv_window);
    }

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Get(url, json_result, extra_http_header);
}

void Binanceusdm::GetOpenOrders(const std::string &symbol,
                                Json::Value &json_result,
                                long recv_window) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<GetOpenOrders> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/fapi/v1/openOrders?";
    std::string querystring = "symbol=" + symbol +
                              "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    if (recv_window > 0) {
        querystring += "&recvWindow=" + std::to_string(recv_window);
    }

    std::string signature = Utils::hmac_sha256(querystring, api_secret_);
    querystring += "&signature=" + signature;
    url += querystring;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Get(url, json_result, extra_http_header);
}

// Account / Position
void Binanceusdm::ChangeLeverage(const std::string &symbol,
                                 int leverage,
                                 Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<ChangeLeverage> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/fapi/v1/leverage?";
    std::string post_data = "symbol=" + symbol +
                            "&leverage=" + std::to_string(leverage) +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Post(url, "", json_result, extra_http_header);
}

void Binanceusdm::ChangeMarginType(const std::string &symbol,
                                   const std::string &marginType,
                                   Json::Value &json_result) {
    if (api_key_.empty() || api_secret_.empty()) {
        std::cerr << "<ChangeMarginType> API Key and Secret Key have not been set." << std::endl;
        return;
    }

    std::string url = getHost() + "/fapi/v1/marginType?";
    std::string post_data = "symbol=" + symbol +
                            "&marginType=" + marginType +
                            "&timestamp=" + std::to_string(Utils::GetCurrentMsEpoch());

    std::string signature = Utils::hmac_sha256(post_data, api_secret_);
    post_data += "&signature=" + signature;
    url += post_data;

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Post(url, "", json_result, extra_http_header);
}

// User Stream
void Binanceusdm::GetUserStreamKey(Json::Value &json_result) {
    if (api_key_.empty()) {
        std::cerr << "<GetUserStreamKey> API Key has not been set." << std::endl;
        return;
    }

    // POST /fapi/v1/listenKey
    std::string url = getHost() + "/fapi/v1/listenKey";

    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Post(url, "", json_result, extra_http_header);
}

void Binanceusdm::KeepAliveUserStreamKey(const std::string &listenKey) {
    if (api_key_.empty()) {
        std::cerr << "<KeepAliveUserStreamKey> API Key has not been set." << std::endl;
        return;
    }

    // PUT /fapi/v1/listenKey
    std::string url = getHost() + "/fapi/v1/listenKey";
    std::string post_data = "listenKey=" + listenKey;

    // Dummy JSON result
    Json::Value dummy_result;
    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Put(url, post_data, dummy_result, extra_http_header);
}

void Binanceusdm::CloseUserStreamKey(const std::string &listenKey) {
    if (api_key_.empty()) {
        std::cerr << "<CloseUserStreamKey> API Key has not been set." << std::endl;
        return;
    }

    // DELETE /fapi/v1/listenKey
    std::string url = getHost() + "/fapi/v1/listenKey";
    std::string post_data = "listenKey=" + listenKey;

    Json::Value dummy_result;
    std::vector<std::string> extra_http_header = {
        "X-MBX-APIKEY: " + api_key_
    };

    http_client_.Delete(url, post_data, dummy_result, extra_http_header);
}

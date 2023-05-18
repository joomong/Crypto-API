#include "binanceusdm.h"

void Binanceusdm::GetServerTime(Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/time";
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binanceusdm::GetExchangeInfo(Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/exchangeInfo";
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binanceusdm::GetOrderBook(std::string &symbol,
                           int limit,
                           Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/depth?symbol=" + symbol + "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetRecentTrades(std::string &symbol,
                              int limit,
                              Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/trades?symbol=" + symbol +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetOldTradeLookup(std::string &symbol,
                              int limit,
                              Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/historicalTrades?symbol=" + symbol +
                  "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetAggTrades(std::string &symbol,
                           int limit,
                           Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/aggTrades?symbol=" + symbol +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binanceusdm::GetKlines(std::string &symbol,
                        std::string &interval,
                        int limit,
                        Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/klines?symbol=" + symbol + "&interval=" + interval +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetContinuousKlines(std::string &symbol, std::string &contractType,
                                std::string &interval, int limit,
                                Json::Value &result_json){
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/continuousKlines?symbol=" + symbol + "&interval=" + interval +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetIndexPriceKlines(std::string &symbol, std::string &interval, int limit,
                                Json::Value &result_json){
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/indexPriceKlines?symbol=" + symbol + "&interval=" + interval +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetMarkPriceKlines(std::string &symbol, std::string &interval, int limit,
                               Json::Value &result_json){
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/markPriceKlines?symbol=" + symbol + "&interval=" + interval +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetMarkPrice(std::string &symbol, Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/premiumIndex?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetFundRate(std::string &symbol, Json::Value &result_json){
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/fundingRate?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::Get24hrTicker(std::string &symbol, Json::Value &result_json){
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/ticker/24hr?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetPriceTicker(Json::Value &result_json){
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/ticker/price";
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binanceusdm::GetOrderBookTicker(std::string &symbol, Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/ticker/bookTicker?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetOpenInterest(std::string &symbol, Json::Value &result_json){
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/openInterest?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetOpenInterestStatistics(std::string &symbol, std::string &period, int limit,
                               Json::Value &result_json){
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/openInterestHist?symbol=" + symbol + "&period=" + period +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetTopTraderLongShortAccount(std::string &symbol, std::string &period, int limit,
                                Json::Value &result_json){
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/topLongShortAccountRatio?symbol=" + symbol + "&period=" + period +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetTopTraderLongShortPosition(std::string &symbol, std::string &period, int limit, Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/topLongShortPositionRatio?symbol=" + symbol + "&period=" + period +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetLongShortRatio(std::string &symbol, std::string &period, int limit, Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/globalLongShortAccountRatio?symbol=" + symbol + "&period=" + period +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetBuySellVolume(std::string &symbol, std::string &period, int limit, Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/takerlongshortRatio?symbol=" + symbol + "&period=" + period +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetLvtKlines(std::string &symbol, std::string &interval, int limit,
                  Json::Value &result_json){
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/lvtKlines?symbol=" + symbol + "&interval=" + interval +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetIndexInfo(std::string &symbol, Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/indexInfo?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetMultiModeAssetIndex(std::string &symbol, Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/fapi/v1/multiModeAssetIndex?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binanceusdm::PostLimitSell(const std::string &symbol,
                            const double &quantity,
                            const double &price,
                            Json::Value &json_result)
{
    std::string url(BINANCE_HOST);
    url += "/api/v3/order?";
    std::string action = "POST";
    std::string result;
    std::string post_data = "symbol=" + symbol + "&side=SELL" +
                            "&type=LIMIT" + "&timeInForce=GTC" +
                            "&quantity=" + std::to_string(quantity) +
                            "&price=" + std::to_string(price)
                            +"&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if (!str_result.empty()) {
        try {
            std::cout << str_result << std::endl;
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);
        } catch (std::exception &e) {
            std::cout << "<send_order> Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "<BinaCPP::send_order> Failed to get anything."
                  << std::endl;
    }
}


void Binanceusdm::PostLimitBuy(const std::string &symbol,
                           const double &quantity,
                           const double &price,
                           Json::Value &json_result)
{
    std::string url(BINANCE_HOST);
    url += "/api/v3/order?";
    std::string action = "POST";
    std::string result;
    std::string post_data = "symbol=" + symbol + "&side=BUY" +
                            "&type=LIMIT_MAKER" + "&timeInForce=GTC" +
                            "&quantity=" + std::to_string(quantity) +
                            "&price=" + std::to_string(price)
                            +"&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector<std::string> extra_http_header{"X-MBX-APIKEY: " + API_KEY};

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if (!str_result.empty()) {
        try {
            std::cout << str_result << std::endl;
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);
        } catch (std::exception &e) {
            std::cout << "<send_order> Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "<BinaCPP::send_order> Failed to get anything."
                  << std::endl;
    }
}


void Binanceusdm::PostMarketBuy(const std::string &symbol,
                            const double &quantity,
                            Json::Value &json_result)
{
    std::string url(BINANCE_HOST);
    url += "/api/v3/order?";
    std::string action = "POST";
    std::string result;
    std::string post_data = "symbol=" + symbol + "&side=BUY" +
                            "&type=MARKET" +
                            "&quantity=" + std::to_string(quantity) +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector<std::string> extra_http_header{"X-MBX-APIKEY: " + API_KEY};

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if (!str_result.empty()) {
        try {
            std::cout << str_result << std::endl;
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);
        } catch (std::exception &e) {
            std::cout << "<send_order> Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "<BinaCPP::send_order> Failed to get anything."
                  << std::endl;
    }
}


void Binanceusdm::PostMarketSell(const std::string &symbol,
                             const double &quantity,
                             Json::Value &json_result)
{
    std::string url(BINANCE_HOST);
    url += "/api/v3/order?";
    std::string action = "POST";
    std::string result;
    std::string post_data = "symbol=" + symbol + "&side=SELL" +
                            "&type=MARKET" +
                            "&quantity=" + std::to_string(quantity) +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector<std::string> extra_http_header{"X-MBX-APIKEY: " + API_KEY};

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if (!str_result.empty()) {
        try {
            std::cout << str_result << std::endl;
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);
        } catch (std::exception &e) {
            std::cout << "<send_order> Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "<BinaCPP::send_order> Failed to get anything."
                  << std::endl;
    }
}


void Binanceusdm::PostOrders(const std::string &symbol,
                         const std::string &side,
                         const std::string &type,
                         const std::string &time_in_force,
                         const double &quantity,
                         const double &price,
                         Json::Value &json_result,
                         const std::string &new_client_order_id,
                         const double &stop_price,
                         const double &iceberg_qty,
                         const long &recv_window)
{
    {
        if (API_KEY.empty() || API_SECRET.empty())
        {
            std::cout << "<BinaCPP::send_order> API Key and Secret Key has not been set."
                      << std::endl;
            return ;
        }

        std::string url(BINANCE_HOST);
        url += "/api/v3/order?";

        std::string action = "POST";

        std::string post_data = "symbol=" + symbol
                                + "&side=" + side
                                + "&type=" + type
                                + "&quantity=" + std::to_string(quantity);

        if(type != "MARKET")
        {
            post_data += "&timeInForce=" + time_in_force
                         + "&price=" + std::to_string(price);
        }

        if (!new_client_order_id.empty() > 0)
        {
            post_data += "&newClientOrderId=" + new_client_order_id;
        }

        if (stop_price > 0.0)
        {
            post_data += "&stopPrice=" + std::to_string(stop_price);
        }

        if (iceberg_qty > 0.0)
        {
            post_data += "&icebergQty=" + std::to_string(iceberg_qty);
        }

        if (recv_window > 0)
        {
            post_data += "&recvWindow=" + std::to_string(recv_window);
        }

        post_data += "&timestamp=" + std::to_string(GetCurrentMsEpoch());

        std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
        post_data += "&signature=" + signature;

        std::vector<std::string> extra_http_header{ "X-MBX-APIKEY: " + API_KEY};

        std::string str_result;
        CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

        if (!str_result.empty()) {
            try {
                std::cout << str_result << std::endl;
                Json::Reader reader;
                json_result.clear();
                reader.parse(str_result, json_result);
            } catch (std::exception &e) {
                std::cout << "<send_order> Error !" << e.what() << std::endl;
            }
        } else {
            std::cout << "<BinaCPP::send_order> Failed to get anything." << std::endl;
        }
    }
}


void Binanceusdm::CancelOrder(const std::string &symbol,
                          const std::string &order_id,
                          Json::Value &json_result,
                          const long &recvWindow)
{
    if ( API_KEY.empty() || API_SECRET.empty() ) {
        std::cout <<  "<BinaCPP::send_order> API Key and Secret Key has not been set."
                  <<  std::endl;
        return ;
    }

    std::string url = BINANCE_HOST;
    url += "/api/v3/order?";

    std::string action = "DELETE";

    std::string post_data = "symbol=" + symbol +
                            "&orderId=" + order_id +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    if (recvWindow > 0)
    {
        post_data.append("&recvWindow=");
        post_data.append(std::to_string(recvWindow));
    }


    std::string signature =  hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector <std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if ( !str_result.empty() )
    {
        try
        {
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result );

        } catch ( std::exception &e ) {
            std::cout <<  "Error !" <<
                    e.what() << std::endl;
        }
    } else
    {
        std::cout << "Failed to get anything." << std::endl;
    }
}


void Binanceusdm::CancelAllOrders(const std::string &symbol,
                              Json::Value &json_result,
                              const long &recvWindow)
{
    if (API_KEY.empty() || API_SECRET.empty())
    {
        std::cout << "API Key and Secret Key has not been set." << std::endl;
        return ;
    }

    std::string url = BINANCE_HOST;
    url += "/api/v3/openOrders?";

    std::string action = "DELETE";

    std::string post_data = "symbol=" + symbol +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    if (recvWindow > 0) {
        post_data.append("&recvWindow=");
        post_data.append(std::to_string(recvWindow));
    }


    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if (!str_result.empty()) {
        try {
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);

        } catch (std::exception &e) {
            std::cout << "Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "Failed to get anything." << std::endl;
    }
}

void Binanceusdm::ReplaceOrder(
        const std::string &symbol,
        const std::string &side,
        const std::string &type,
        const std::string &cancel_replace_mode, // must STOP_ON_FAILURE , ALLOW_FAILURE
        const double &quantity,
        const double &price,
        Json::Value &json_result,

        const std::string &time_in_force, // GTC, IOC, FOK
        const double &quote_order_qty, //ex usdt
        const std::string &cancel_new_client_order_id, //Used to uniquely identify this cancel. Automatically generated by default.
        const std::string &cancel_orig_client_order_id, //Either the cancelOrigClientOrderId or cancelOrderId must be provided. If both are provided, cancelOrderId takes precedence.
        const long &cancel_order_id, //Either the cancelOrigClientOrderId or cancelOrderId must be provided. If both are provided, cancelOrderId takes precedence.
        const std::string &new_client_order_id,
        const int &strategy_id,
        const int &strategy_type,
        const double &stop_price,
        const double &trailing_delta,
        const double &iceberg_qty,
        const std::string &new_order_resp_type, // ACK, RESULT, FULL?
        const std::string &self_trade_prevention_mode,
        const std::string &cancel_restrictions,
        const long &recv_window)
{
    if (API_KEY.empty()|| API_SECRET.empty())
    {
        std::cout <<  "<BinaCPP::replace_order> API Key and Secret Key has not been set."
                  << std::endl;
        return ;
    }
    std::string url(BINANCE_HOST);
    url += "/api/v3/cancelReplace?";

    std::string action("POST");

    std::string post_data = "symbol=" + std::string(symbol) +
                            "&side=" + std::string(side) +
                            "&type=" + std::string(type) +
                            "&cancelReplaceMode=" + std::string(cancel_replace_mode) +
                            "&quantity=" + std::to_string(quantity) +
                            "&price=" + std::to_string(price) +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    if (!time_in_force.empty()) {
        post_data.append("&timeInForce=");
        post_data.append(time_in_force);
    }

    if (quote_order_qty > 0) {
        post_data.append("&quoteOrderQty=");
        post_data.append(std::to_string(quote_order_qty));
    }

    if (!cancel_new_client_order_id.empty()) {
        post_data.append("&cancelNewClientOrderId=");
        post_data.append(cancel_new_client_order_id);
    }

    if (!cancel_orig_client_order_id.empty()) {
        post_data.append("&cancelOrigClientOrderId=");
        post_data.append(cancel_orig_client_order_id);
    }

    if (cancel_order_id > 0) {
        post_data.append("&cancelOrderId=");
        post_data.append(std::to_string(cancel_order_id));
    }

    if (!new_client_order_id.empty()) {
        post_data.append("&newClientOrderId=");
        post_data.append(new_client_order_id);
    }

    if (strategy_id > 0) {
        post_data.append("&strategyId=");
        post_data.append(std::to_string(strategy_id));
    }

    if (strategy_type > 0) {
        post_data.append("&strategyType=");
        post_data.append(std::to_string(strategy_type));
    }

    if (stop_price > 0) {
        post_data.append("&stopPrice=");
        post_data.append(std::to_string(stop_price));
    }

    if (trailing_delta > 0) {
        post_data.append("&trailingDelta=");
        post_data.append(std::to_string(trailing_delta));
    }

    if (iceberg_qty > 0) {
        post_data.append("&icebergQty=");
        post_data.append(std::to_string(iceberg_qty));
    }

    if (!new_order_resp_type.empty()) {
        post_data.append("&newOrderRespType=");
        post_data.append(new_order_resp_type);
    }

    if (!self_trade_prevention_mode.empty()) {
        post_data.append("&selfTradePrevention=");
        post_data.append(self_trade_prevention_mode);
    }

    if (!cancel_restrictions.empty()) {
        post_data.append("&cancelRestrictions=");
        post_data.append(cancel_restrictions);
    }


    if (recv_window > 0) {
        post_data.append("&recvWindow=");
        post_data.append(std::to_string(recv_window));
    }

    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if (!str_result.empty()) {
        try {
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);

        } catch (std::exception &e) {
            std::cout << "Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "Failed to get anything." << std::endl;
    }
}


void Binanceusdm::GetCurrentOpenOrders(const std::string &symbol,
                                   Json::Value &json_result)
{
    std::string url(BINANCE_HOST);
    url += "/api/v3/openOrders?" ;

    std::string action("GET");

    std::string post_data =
            "symbol=" + std::string(symbol) +
            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if (!str_result.empty()) {
        try {
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);

        } catch (std::exception &e) {
            std::cout << "Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "Failed to get anything." << std::endl;
    }
}



void Binanceusdm::GetOrders(const std::string &symbol,
                        Json::Value &json_result,
                        const long &orderId,
                        const long &startTime,
                        const long &endTime,
                        const long &limit,
                        const long &recvWindow)
{
    std::string url(BINANCE_HOST);
    url += "/api/v3/openOrders?";

    std::string action("GET");

    std::string post_data = "symbol=" + std::string(symbol) +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    if (orderId > 0) {
        post_data.append("&orderId=");
        post_data.append(std::to_string(orderId));
    }

    if (startTime > 0) {
        post_data.append("&startTime=");
        post_data.append(std::to_string(startTime));
    }

    if (endTime > 0) {
        post_data.append("&endTime=");
        post_data.append(std::to_string(endTime));
    }

    if (limit > 0) {
        post_data.append("&limit=");
        post_data.append(std::to_string(limit));
    }

    if (recvWindow > 0) {
        post_data.append("&recvWindow=");
        post_data.append(std::to_string(recvWindow));
    }

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if (!str_result.empty()) {
        try {
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);

        } catch (std::exception &e) {
            std::cout << "Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "Failed to get anything." << std::endl;
    }
}


void Binanceusdm::GetAccountInfo(Json::Value &json_result)
{

    std::string url(BINANCE_HOST);
    url += "/api/v3/Account?";

    std::string action("GET");

    std::string post_data = "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if (!str_result.empty()) {
        try {
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);

        } catch (std::exception &e) {
            std::cout << "Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "Failed to get anything." << std::endl;
    }
}

void Binanceusdm::GetAccountTradeList(const std::string &symbol,
                                  Json::Value &json_result,
                                  const long &orderId,
                                  const long &startTime,
                                  const long &endTime,
                                  const long &fromId,
                                  const int &limit,
                                  const long &recvWindow)
{
    std::string url(BINANCE_HOST);
    url += "/api/v3/myTrades?";

    std::string action("GET");

    std::string post_data = "symbol=" + std::string(symbol) +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    if (orderId > 0) {
        post_data.append("&orderId=");
        post_data.append(std::to_string(orderId));
    }

    if (startTime > 0) {
        post_data.append("&startTime=");
        post_data.append(std::to_string(startTime));
    }

    if (endTime > 0) {
        post_data.append("&endTime=");
        post_data.append(std::to_string(endTime));
    }

    if (fromId > 0) {
        post_data.append("&fromId=");
        post_data.append(std::to_string(fromId));
    }

    if (limit > 0) {
        post_data.append("&limit=");
        post_data.append(std::to_string(limit));
    }

    if (recvWindow > 0) {
        post_data.append("&recvWindow=");
        post_data.append(std::to_string(recvWindow));
    }

    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if (!str_result.empty()) {
        try {
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);

        } catch (std::exception &e) {
            std::cout << "Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "Failed to get anything." << std::endl;
    }
}

void Binanceusdm::GetUserStreamKey(Json::Value &json_result)
{
    if (API_KEY.empty()) {
        std::cout << "<BinaCPP::start_userDataStream> API Key has not been set."
                  << std::endl;
        return;
    }


    std::string url(BINANCE_HOST);
    url += "/api/v1/userDataStream?";

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");


    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string action = "POST";
    std::string post_data;

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if (!str_result.empty()) {

        try {
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);

        } catch (std::exception &e) {
            std::cout << "<BinaCPP::start_userDataStream> Error ! " << e.what()
                      <<std::endl;
        }
    } else {
        std::cout << "<BinaCPP::start_userDataStream> Failed to get anything."
                  << std::endl;
    }
}


void Binanceusdm::KeepAliveUserStreamKey(const std::string &listenKey)
{
    if (API_KEY.empty()) {
        std::cout << "<BinaCPP::keep_userDataStream> API Key has not been set."
                  << std::endl;
        return ;
    }


    std::string url(BINANCE_HOST);
    url += "/api/v1/userDataStream?";

    std::vector <std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");


    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string action = "PUT";
    std::string post_data("listenKey=");
    post_data.append(listenKey);

    std::string str_result;
    CurlApiWithHeader( url, str_result , extra_http_header , post_data , action ) ;

    if ( str_result.empty() )
    {
        std::cout <<  "<BinaCPP::keep_userDataStream> Failed to get anything."
                  << std::endl;
    }
}


void Binanceusdm::CloseUserStreamKey(const std::string &listenKey)
{
    if ( API_KEY.empty() ) {
        std::cout << "<BinaCPP::close_userDataStream> API Key has not been set."
                  << std::endl;
        return ;
    }


    std::string url(BINANCE_HOST);
    url += "/api/v1/userDataStream?";

    std::vector <std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");


    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string action = "DELETE";
    std::string post_data("listenKey=");
    post_data.append( listenKey );

    std::string str_result;
    CurlApiWithHeader( url, str_result , extra_http_header , post_data , action ) ;

    if ( str_result.empty() )
    {
        std::cout << "<BinaCPP::close_userDataStream> Failed to get anything."
                  << std::endl;
    }
}

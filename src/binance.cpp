#include "binance.h"

void Binance::GetServerTime(Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/api/v3/time";
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binance::GetExchangeInfo(Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/api/v3/exchangeInfo";
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binance::GetOrderBook(std::string &symbol,
                           int limit,
                           Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/api/v3/depth?symbol=" + symbol + "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binance::GetRecentTrades(std::string &symbol,
                              int limit,
                              Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/api/v3/historicalTrades?symbol=" + symbol +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binance::GetAggTrades(std::string &symbol,
                           int limit,
                           Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/api/v3/aggTrades?symbol=" + symbol +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binance::GetKlines(std::string &symbol,
                        std::string &interval,
                        int limit,
                        Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/api/v3/klines?symbol=" + symbol + "&interval=" + interval +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binance::GetAvgPrice(std::string &symbol, Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/api/v3/avgPrice?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binance::Get24hrTicker(std::string &symbol, Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/api/v3/ticker/24hr?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binance::GetPriceTicker(Json::Value &result_json) {
    std::string url = BINANCE_HOST;
    url += "/api/v3/ticker/price";
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binance::GetBookTicker(Json::Value &result_json)
{
    std::string url = BINANCE_HOST;
    url += "/api/v3/ticker/bookTicker";
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binance::GetRolling24hrTicker(Json::Value &result_json)
{
    std::string url = BINANCE_HOST;
    url += "/api/v3/ticker/24hr";
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binance::PostLimitSell(const std::string &symbol,
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
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);
        } catch (std::exception &e) {
            std::cout << "<send_order> Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "<send_order> Failed to get anything."
                  << std::endl;
    }
}


void Binance::PostLimitBuy(const std::string &symbol,
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
            Json::Reader reader;
            json_result.clear();
            reader.parse(str_result, json_result);
        } catch (std::exception &e) {
            std::cout << "<send_order> Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "<send_order> Failed to get anything."
                  << std::endl;
    }
}


void Binance::PostMarketBuy(const std::string &symbol,
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


void Binance::PostMarketSell(const std::string &symbol,
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


void Binance::PostOrders(const std::string &symbol, 
                         const std::string &side,
                         const std::string &type,
                         const double &quantity,
                         const double &price,
                         Json::Value &json_result,
                         const std::string &time_in_force,
                         const std::string &new_client_order_id,
                         const double &stop_price,
                         const double &iceberg_qty,
                         const long &recv_window)
{
    {
        if (API_KEY.empty() || API_SECRET.empty())
        {
            std::cout << "API Key and Secret Key has not been set."
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
                Json::Reader reader;
                json_result.clear();
                reader.parse(str_result, json_result);
            } catch (std::exception &e) {
               std::cout << "<send_order> Error !" << e.what() << std::endl;
            }
        } else {
           std::cout << "<send_order> Failed to get anything." << std::endl;
        }
    }
}


void Binance::CancelOrder(const std::string &symbol,
                          const std::string &order_id,
                          Json::Value &json_result,
                          const long &recvWindow)
{
    if ( API_KEY.empty() || API_SECRET.empty() ) {
        std::cout <<  "API Key and Secret Key has not been set."
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


void Binance::CancelAllOrders(const std::string &symbol,
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

void Binance::ReplaceOrder(
        const std::string &symbol, 
        const std::string &side,
        const std::string &type,
        const std::string &cancel_replace_mode,
        const double &quantity, 
        const double &price,
        Json::Value &json_result,
        const std::string &time_in_force,
        const double &quote_order_qty,
        const std::string &cancel_new_client_order_id,
        const std::string &cancel_orig_client_order_id,
        const long &cancel_order_id,
        const std::string &new_client_order_id,
        const int &strategy_id,
        const int &strategy_type,
        const double &stop_price,
        const double &trailing_delta, 
        const double &iceberg_qty,
        const std::string &new_order_resp_type,
        const std::string &self_trade_prevention_mode,
        const std::string &cancel_restrictions,
        const long &recv_window)
{
    if (API_KEY.empty()|| API_SECRET.empty()) 
    {
        std::cout <<  "<replace_order> API Key and Secret Key has not been set."
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


void Binance::GetCurrentOpenOrders(const std::string &symbol,
                             Json::Value &json_result)
{
    std::string url(BINANCE_HOST);
    url += "/api/v3/openOrders?";

    std::string action("GET");

    std::string querystring =
            "symbol=" + symbol +
            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(querystring.c_str(),API_SECRET.c_str());
    querystring += "&signature=" + signature;

    url += querystring;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string post_data;

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



void Binance::GetOrders(const std::string &symbol, 
                        Json::Value &json_result,
                        const long &orderId,
                        const long &startTime,
                        const long &endTime,
                        const long &limit,
                        const long &recvWindow)
{
    std::string url(BINANCE_HOST);
    url += "/api/v3/allOrders?";
    std::string action("GET");
    std::string post_data;
    std::string querystring = "symbol=" + std::string(symbol) +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());
    std::string signature = hmac_sha256(querystring.c_str(),API_SECRET.c_str());
    querystring += "&signature=" + signature;

    if (orderId > 0) {
        querystring.append("&orderId=");
        post_data.append(std::to_string(orderId));
    }

    if (startTime > 0) {
        querystring.append("&startTime=");
        querystring.append(std::to_string(startTime));
    }

    if (endTime > 0) {
        querystring.append("&endTime=");
        querystring.append(std::to_string(endTime));
    }

    if (limit > 0) {
        querystring.append("&limit=");
        querystring.append(std::to_string(limit));
    }

    if (recvWindow > 0) {
        querystring.append("&recvWindow=");
        querystring.append(std::to_string(recvWindow));
    }

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    url += querystring;

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


void Binance::GetAccountInfo(Json::Value &json_result)
{

    std::string url(BINANCE_HOST);
    url += "/api/v3/account?";

    std::string action("GET");

    std::string post_data;

    std::string querystring = "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(querystring.c_str(),API_SECRET.c_str());
    querystring += "&signature=" + signature;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    url += querystring;

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

void Binance::GetAccountTradeList(const std::string &symbol,
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

    std::string querystring = "symbol=" + std::string(symbol) +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());
    
    if (orderId > 0) {
        querystring.append("&orderId=");
        querystring.append(std::to_string(orderId));
    }

    if (startTime > 0) {
        querystring.append("&startTime=");
        querystring.append(std::to_string(startTime));
    }

    if (endTime > 0) {
        querystring.append("&endTime=");
        querystring.append(std::to_string(endTime));
    }

    if (fromId > 0) {
        querystring.append("&fromId=");
        querystring.append(std::to_string(fromId));
    }

    if (limit > 0) {
        querystring.append("&limit=");
        querystring.append(std::to_string(limit));
    }

    if (recvWindow > 0) {
        querystring.append("&recvWindow=");
        querystring.append(std::to_string(recvWindow));
    }

    std::string signature = hmac_sha256(querystring.c_str(),API_SECRET.c_str());
    querystring += "&signature=" + signature;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);
    std::string post_data;

    url += querystring;

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

void Binance::GetUserStreamKey(Json::Value &json_result)
{
    if (API_KEY.empty()) {
        std::cout << "API Key has not been set."
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
            std::cout << "start_userDataStream Error ! " << e.what()
            <<std::endl;
        }
    } else {
            std::cout << "<start_userDataStream> Failed to get anything."
            << std::endl;
    }
}


void Binance::KeepAliveUserStreamKey(const std::string &listenKey)
{
    if (API_KEY.empty()) {
        std::cout << "<keep_userDataStream> API Key has not been set."
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
        std::cout <<  "<keep_userDataStream> Failed to get anything."
        << std::endl;
    }
}


void Binance::CloseUserStreamKey(const std::string &listenKey)
{
    if ( API_KEY.empty() ) {
        std::cout << "<close_userDataStream> API Key has not been set."
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
        std::cout << "<close_userDataStream> Failed to get anything."
        << std::endl;
    }
}

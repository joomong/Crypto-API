#include "binanceusdm.h"

void Binanceusdm::GetServerTime(Json::Value &result_json)
{
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/time";
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binanceusdm::GetExchangeInfo(Json::Value &result_json)
{
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/exchangeInfo";
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binanceusdm::GetOrderBook(std::string &symbol,
                           int limit,
                           Json::Value &result_json)
{
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/depth?symbol=" + symbol + "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetRecentTrades(std::string &symbol,
                              int limit,
                              Json::Value &result_json)
{
    std::string url = BINANCEUSDM_HOST;
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
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/historicalTrades?" + symbol +
                  "&limit=" + std::to_string(limit);
    std::cout << url << std::endl;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetAggTrades(std::string &symbol,
                           int limit,
                           Json::Value &result_json) {
    std::string url = BINANCEUSDM_HOST;
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
                            Json::Value &result_json)
{
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/klines?symbol=" + symbol + "&interval=" + interval +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetContinuousKlines(std::string &symbol, std::string &contractType,
                                    std::string &interval, int limit,
                                    Json::Value &result_json)
{
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/continuousKlines?pair=" + symbol + "&contractType=" + contractType +
           "&interval=" + interval +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetIndexPriceKlines(std::string &symbol, std::string &interval, int limit,
                                Json::Value &result_json){
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/indexPriceKlines?pair=" + symbol + "&interval=" + interval +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetMarkPriceKlines(std::string &symbol, std::string &interval, int limit,
                               Json::Value &result_json){
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/markPriceKlines?symbol=" + symbol + "&interval=" + interval +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetMarkPrice(std::string &symbol, Json::Value &result_json) {
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/premiumIndex?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetFundRate(std::string &symbol, Json::Value &result_json){
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/fundingRate?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::Get24hrTicker(std::string &symbol, Json::Value &result_json){
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/ticker/24hr?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetPriceTicker(Json::Value &result_json){
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/ticker/price";
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}


void Binanceusdm::GetOrderBookTicker(std::string &symbol, Json::Value &result_json) {
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/ticker/bookTicker?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetOpenInterest(std::string &symbol, Json::Value &result_json){
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/openInterest?symbol=" + symbol;
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetOpenInterestStatistics(std::string &symbol, std::string &period, int limit,
                               Json::Value &result_json){
    std::string url = BINANCEUSDM_HOST;
    url += "/futures/data/openInterestHist?symbol=" + symbol + "&period=" + period +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetTopTraderLongShortAccount(std::string &symbol, std::string &period, int limit,
                                Json::Value &result_json){
    std::string url = BINANCEUSDM_HOST;
    url += "/futures/data/topLongShortAccountRatio?symbol=" + symbol + "&period=" + period +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetTopTraderLongShortPosition(std::string &symbol, std::string &period, int limit, Json::Value &result_json) {
    std::string url = BINANCEUSDM_HOST;
    url += "/futures/data/topLongShortPositionRatio?symbol=" + symbol + "&period=" + period +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetLongShortRatio(std::string &symbol, std::string &period, int limit, Json::Value &result_json) {
    std::string url = BINANCEUSDM_HOST;
    url += "/futures/data/globalLongShortAccountRatio?symbol=" + symbol + "&period=" + period +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetBuySellVolume(std::string &symbol, std::string &period, int limit, Json::Value &result_json) {
    std::string url = BINANCEUSDM_HOST;
    url += "/futures/data/takerlongshortRatio?symbol=" + symbol + "&period=" + period +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetLvtKlines(std::string &symbol, std::string &interval, int limit,
                  Json::Value &result_json){
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/lvtKlines?symbol=" + symbol + "&interval=" + interval +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetIndexInfo(std::string &symbol, Json::Value &result_json)
{
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/indexInfo?symbol=" + symbol;
    //TODO: invalid symbol
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Binanceusdm::GetMultiModeAssetIndex(std::string &symbol, Json::Value &result_json) {
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/assetIndex?symbol=" + symbol;
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
    std::string url(BINANCEUSDM_HOST);
    url += "/fapi/v1/order?";
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
    std::string url(BINANCEUSDM_HOST);
    url += "/fapi/v1/order?";
    std::string action = "POST";
    std::string result;
    std::string post_data = "symbol=" + symbol + "&side=BUY" +
                            "&type=LIMIT" + "&timeInForce=GTC" +
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
    std::string url(BINANCEUSDM_HOST);
    url += "/fapi/v1/order?";
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
        std::cout << "<send_order> Failed to get anything."
                  << std::endl;
    }
}


void Binanceusdm::PostMarketSell(const std::string &symbol,
                             const double &quantity,
                             Json::Value &json_result)
{
    std::string url(BINANCEUSDM_HOST);
    url += "/fapi/v1/order?";
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
        std::cout << "<send_order> Failed to get anything."
                  << std::endl;
    }
}


void Binanceusdm::PostOrders(const std::string &symbol,
                            const std::string &side,
                            const std::string &type,
                            const double &quantity,
                            Json::Value &json_result,
                            const double &price,
                            const std::string &time_in_force,
                            const std::string &position_side,
                            const std::string &reduce_only,
                            const std::string &new_client_order_id,
                            const double &stop_price,
                            const std::string &close_position,
                            const double &activation_price,
                            const double &callback_rate,
                            const std::string &working_type,
                            const std::string &price_protect,
                            const std::string &new_order_resp_type,
                            const double &iceberg_qty,
                            const long &recv_window)
{
    {
        if (API_KEY.empty() || API_SECRET.empty())
        {
            std::cout << "<send_order> API Key and Secret Key has not been set."
                      << std::endl;
            return ;
        }

        std::string url(BINANCEUSDM_HOST);
        url += "/fapi/v1/order?";

        std::string action = "POST";

        std::string post_data = "symbol=" + symbol
                                + "&side=" + side
                                + "&type=" + type
                                + "&quantity=" + std::to_string(quantity);
        if(!position_side.empty())
        {
            post_data += "&positionSide=" + position_side;
        }

        if(type != "MARKET")
        {
            post_data += "&timeInForce=" + time_in_force
                         + "&price=" + std::to_string(price);
        }

        if (!new_client_order_id.empty())
        {
            post_data += "&newClientOrderId=" + new_client_order_id;
        }

        if (!reduce_only.empty())
        {
            post_data += "&reduceOnly=" + reduce_only;
        }

        if (stop_price > 0.0)
        {
            post_data += "&stopPrice=" + std::to_string(stop_price);
        }

        if (!close_position.empty())
        {
            post_data += "&closePosition=" + close_position;
        }

        if (activation_price > 0.0)
        {
            post_data += "&activationPrice=" + std::to_string(activation_price);
        }

        if (callback_rate > 0.0)
        {
            post_data += "&callbackRate=" + std::to_string(callback_rate);
        }

        if (!working_type.empty())
        {
            post_data += "&workingType=" + working_type;
        }

        if (!price_protect.empty())
        {
            post_data += "&priceProtect=" + price_protect;
        }

        if (!new_order_resp_type.empty())
        {
            post_data += "&newOrderRespType=" + new_order_resp_type;
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
            std::cout << "<send_order> Failed to get anything." << std::endl;
        }
    }
}
void Binanceusdm::ModifyOrder(const std::string &order_id,
                              const std::string &symbol,
                              const std::string &side,
                              const double &quantity,
                              const double &price,
                              Json::Value &json_result,
                              const double &recv_window,
                              const std::string &orig_client_order_id)
{
    if (API_KEY.empty() || API_SECRET.empty())
    {
        std::cout << "<modify_order> API Key and Secret Key has not been set." << std::endl;
        return;
    }
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/order?";
    std::string action = "PUT";
    std::string post_data = "symbol=" + symbol
                            + "&orderId=" + order_id
                            + "&price=" + std::to_string(price)
                            + "&side=" + side
                            + "&quantity=" + std::to_string(quantity)
                            + "&timestamp=" + std::to_string(GetCurrentMsEpoch());
    if (recv_window > 0)
    {
        post_data += "&recvWindow=" + std::to_string(recv_window);
    }

    if (!orig_client_order_id.empty())
    {
        post_data += "&origClientOrderId=" + orig_client_order_id;
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


void Binanceusdm::GetOrder(const std::string &symbol,
                           const std::string &order_id,
                           Json::Value &json_result,
                           const long &recv_window)
{
   if(API_KEY.empty() || API_SECRET.empty())
   {
      std::cout << "<get_order> API Key and Secret Key has not been set." << std::endl;
      return;
   }
    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/order?";
    std::string action = "GET";
    std::string querystring = "symbol=" + symbol
                            + "&orderId=" + order_id
                            + "&timestamp=" + std::to_string(GetCurrentMsEpoch());
    if (recv_window > 0)
    {
        querystring.append("&recvWindow=");
        querystring.append(std::to_string(recv_window));
    }

    std::string signature = hmac_sha256(querystring.c_str(),API_SECRET.c_str());
    querystring += "&signature=" + signature;

    url += querystring;

    std::vector <std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string post_data;

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

void Binanceusdm::CancelOrder(const std::string &symbol,
                              const std::string &order_id,
                              Json::Value &json_result,
                              const long &recvWindow)
{
    if ( API_KEY.empty() || API_SECRET.empty() ) {
        std::cout <<  "<send_order> API Key and Secret Key has not been set."
                  <<  std::endl;
        return ;
    }

    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/order?";

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

    std::string url = BINANCEUSDM_HOST;
    url += "/fapi/v1/allOpenOrders?";

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

void Binanceusdm::AutoCancelALLOpenOrders(const std::string &symbol,
                                          const int &countdownTime,
                                          Json::Value &json_result)
{
    std::string url(BINANCEUSDM_HOST);
    url += "/fapi/v1/countdownCancelAll?";
    std::string action("POST");

    std::string post_data = "symbol=" + symbol +
                            "&countdownTime=" + std::to_string(countdownTime) +
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


void Binanceusdm::GetOpenOrder(const std::string &symbol,
                               const long &order_id,
                               Json::Value &json_result,
                               const long &recv_window)
{
    std::string url(BINANCEUSDM_HOST);
    url += "/fapi/v1/openOrder?";
    std::string action("GET");

    std::string querystring = "symbol=" + symbol +
                            "&orderId=" + std::to_string(order_id) +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());
    std::string signature = hmac_sha256(querystring.c_str(),API_SECRET.c_str());
    querystring += "&signature=" + signature;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("x-mbx-apikey: ");
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
            std::cout << "error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "failed to get anything." << std::endl;
    }
}

void Binanceusdm::GetOpenOrders(const std::string &symbol,
                                Json::Value &json_result,
                                const long &recv_window)
{
    std::string url(BINANCEUSDM_HOST);
    url += "/fapi/v1/openOrders?";
    std::string action("GET");

    std::string querystring = "symbol=" + symbol +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    if (recv_window > 0)
    {
        querystring.append("&recvWindow=");
        querystring.append(std::to_string(recv_window));
    }
    std::string signature = hmac_sha256(querystring.c_str(),API_SECRET.c_str());
    querystring += "&signature=" + signature;
    url += querystring;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("x-mbx-apikey: ");
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
            std::cout << "error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "failed to get anything." << std::endl;
    }
}

void Binanceusdm::ChangeLeverage(const std::string &symbol,
                                 const int &leverage,
                                 Json::Value &json_result)
{
    std::string url(BINANCEUSDM_HOST);
    url += "/fapi/v1/leverage?";
    std::string action("POST");

    std::string post_data = "symbol=" + symbol +
                            "&leverage=" + std::to_string(leverage) +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());
    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("x-mbx-apikey: ");
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
            std::cout << "error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "failed to get anything." << std::endl;
    }
}


void Binanceusdm::ChangeMarginType(const std::string &symbol,
                                   const std::string &marginType,
                                   Json::Value &json_result)
{
    std::string url(BINANCEUSDM_HOST);
    url += "/fapi/v1/marginType?";
    std::string action("POST");
    std::string post_data = "symbol=" + symbol +
                            "&marginType=" + marginType +
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


//void Binanceusdm::GetAccountInfo(Json::Value &json_result)
//{
//
//    std::string url(BINANCE_HOST);
//    url += "/api/v3/Account?";
//
//    std::string action("GET");
//
//    std::string post_data = "&timestamp=" + std::to_string(GetCurrentMsEpoch());
//
//    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
//    post_data += "&signature=" + signature;
//
//    std::vector<std::string> extra_http_header;
//    std::string header_chunk("X-MBX-APIKEY: ");
//    header_chunk.append(API_KEY);
//    extra_http_header.push_back(header_chunk);
//
//    std::string str_result;
//    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);
//
//    if (!str_result.empty()) {
//        try {
//            Json::Reader reader;
//            json_result.clear();
//            reader.parse(str_result, json_result);
//
//        } catch (std::exception &e) {
//            std::cout << "Error !" << e.what() << std::endl;
//        }
//    } else {
//        std::cout << "Failed to get anything." << std::endl;
//    }
//}

//void Binanceusdm::GetAccountTradeList(const std::string &symbol,
//                                  Json::Value &json_result,
//                                  const long &orderId,
//                                  const long &startTime,
//                                  const long &endTime,
//                                  const long &fromId,
//                                  const int &limit,
//                                  const long &recvWindow)
//{
//    std::string url(BINANCE_HOST);
//    url += "/api/v3/myTrades?";
//
//    std::string action("GET");
//
//    std::string post_data = "symbol=" + std::string(symbol) +
//                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());
//
//    if (orderId > 0) {
//        post_data.append("&orderId=");
//        post_data.append(std::to_string(orderId));
//    }
//
//    if (startTime > 0) {
//        post_data.append("&startTime=");
//        post_data.append(std::to_string(startTime));
//    }
//
//    if (endTime > 0) {
//        post_data.append("&endTime=");
//        post_data.append(std::to_string(endTime));
//    }
//
//    if (fromId > 0) {
//        post_data.append("&fromId=");
//        post_data.append(std::to_string(fromId));
//    }
//
//    if (limit > 0) {
//        post_data.append("&limit=");
//        post_data.append(std::to_string(limit));
//    }
//
//    if (recvWindow > 0) {
//        post_data.append("&recvWindow=");
//        post_data.append(std::to_string(recvWindow));
//    }
//
//    std::string signature = hmac_sha256(post_data.c_str(),API_SECRET.c_str());
//    post_data += "&signature=" + signature;
//
//    std::vector<std::string> extra_http_header;
//    std::string header_chunk("X-MBX-APIKEY: ");
//    header_chunk.append(API_KEY);
//    extra_http_header.push_back(header_chunk);
//
//    std::string str_result;
//    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);
//
//    if (!str_result.empty()) {
//        try {
//            Json::Reader reader;
//            json_result.clear();
//            reader.parse(str_result, json_result);
//
//        } catch (std::exception &e) {
//            std::cout << "Error !" << e.what() << std::endl;
//        }
//    } else {
//        std::cout << "Failed to get anything." << std::endl;
//    }
//}

void Binanceusdm::GetUserStreamKey(Json::Value &json_result)
{
    if (API_KEY.empty()) {
        std::cout << "<start_userDataStream> API Key has not been set."
                  << std::endl;
        return;
    }

    std::string url(BINANCEUSDM_HOST);
    url += "/fapi/v1/listenKey?";

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
        std::cout << "<keep_userDataStream> API Key has not been set."
                  << std::endl;
        return ;
    }

    std::string url(BINANCEUSDM_HOST);
    url += "/fapi/v1/listenKey?";

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


void Binanceusdm::CloseUserStreamKey(const std::string &listenKey)
{
    if ( API_KEY.empty() ) {
        std::cout << "<close_userDataStream> API Key has not been set."
                  << std::endl;
        return ;
    }


    std::string url(BINANCEUSDM_HOST);
    url += "/fapi/v1/listenKey?";

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

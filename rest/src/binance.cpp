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
    url += "/api/v3/order";
    std::string action = "POST";
    std::string result;
    std::string post_data = "symbol=" + symbol + "&side=SELL" +
                            "&type=LIMIT_MAKER" + "&timeInForce=GTC" +
                            "&quantity=" + std::to_string(quantity) +
                            "&price=" + std::to_string(price)
                            +"&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(API_SECRET.c_str(), post_data.c_str());
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


void Binance::PostLimitBuy(const std::string &symbol,
                                 const double &quantity,
                                 const double &price,
                                 Json::Value &json_result)
{
    std::string url(BINANCE_HOST);
    url += "/api/v3/order";
    std::string action = "POST";
    std::string result;
    std::string post_data = "symbol=" + symbol + "&side=BUY" +
                            "&type=LIMIT_MAKER" + "&timeInForce=GTC" +
                            "&quantity=" + std::to_string(quantity) +
                            "&price=" + std::to_string(price)
                            +"&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(API_SECRET.c_str(), post_data.c_str());
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


void Binance::PostMarketBuy(const std::string &symbol,
                                const double &quantity,
                                Json::Value &json_result) 
{
    std::string url(BINANCE_HOST);
    url += "/api/v3/order";
    std::string action = "POST";
    std::string result;
    std::string post_data = "symbol=" + symbol + "&side=BUY" +
                            "&type=MARKET" +
                            "&quantity=" + std::to_string(quantity) +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(API_SECRET.c_str(), post_data.c_str());
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
    url += "/api/v3/order";
    std::string action = "POST";
    std::string result;
    std::string post_data = "symbol=" + symbol + "&side=SELL" +
                            "&type=MARKET" +
                            "&quantity=" + std::to_string(quantity) +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(API_SECRET.c_str(), post_data.c_str());
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

        std::string signature = hmac_sha256(API_SECRET.c_str(), post_data.c_str());
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


void Binance::CancelOrder(const std::string &symbol,
                          const std::string &order_id,
                          Json::Value &json_result,
                          const long recvWindow)
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
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());;

    if (recvWindow > 0) 
    {
        post_data.append("&recvWindow=");
        post_data.append(std::to_string(recvWindow));
    }


    std::string signature =  hmac_sha256( API_SECRET.c_str(), post_data.c_str() );
    post_data += "&signature=" + signature;

    std::vector <std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if ( str_result.size() > 0 ) 
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
                              const long recvWindow)
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
    ;

    if (recvWindow > 0) {
        post_data.append("&recvWindow=");
        post_data.append(std::to_string(recvWindow));
    }


    std::string signature = hmac_sha256(API_SECRET.c_str(), post_data.c_str());
    post_data += "&signature=" + signature;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append(API_KEY);
    extra_http_header.push_back(header_chunk);

    std::string str_result;
    CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

    if (str_result.size() > 0) {
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


void ReplaceOrder(const char *symbol, 
                  const char *origClientOrderId,
                  const char *orderId, 
                  const char *side, 
                  const char *type,
                  const char *timeInForce, 
                  double quantity, 
                  double price,
                  const char *newClientOrderId, 
                  double stopPrice,
                  double icebergQty, 
                  long recvWindow, 
                  Json::Value &json_result)
{







}


void GetCurrentOpenOrders(const char *symbol, 
                          long recvWindow,
                          Json::Value &json_result)
{





}



void GetOrders(const char *symbol, 
                  long orderId, 
                  long startTime, 
                  long endTime,
                  long limit, 
                  long recvWindow, 
                  Json::Value &json_result)
{



}


void GetAccountInfo(long recvWindow, Json::Value &json_result)
{



}


void GetCurrentOpenOrders(const char *symbol, long recvWindow,
                          Json::Value &json_result)
{





}


void Binance::KeepAliveUserStreamKey(const char *listenKey, long recvWindow, Json::Value &json_result)
{
    BinaCPP_logger::write_log( "<BinaCPP::keep_userDataStream>" ) ;

    if ( api_key.size() == 0 ) {
        BinaCPP_logger::write_log( "<BinaCPP::keep_userDataStream> API Key has not been set." ) ;
        return ;
    }


    string url(BINANCE_HOST);
    url += "/api/v1/userDataStream";

    vector <string> extra_http_header;
    string header_chunk("X-MBX-APIKEY: ");


    header_chunk.append( api_key );
    extra_http_header.push_back(header_chunk);

    string action = "PUT";
    string post_data("listenKey=");
    post_data.append( listenKey );

    BinaCPP_logger::write_log( "<BinaCPP::keep_userDataStream> url = |%s|, post_data = |%s|" , url.c_str() , post_data.c_str() ) ;

    string str_result;
    curl_api_with_header( url, str_result , extra_http_header , post_data , action ) ;

    if ( str_result.size() > 0 ) {

        BinaCPP_logger::write_log( "<BinaCPP::keep_userDataStream> Done." ) ;

    } else {
        BinaCPP_logger::write_log( "<BinaCPP::keep_userDataStream> Failed to get anything." ) ;
    }

    BinaCPP_logger::write_log( "<BinaCPP::keep_userDataStream> Done.\n" ) ;

}


void Binance::CloseUserStreamKey( const char *listenKey )
{
    BinaCPP_logger::write_log( "<BinaCPP::close_userDataStream>" ) ;

    if ( api_key.size() == 0 ) {
        BinaCPP_logger::write_log( "<BinaCPP::close_userDataStream> API Key has not been set." ) ;
        return ;
    }


    string url(BINANCE_HOST);
    url += "/api/v1/userDataStream";

    vector <string> extra_http_header;
    string header_chunk("X-MBX-APIKEY: ");


    header_chunk.append( api_key );
    extra_http_header.push_back(header_chunk);

    string action = "DELETE";
    string post_data("listenKey=");
    post_data.append( listenKey );

    BinaCPP_logger::write_log( "<BinaCPP::close_userDataStream> url = |%s|, post_data = |%s|" , url.c_str() , post_data.c_str() ) ;

    string str_result;
    curl_api_with_header( url, str_result , extra_http_header , post_data , action ) ;

    if ( str_result.size() > 0 ) {

        BinaCPP_logger::write_log( "<BinaCPP::close_userDataStream> Done." ) ;

    } else {
        BinaCPP_logger::write_log( "<BinaCPP::close_userDataStream> Failed to get anything." ) ;
    }

    BinaCPP_logger::write_log( "<BinaCPP::close_userDataStream> Done.\n" ) ;

}

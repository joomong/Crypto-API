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

//TODO: Function Overriding
//void Binance::PostLimitSellOrders(const char *symbol,
//                                 const char *side,
//                                 const char *type,
//                                 double quantity,
//                                 double price,
//                                 long recvWindow,
//                                 Json::Value &json_result)
//{
//    PostOrders(symbol,
//               side,
//               type,
//               "",
//               0.0,
//               quantity,
//               price,
//               "",
//               0.0,
//               recvWindow,
//               json_result);
//}

//
//void Binance::PostLimitBuyOrders(const char *symbol,
//                         const char *side,
//                         const char *type,
//                         const char *timeInForce,
//                         double quantity,
//                         double price,
//                         long recvWindow,
//                         Json::Value &json_result)
//{
//    PostOrders(symbol,
//               side,
//               type,
//               timeInForce,
//               quantity,
//               price,
//               "",
//               0.0,
//               0.0,
//               recvWindow,
//               json_result);
//}

//
//void Binance::PostMarketSellOrders(const char *symbol,
//                                 const char *side,
//                                 const char *type,
//                                 const char *timeInForce,
//                                 double quantity,
//                                 double price,
//                                 const char *newClientOrderId,
//                                 double stopPrice,
//                                 double icebergQty,
//                                 long recvWindow,
//                                 Json::Value &json_result){}
//
//
//void Binance::PostMarketBuyOrders(const char *symbol,
//                                 const char *side,
//                                 const char *type,
//                                 const char *timeInForce,
//                                 double quantity,
//                                 double price,
//                                 const char *newClientOrderId,
//                                 double stopPrice,
//                                 double icebergQty,
//                                 long recvWindow,
//                                 Json::Value &json_result){}


void Binance::PostOrders(const char *symbol,
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
    {
        if (API_KEY.empty() || API_SECRET.empty())
        {
            std::cout << "<BinaCPP::send_order> API Key and Secret Key has not been set." << std::endl;
            return ;
        }

        std::string url(BINANCE_HOST);
        url += "/api/v3/order?";

        std::string action = "POST";

        std::string post_data = "symbol=" + std::string(symbol)
                                + "&side=" + std::string(side)
                                + "&type=" + std::string(type)
                                + "&quantity=" + std::to_string(quantity);

        if(strcmp(type, "MARKET"))//type != MARKET
        {
            post_data += "&timeInForce=" + std::string(timeInForce)
                         + "&price=" + std::to_string(price);
        }

        if (strlen(newClientOrderId) > 0)
        {
            post_data += "&newClientOrderId=" + std::string(newClientOrderId);
        }

        if (stopPrice > 0.0)
        {
            post_data += "&stopPrice=" + std::to_string(stopPrice);
        }

        if (icebergQty > 0.0)
        {
            post_data += "&icebergQty=" + std::to_string(icebergQty);
        }

        if (recvWindow > 0)
        {
            post_data += "&recvWindow=" + std::to_string(recvWindow);
        }

        post_data += "&timestamp=" + std::to_string(GetCurrentMsEpoch());

        std::string signature = hmac_sha256(API_SECRET.c_str(), post_data.c_str());
        post_data += "&signature=" + signature;

        std::vector<std::string> extra_http_header{ "X-MBX-APIKEY: " + API_KEY};

        std::string str_result;
        CurlApiWithHeader(url, str_result, extra_http_header, post_data, action);

        if (!str_result.empty()) {
            try {
                Json::Reader reader;
                json_result.clear();
                reader.parse(str_result, json_result);
//                BinaCPP_logger::write_log("<BinaCPP::send_order> Done.");
            } catch (std::exception &e) {
//                BinaCPP_logger::write_log("<BinaCPP::send_order> Error ! %s", e.what());
            }
        } else {
//            BinaCPP_logger::write_log("<BinaCPP::send_order> Failed to get anything.");
        }

//        BinaCPP_logger::write_log("<BinaCPP::send_order> Done.\n");
    }
}


void Binance::CancelOrder(const char *symbol,
                          const char *origClientOrderId,
                          const char *orderId,
                          const char *newClientOrderId,
                          long recvWindow,
                          Json::Value &json_result)
{
    if ( API_KEY.empty() || API_SECRET.empty() ) {
        std::cout <<  "<BinaCPP::send_order> API Key and Secret Key has not been set."
                  <<  std::endl;
        return ;
    }

    std::string url(BINANCE_HOST);
    url += "/api/v3/order?";

    string action = "DELETE";

    string post_data("symbol=");
    post_data.append( symbol );

    if ( orderId > 0 ) {
        post_data.append("&orderId=");
        post_data.append( to_string( orderId ) );
    }

    if ( strlen( origClientOrderId ) > 0 ) {
        post_data.append("&origClientOrderId=");
        post_data.append( origClientOrderId );
    }

    if ( strlen( newClientOrderId ) > 0 ) {
        post_data.append("&newClientOrderId=");
        post_data.append( newClientOrderId );
    }

    if ( recvWindow > 0 ) {
        post_data.append("&recvWindow=");
        post_data.append( to_string( recvWindow) );
    }


    post_data.append("&timestamp=");
    post_data.append( to_string( get_current_ms_epoch() ) );


    string signature =  hmac_sha256( secret_key.c_str(), post_data.c_str() );
    post_data.append( "&signature=");
    post_data.append( signature );


    vector <string> extra_http_header;
    string header_chunk("X-MBX-APIKEY: ");
    header_chunk.append( api_key );
    extra_http_header.push_back(header_chunk);

    BinaCPP_logger::write_log( "<BinaCPP::send_order> url = |%s|, post_data = |%s|" , url.c_str(), post_data.c_str() ) ;

    string str_result;
    curl_api_with_header( url, str_result , extra_http_header, post_data, action ) ;

    if ( str_result.size() > 0 ) {

        try {
            Json::Reader reader;
            json_result.clear();
            reader.parse( str_result , json_result );

        } catch ( exception &e ) {
            BinaCPP_logger::write_log( "<BinaCPP::send_order> Error ! %s", e.what() );
        }
        BinaCPP_logger::write_log( "<BinaCPP::send_order> Done." ) ;

    } else {
        BinaCPP_logger::write_log( "<BinaCPP::send_order> Failed to get anything." ) ;
    }

    BinaCPP_logger::write_log( "<BinaCPP::send_order> Done.\n" ) ;
}


// TODO:
void Binance::CancelAllOrders(const char *symbol,
                              long recvWindow,
                              Json::Value &json_result) {
    if (API_KEY.empty() || API_SECRET.empty())
    {
        std::cout << "<BinaCPP::send_order> API Key and Secret Key has not been set." << std::endl;
        return ;
    }

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

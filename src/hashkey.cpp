#include "hashkey.h"

std::string Hashkey::API_KEY = "";
std::string Hashkey::API_SECRET = "";


void Hashkey::init(std::string &api_key, std::string &api_secret){
    Exchange::init();
    API_KEY = api_key;
    API_SECRET = api_secret;
}

void Hashkey::GetServerTime(Json::Value &result_json){
    std::string url = HASHKEY_HOST;
    url += "/api/v1/time";
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result,result_json);
}

void Hashkey::GetExchangeInfo(std::string &symbol,Json::Value &result_json){
    std::string url = HASHKEY_HOST;
    url += "/api/v1/exchangeInfo?symbol=" + symbol;
    std::string result;
    CurlApi(url , result);
    Json::Reader reader;
    reader.parse(result , result_json);
}

void Hashkey::GetOrderBook(std::string &symbol, int limit, 
                            Json::Value &result_json){
    std::string url = HASHKEY_HOST;
    url += "/quote/v1/depth?symbol=" + symbol + 
            "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url , result);
    Json::Reader reader;
    reader.parse(result , result_json);
}

void Hashkey::GetRecentTrades(std::string &symbol , int limit,
                            Json::Value &result_json){
    std::string url = HASHKEY_HOST;
    url += "/quote/v1/trades?symbol=" + symbol +
           "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);
}

void Hashkey::GetKlines(std::string &symbol, std::string &interval, int limit,
                          Json::Value &result_json){
    std::string url = HASHKEY_HOST;
    url += "/quote/v1/klines?symbol=" + symbol 
        + "&interval=" + interval
        + "&limit=" + std::to_string(limit);
    std::string result;
    CurlApi(url, result);
    Json::Reader reader;
    reader.parse(result, result_json);                 
}




//Private
void Hashkey::PostLimitOrder(const std::string &symbol,
                            const std::string &side,
                            const double &quantity,
                            const double &price, 
                            Json::Value &json_result,
                            const std::string &time_in_force,
                            const std::string &client_order_id){
    std::string url(HASHKEY_HOST);
    url += "/api/v1/futures/order?";
    std::string action = "POST";
    std::string result;
    std::string querystring = "symbol=" + symbol + 
                            "&side=" + side +
                            "&timeInForce=" + time_in_force +
                            "&priceType=" +  "INPUT" +
                            "&type=" + "LIMIT" +
                            "&quantity=" + std::to_string(quantity) +
                            "&price=" + std::to_string(price) +
                            "&clientOrderId=" + client_order_id +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(querystring.c_str(),API_SECRET.c_str());
    querystring += "&signature=" + signature;
    url += querystring;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-HK-APIKEY: ");
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
            std::cout << "<send_order> Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "<send_order> Failed to get anything."
                  << std::endl;
    }
}

void Hashkey::PostMarketOrder(const std::string &symbol,
                            const std::string &side,
                            const double &quantity,
                            Json::Value &json_result,
                            const std::string &client_order_id){
    std::string url(HASHKEY_HOST);
    url += "/api/v1/futures/order?";
    std::string action = "POST";
    std::string result;
    std::string querystring = "symbol=" + symbol + 
                            "&side=" + side +
                            "&type=" + "LIMIT" +
                            "&timeInForce=" + "GTC" +
                            "&priceType=" + "MARKET" +
                            "&quantity=" + std::to_string(quantity) +
                            "&clientOrderId=" + client_order_id +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());

    std::string signature = hmac_sha256(querystring.c_str(),API_SECRET.c_str());
    querystring += "&signature=" + signature;
    url += querystring;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-HK-APIKEY: ");
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
            std::cout << "<send_order> Error !" << e.what() << std::endl;
        }
    } else {
        std::cout << "<send_order> Failed to get anything."
                  << std::endl;
    }
}

void Hashkey::CancelOrder(const std::string &symbol,
                     const std::string &order_id,
                     Json::Value &json_result,
                     const std::string &client_order_id){
    std::string url = HASHKEY_HOST;
    url += "/api/v1/futures/order?";

    std::string action = "DELETE";

    std::string post_data = "symbol=" + symbol + 
                            "&orderId=" + order_id +
                            "&orgClientOrderId=" + client_order_id +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());


    std::string signature =  hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector <std::string> extra_http_header;
    std::string header_chunk("X-HK-APIKEY: ");
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

void Hashkey::CancelAllOrders(const std::string &symbol,
                         const std::string &side,
                         Json::Value &json_result){

    std::string url = HASHKEY_HOST;
    url += "api/v1/futures/batchOrders?";

    std::string action = "DELETE";

    std::string post_data = "symbol=" + symbol + 
                            "side=" + side +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());


    std::string signature =  hmac_sha256(post_data.c_str(),API_SECRET.c_str());
    post_data += "&signature=" + signature;

    std::vector <std::string> extra_http_header;
    std::string header_chunk("X-HK-APIKEY: ");
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

void Hashkey::GetCurrentOpenOrders(const std::string &symbol,
                            Json::Value &json_result){
    std::string url(HASHKEY_HOST);
    url += "/api/v1/futures/openOrders?";

    std::string action = "GET";

    std::string querystring = "symbol=" + symbol +
                            "&type=" + "LIMIT" +
                            "&timestamp=" + std::to_string(GetCurrentMsEpoch());
    
    std::string signature =  hmac_sha256(querystring.c_str(),API_SECRET.c_str());
    querystring += "&signature=" + signature;

    url += querystring;

    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-HK-APIKEY: ");
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

void Hashkey::GetAccountInfo(Json::Value &json_result){
    std::string url(HASHKEY_HOST);
    url += "/api/v1/account?";
    std::string action = "GET";

    std::string post_data;
    std::string querystring = "timestamp=" + std::to_string(GetCurrentMsEpoch());
    
    std::string signature =  hmac_sha256(querystring.c_str(),API_SECRET.c_str());
    querystring += "&signature=" + signature;


    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-HK-APIKEY: ");
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


void Hashkey::GetUserStreamKey(Json::Value &json_result){
    std::string url(HASHKEY_HOST);


    std::string action = "POST";
    url += "/api/v1/userDataStream?";
    std::string post_data;
    std::string querystring = "timestamp=" + std::to_string(GetCurrentMsEpoch());
    
    std::string signature =  hmac_sha256(querystring.c_str(),API_SECRET.c_str());
    querystring += "&signature=" + signature;


    std::vector<std::string> extra_http_header;
    std::string header_chunk("X-HK-APIKEY: ");
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
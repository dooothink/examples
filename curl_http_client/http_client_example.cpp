#include <iostream>
#include "curl_easy_httpclient.hpp"

using namespace std;
using namespace EasyCurl;
int main()
{
    CHttpClient *pClient = new CHttpClient();
    std::string url = "http://httpbin.org/post";
    std::string content_type = "Content-Type: text/html";
    std::string content = "test for http post!";
    std::string response;
    int ret = pClient->post(url,content_type,content,response,true,2000,5000);
    cout << response << endl;
    return 0;
}
#ifndef __curl_easy_httpclient_h_
#define __curl_easy_httpclient_h_

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "curl/curl.h"

namespace EasyCurl
{
    using namespace std;
    class CHttpClient
    {
    public:
        int init()
        {
            return 0;
        }
        int uninit()
        {
            return 0;
        }
        int post(const std::string url,
            const std::string &content_type,
            const std::string &content,
            std::string &response,
            bool is_debug = false,
            int connect_timeout_miliseconds = 100,
            int timeout_miliseconds = 100
        ){
            CURLcode ret = CURLE_OK;
            CURL* curl = curl_easy_init();
            if (NULL == curl){
                return CURLE_FAILED_INIT;
            }
            if (is_debug){
                curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
                curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION,debug_callback);
            }
            struct curl_slist *headers = NULL;
            if (!content_type.empty()){
                headers = curl_slist_append(headers, content_type.c_str());
                if (headers != NULL) {
                    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                }
            }
#if 0
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Accept: application/json");
            headers = curl_slist_append(headers, "Content-Type: application/json");
            headers = curl_slist_append(headers, "charsets: utf-8");
            headers = curl_slist_append(headers, content_type.c_str());
            if (headers != NULL) {
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            }
#endif
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_POST, 1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, content.length());
            curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
            curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
            curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, connect_timeout_miliseconds);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout_miliseconds);
            ret = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (headers != nullptr) {
                curl_slist_free_all(headers);
            }
            return ret;
        }
        int get()
        {
            return 0;
        }
        int url_encode()
        {
            return 0;
        }
        int url_decode()
        {
            return 0;
        }
        static int debug_callback(CURL* handle,
            curl_infotype itype,
            char * pData,
            size_t size, void *);
        static size_t write_data_callback(void* buffer,
            size_t size,
            size_t nmemb,
            void* lpVoid);
        static std::map<int, std::string> info_map;
    protected:
    private:
    };
    int CHttpClient::debug_callback(CURL* handle,
        curl_infotype type,
        char * data,
        size_t size, void *)
    {
        ostringstream oss_debug;
        oss_debug << info_map[type] << ": " << data;
        cout << oss_debug.str();
        return 0;
    }

    size_t CHttpClient::write_data_callback(void* buffer,
        size_t size,
        size_t nmemb,
        void* pvoid)
    {
        std::string* str = dynamic_cast<std::string*>((std::string *)pvoid);
        if (NULL == str || NULL == buffer){
            return -1;
        }
        char* data = (char*)buffer;
        str->append(data, size * nmemb);
        return size * nmemb;
    }
    std::map<int, std::string> CHttpClient::info_map = 
    {
        { CURLINFO_TEXT,            "CURLINFO_TEXT" },
        { CURLINFO_HEADER_IN,       "CURLINFO_HEADER_IN" },
        { CURLINFO_HEADER_OUT,      "CURLINFO_HEADER_OUT" },
        { CURLINFO_DATA_IN,         "CURLINFO_DATA_IN" },
        { CURLINFO_DATA_OUT,        "CURLINFO_DATA_OUT" },
        { CURLINFO_SSL_DATA_IN,     "CURLINFO_SSL_DATA_IN" },
        { CURLINFO_SSL_DATA_OUT,    "CURLINFO_SSL_DATA_OUT" },
        { CURLINFO_END,             "CURLINFO_END" }
    };
}

#endif // __curl_easy_httpclient_h_

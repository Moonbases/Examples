#include <iostream>
#include <curl/curl.h>
#include <sstream>
#include <string>

struct LicenseRequest {
    std::string product;
    std::string license;
    std::string hwid;
};

int main() {
    std::string url = "http://localhost/api/license/authenticate";
    LicenseRequest body = {"product_name", "license_key", "hardware_id"};
    std::string apiKey = "public_api_key";
    std::ostringstream stream;

    stream << "{\"product\": \"" << body.product << "\", \"license\": \"" << body.license << "\", \"hwid\": \"" << body.hwid << "\"}";
    std::string jsonBody = stream.str();

    curl_global_init(CURL_GLOBAL_ALL);
    struct curl_slist* headers = NULL;

    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("Authorization: " + apiKey).c_str());
    CURL* curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonBody.size());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            std::cout << "Response code: " << response_code << std::endl;
            curl_easy_cleanup(curl);
        }

        curl_slist_free_all(headers);
    }
    curl_global_cleanup();
    return 0;
}
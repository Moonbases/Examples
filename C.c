#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"

struct LicenseRequest {
    char product[100];
    char license[100];
    char hwid[100];
};

int main() {
    CURL* curl;
    CURLcode res;
    
    struct LicenseRequest body = {"product_name", "license_key", "hardware_id"};
    char apiKey[] = "public_api_key";
    char url[] = "http://localhost/api/license/authenticate";
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    char authHeader[100];
    sprintf(authHeader, "Authorization: %s", apiKey);

    headers = curl_slist_append(headers, authHeader);
    curl = curl_easy_init();

    if (curl) {
        cJSON* jsonBody = cJSON_CreateObject();
        cJSON_AddStringToObject(jsonBody, "product", body.product);
        cJSON_AddStringToObject(jsonBody, "license", body.license);
        cJSON_AddStringToObject(jsonBody, "hwid", body.hwid);

        char* jsonString = cJSON_Print(jsonBody);
        cJSON_Delete(jsonBody);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            printf("Response code: %ld\n", response_code);
        }

        curl_easy_cleanup(curl);
        free(jsonString);
    }
    curl_global_cleanup();
    return 0;
}
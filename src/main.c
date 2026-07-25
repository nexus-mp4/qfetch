#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
struct memst {
    char *memory;
    size_t size;
};
static size_t tuffwrite(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct memst *mem = (struct memst *)userp;
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    struct memst bro;
    bro.memory = malloc(1);
    bro.size = 0;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.quotable.io/random");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, tuffwrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&bro);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // -k
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // this shit is so fucking ass
            cJSON *root = cJSON_Parse(bro.memory);
            if(root == NULL) {
                fprintf(stderr, "JSON parse error\n");
            } else {
                cJSON *content = cJSON_GetObjectItemCaseSensitive(root, "content");
                cJSON *author  = cJSON_GetObjectItemCaseSensitive(root, "author");
                if(cJSON_IsString(content) && content->valuestring != NULL &&
                   cJSON_IsString(author)  && author->valuestring != NULL) {
                    printf("\"%s\"\n - \"%s\"\n", content->valuestring, author->valuestring);
                }
                cJSON_Delete(root);
            }
        }
        curl_easy_cleanup(curl);
    }
    free(bro.memory);
    return 0;
}

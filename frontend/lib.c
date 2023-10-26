#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#define URL "http://localhost:8080"

int downloadFile(const char *url, const char *output_filename) {
    CURL *curl;
    CURLcode res;

    FILE *output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        fprintf(stderr, "Failed to open output file for writing\n");
        return 1;
    }

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
        fclose(output_file);
    }

    return 0;
}

int pkg_install(char* package) {
  char* url = (char*)malloc(sizeof(package)+sizeof(URL)+6);
  char* output = (char*)malloc(sizeof(package)+4);
  sprintf(url, "%s/%s.dpm", URL, package);
  sprintf(output, "%s.dpm", package);
  
  if (downloadFile(url, output) == 1) {
    return 1;
  };
  
}




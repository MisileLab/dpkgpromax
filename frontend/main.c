#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define URL "http://localhost:8080"

int main() {
  printf("dpkg pro max v0.1++");
}

int downloadFile(const char* url, const char* output_filename) {
  CURL* curl;
  CURLcode res;

  FILE* output_file = fopen(output_filename, "wb");
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
      fclose(output_file);  // close file
      remove(output_filename);  // remove downloaded file
      return 1;
    }

    curl_easy_cleanup(curl);
    fclose(output_file);
  }

  return 0;
}

int install(char* package) {
  char* url = (char*)malloc(strlen(package) + strlen(URL) + 7);
  char* output = (char*)malloc(strlen(package) + 5);
  sprintf(url, "%s/%s.dpm", URL, package);
  sprintf(output, "%s.dpm", package);

  if (downloadFile(url, output) == 1) {
    fprintf(stderr, "Failed to download package: %s\n", package);
    free(url);
    free(output);
    return 1;
  }

  free(url);
  free(output);
  return 0;
}


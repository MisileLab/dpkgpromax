#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#define URL "https://dpkg.ny64.kr"

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
    }

    curl_easy_cleanup(curl);
    fclose(output_file);
  }

  return 0;
}

int pkg_install(char* package) {
  char* url = (char*)malloc(sizeof(package) + sizeof(URL) + 6);
  char* output = (char*)malloc(sizeof(package) + 4);
  sprintf(url, "%s/%s.dpm", URL, package);
  sprintf(output, "%s.dpm", package);

  if (downloadFile(url, output) == 1) {
    return 1;
  };
  free(url);
  free(output);
  return 0;
}

int pkg_search(char *package) {
  char* url = (char*)malloc(sizeof(URL)+7);
  char* output = (char*)malloc(5);
  sprintf(url, "%s/files", URL);
  sprintf(url, "files");

  if (downloadFile(url, output) == 1) {
    return 1;
  }
  free(url);
  free(output);

  FILE* file = fopen("files", "r");
  if (file == NULL) {
    return 2;
  }

  while(!feof(file)) {
    char* line = (char*)malloc(100);
    fgets(line, 100, file);
    if (strstr(line, package) != NULL) {
      printf("%s", line);
    }
    free(line);
  }
  return 0;
}

int pkg_remove(char *package) {
  char* packagedpm = (char*)malloc(sizeof(package) + 4);

  if (fopen("packagedpm", "w") == NULL) {
    return -1;
  }
  // bin remove thing
  free(packagedpm);
  return 0;
}

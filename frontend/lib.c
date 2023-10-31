#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include <curl/curl.h>
#include "microtar/src/microtar.h"

#define URL "https://dpkg.ny64.kr"
#define MAX 100

int decompressTar(const char *tarFile, const char *outputDir) {
    mtar_t mtar;
    mtar_header_t header;

    // Open the tar archive for reading
    if (mtar_open(&mtar, tarFile, "r") != MTAR_ESUCCESS) {
        fprintf(stderr, "Failed to open the tar archive: %s\n", tarFile);
        return 1;
    }

    // Iterate through the tar archive and extract files
    while (mtar_read_header(&mtar, &header) == MTAR_ESUCCESS) {
        // Construct the output file path
        char outputFilePath[PATH_MAX];
        snprintf(outputFilePath, PATH_MAX, "%s/%s", outputDir, header.name);

        // Create the directory structure if it doesn't exist
        char* last_slash = strrchr(outputFilePath, '/');
        if (last_slash) {
            *last_slash = '\0';
            mkdir(outputFilePath, 0755);
            *last_slash = '/';
        }

        // Open the output file for writing
        FILE* outFile = fopen(outputFilePath, "wb");
        if (!outFile) {
            fprintf(stderr, "Failed to open output file: %s\n", outputFilePath);
            mtar_close(&mtar);
            return 1;
        }

        // Extract the file
        if (mtar_read_data(&mtar, outFile, header.size) != MTAR_ESUCCESS) {
            fprintf(stderr, "Failed to extract file: %s\n", header.name);
            fclose(outFile);
            mtar_close(&mtar);
            return 1;
        }

        // Close the output file
        fclose(outFile);
    }

    // Close the tar archive
    mtar_close(&mtar);

    return 0;
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

  FILE* f = fopen(output, "r");
  if (f == NULL) {
    return 2;
  }

  if (decompressTar(output, package) != 0) {
    return 3;
  }

  char* pkgdepend = (char*)malloc(sizeof(package) + 20);
  sprintf(pkgdepend, "%s/DEPENDS", package);

  FILE* dependf = fopen(pkgdepend, "r");
  char** dependencies;

  while(!feof(dependf)) {
    char* line = (char*)malloc(MAX);
    fgets(line, MAX, dependf);
    if (realloc(dependencies, sizeof(dependencies) + sizeof(line)) == NULL) {
      return 1;
    }
    dependencies[sizeof(dependencies)/MAX] = line;
  }

  for(int i=0;i<sizeof(dependencies)/MAX;i++) {
    pkg_install(dependencies[i]);
  }

  

  return 0;
}

char pkg_search(char *package) {
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
    char* line = (char*)malloc(MAX);
    fgets(line, MAX, file);
    if (strstr(line, package) != NULL) {
      return 0;
    }
    free(line);
  }
  return -1;
}

int pkg_remove(char *package) {
  char* packagedpm = (char*)malloc(sizeof(package) + 4);

  if (fopen("packagedpm", "w") == NULL) {
    return -1;
  }
  free(packagedpm);
  return 0;
}

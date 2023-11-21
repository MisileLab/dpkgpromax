#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <curl/curl.h>

#ifdef _WIN32
#include <Windows.h>
#define REMOVE_COMMAND "del"
#define PATH_SEPARATOR "\\"
#else
#include <unistd.h>
#define REMOVE_COMMAND "rm"
#define PATH_SEPARATOR "/"
#endif

#ifdef _WIN32
#include <Windows.h>
#define MOVE_COMMAND "move"
#else
#include <unistd.h>
#include <string.h>
#define MOVE_COMMAND "mv"
#endif

#define URL "https://dpkgpromax.misilelaboratory.xyz"
#define MAX 100

#ifdef _WIN32
#include <Windows.h>
#define PATH_SEPARATOR "\\"
#else
#include <unistd.h>
#endif

int fileExists(const char *filename) {
#ifdef _WIN32
    DWORD attrib = GetFileAttributes(filename);
    return (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY));
#else
    return access(filename, F_OK) != -1;
#endif
}

void removeBinaryIfExists(const char* binaryName, const char* installPath) {
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s%s%s", installPath, PATH_SEPARATOR, binaryName);
    printf("%s\nz", fullPath);

    if (fileExists(fullPath)) {
#ifdef _WIN32
        // Use Windows API to remove file
        if (DeleteFile(fullPath) == 0) {
            perror("Removal failed");
            exit(EXIT_FAILURE);
        }
#else
        // Use UNIX command to remove file
        char removeCommand[256];
        snprintf(removeCommand, sizeof(removeCommand), "rm %s", fullPath);

        int removeStatus = system(removeCommand);

        if (removeStatus == -1) {
            perror("Removal failed");
            exit(EXIT_FAILURE);
        }
#endif
        printf("Binary '%s' removed successfully!\n", binaryName);
    } else {
        printf("Binary '%s' not found.\n", binaryName);
    }
}

void installBinary(const char* binaryPath) {
    char moveCommand[100];
    
#ifdef _WIN32
    system("mkdir \"C:\\Program Files\\YourApp\\\"");
    snprintf(moveCommand, sizeof(moveCommand), "%s \"%s\" \"C:\\Program Files\\YourApp\\\"", MOVE_COMMAND, binaryPath);
#else
    snprintf(moveCommand, sizeof(moveCommand), "%s \"%s\" /usr/local/bin/", MOVE_COMMAND, binaryPath);
    char* command = (char*)malloc(sizeof(binaryPath) + 50);
    sprintf(command, "chmod a+x %s", binaryPath);
    system(command);
#endif

    int moveStatus = system(moveCommand);

    if (moveStatus == -1) {
        perror("Move failed");
        exit(EXIT_FAILURE);
    }

    printf("Binary installed successfully!\n");
}

int downloadFile(const char *url, const char *output_filename) {
  CURL *curl;
  CURLcode res;

  FILE *output_file = fopen(output_filename, "wb+");
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
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
    fclose(output_file);
  }

  return 0;
}

void create_folder(const char* folder_name) {
    struct stat st;

    if (stat(folder_name, &st) == -1) {
        // The folder doesn't exist, create it
        if (mkdir(folder_name, 0777) == 0) {
            printf("Folder '%s' created successfully.\n", folder_name);
        } else {
            perror("Error creating folder");
        }
    } else {
        printf("Folder '%s' already exists.\n", folder_name);
    }
}

int pkg_search(char *package) {
  char *url = (char *)malloc(sizeof(URL) + 7);
  sprintf(url, "%s/files", URL);

  if (downloadFile(url, "files") == 1) {
    fprintf(stderr, "Failed to download file %s\n", url);
    return 1;
  }
  free(url);

  FILE *file = fopen("files", "r");
  if (file == NULL) {
    fprintf(stderr, "Failed to open file %s\n", "files");
    return 2;
  }

  while (!feof(file)) {
    char *line = (char *)malloc(MAX);
    fgets(line, MAX, file);
    line[strcspn(line, "\n\r")] = 0;
    if (strcmp(line, package) == 0) {
      printf("found\n");
      return 0;
    }
    free(line);
  }
  fprintf(stderr, "Package not found\n");
  return -1;
}

int pkg_install(char *package) {
  if (pkg_search(package) == -1) { printf("Package not found"); return -1; }
  char *url = (char *)malloc(sizeof(package) + sizeof(URL) + 6);
  char *output = (char *)malloc(sizeof(package) + 4);
  sprintf(url, "%s/%s", URL, package);
  sprintf(output, "%s", package);

  if (downloadFile(url, output) == 1) {
    fprintf(stderr, "Failed to download file %s\n", url);
    return 1;
  };
  installBinary(output);

  return 0;
}

int pkg_remove(char *package) {
  char *packagedpm = (char *)malloc(sizeof(package) + 4);
  packagedpm = strcpy(packagedpm, package);

  #ifdef _WIN32
  removeBinaryIfExists(packagedpm, "C:\\Program Files\\YourApp\\");
  #else
  removeBinaryIfExists(packagedpm, "/usr/local/bin");
  #endif

  free(packagedpm);
  return 0;
}

int pkg_upgrade(char *package) {
  pkg_remove(package);
  pkg_install(package);
  return 0;
} 


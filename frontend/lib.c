#include <dirent.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include "microtar/src/microtar.h"
#include <curl/curl.h>

#define URL "https://dpkgpromax.misilelaboratory.xyz"
#define MAX 100

int fileExists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

int removeIfSameName(const char *srcDir, const char *destDir) {
    int flag = 0;

    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(srcDir)) == NULL) {
        perror("Error opening source directory");
        return 1; // Error
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char srcPath[PATH_MAX];
            snprintf(srcPath, PATH_MAX, "%s/%s", srcDir, entry->d_name);

            char destPath[PATH_MAX];
            snprintf(destPath, PATH_MAX, "%s/%s", destDir, entry->d_name);

            if (fileExists(destPath)) {
                printf("File %s exists in %s. Do you want to remove it? (y/n): ", entry->d_name, destDir);
                char confirmation;
                scanf(" %c", &confirmation);

                if (confirmation == 'y' || confirmation == 'Y') {
                    if (remove(destPath) == 0) {
                        printf("Removed file %s in %s.\n", entry->d_name, destDir);
                    } else {
                        perror("Error removing the file");
                        flag = 1;
                    }
                } else {
                    printf("No action taken for file %s in %s.\n", entry->d_name, destDir);
                }
            } else {
                printf("The file %s doesn't exist in %s. No action taken.\n", entry->d_name, destDir);
            }
        }
    }

    closedir(dir);
    return flag; // 0 on success, 1 if there were errors
}

int decompressTar(const char *tarFile, const char *outputDir) {
  mtar_t mtar;
  mtar_header_t header;

  // Open the tar archive for reading
  if (mtar_open(&mtar, tarFile, "r") != MTAR_ESUCCESS) {
    fprintf(stderr, "Failed to open the tar archive: %s\n", tarFile);
    return 1;
  }

  // Iterate through the tar archive and extract files
  while (mtar_read_header(&mtar, &header) != MTAR_ENULLRECORD) {
    // Construct the output file path
    char outputFilePath[PATH_MAX];
    snprintf(outputFilePath, PATH_MAX, "%s/%s", outputDir, header.name);
    printf("%s\n", header.name);
  //printf(outputFilePath);

    // Create the directory structure if it doesn't exist
    char *last_slash = strrchr(outputFilePath, '/');
    if (last_slash) {
      *last_slash = '\0';
      mkdir(outputFilePath, 0755);
      *last_slash = '/';
    }

    // Open the output file for writing
    DIR* dir = opendir(outputFilePath);
    if (dir) {fprintf(stderr, "it's folder: %s\n", outputFilePath);continue;} else if (ENONET == errno) {printf("create a file cause not found");mkdir(outputFilePath, 0777);continue;}
    
    FILE *outFile = fopen(outputFilePath, "wb+");
    if (!outFile) {
      fprintf(stderr, "Failed to open output file: %s\n", outputFilePath);
      fprintf(stderr, "Trying to use alternative way\n");
      FILE *outFile = fopen(outputFilePath, "wb");
      if (!outFile) {
        fprintf(stderr, "Failed to open output file: %s\n", outputFilePath);
        mtar_close(&mtar);
      }
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

void moveFilesToSystemDirs() {
  int status;

  // Move the contents of the 'lib' directory to '/usr/lib'
  status = system("cp lib/* /usr/lib/");
  if (status == -1) {
    perror("Error moving files to /usr/lib");
  }

  // Move the contents of the 'bin' directory to '/usr/bin'
  status = system("cp bin/* /usr/bin/");
  if (status == -1) {
    perror("Error moving files to /usr/bin");
  }
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

int pkg_install(char *package) {
  char *url = (char *)malloc(sizeof(package) + sizeof(URL) + 6);
  char *output = (char *)malloc(sizeof(package) + 4);
  sprintf(url, "%s/%s.dpm", URL, package);
  sprintf(output, "%s.dpm", package);

  if (downloadFile(url, output) == 1) {
    fprintf(stderr, "Failed to download file %s\n", url);
    return 1;
  };
  free(url);

  FILE *f = fopen(output, "r");
  if (f == NULL) {
    fprintf(stderr, "Failed to open file %s\n", output);
    return 2;
  }

  char *outputa = (char *)malloc(sizeof(package) + 4);
  sprintf(outputa, "%s", package);

  create_folder(outputa);
  char *output2 = (char *)malloc(sizeof(package) + 9);
  char *output3 = (char *)malloc(sizeof(package) + 9);
  sprintf(output2, "%s/lib", outputa);
  sprintf(output3, "%s/bin", outputa);
  create_folder(output2);
  create_folder(output3);

  if (decompressTar(output, outputa) != 0) {
    fprintf(stderr, "Failed to decompress file %s\n", output);
    return 3;
  }

  char *pkgdepend = (char *)malloc(sizeof(package) + 20);
  sprintf(pkgdepend, "%s/DEPENDS", package);

  FILE *dependf = fopen(pkgdepend, "r");
  char **dependencies;

  while (!feof(dependf)) {
    char *line = (char *)malloc(MAX);
    fgets(line, MAX, dependf);
    if (realloc(dependencies, sizeof(dependencies) + sizeof(line)) == NULL) {
      fprintf(stderr, "Failed to allocate memory\n");
      return 1;
    }
    dependencies[sizeof(dependencies) / MAX] = line;
  }

  for (int i = 0; i < sizeof(dependencies) / MAX; i++) {
    pkg_install(dependencies[i]);
  }

  moveFilesToSystemDirs();

  return 0;
}

char pkg_search(char *package) {
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
    if (strstr(line, package) != NULL) {
      printf("found");
      return 0;
    }
    free(line);
  }
  fprintf(stderr, "Package not found\n");
  return -1;
}

int pkg_remove(char *package) {
  char *packagedpm = (char *)malloc(sizeof(package) + 4);
  packagedpm = strcat(package, ".dpm");

  if (fopen(packagedpm, "w") == NULL) {
    fprintf(stderr, "Failed to open file %s\n", packagedpm);
    return -1;
  }

  removeIfSameName("lib", "/usr/lib");
  removeIfSameName("bin", "/usr/bin");

  free(packagedpm);
  return 0;
}

int pkg_upgrade(char *package) {
  pkg_install(package);
  pkg_upgrade(package);
  return 0;
} 


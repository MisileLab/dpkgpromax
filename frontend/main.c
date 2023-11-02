#include "lib.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
  printf("dpkgpromax++\n");
  if (argc <= 2) {
    printf("not enough arguments\n");
    return 1;
  }
  if (strcmp(argv[1], "install") == 0) {
    pkg_install(argv[2]);
  } else if (strcmp(argv[1], "remove") == 0) {
    pkg_remove(argv[2]);
  } else if (strcmp(argv[1], "upgrade") == 0) {
    pkg_upgrade(argv[2]);
  } else {
    pkg_search(argv[2]);
  }
}


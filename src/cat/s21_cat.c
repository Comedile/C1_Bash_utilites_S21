#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cat.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    char g[1000];  //сделать динамическое расширение строки
    while (1) {
      for (int i = 0; i < 255; i++) {
        scanf("%c", &g[i]);
        printf("%c", g[i]);
      }
    }
  }
  Flag r = {0};
  FILE *f = NULL;
  if (parser(argc, argv, &r) == 0) {
    fprintf(stderr, "invalid key\n");
  }
  open_file(argc, argv, f, &r);
  return 0;
}
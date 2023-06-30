#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grep.h"

int main(int argc, char *argv[]) {
  Flag r = {0};
  FILE *f = NULL;
  int count = 0;  //счетчик шаблонов
  int q = 0;      //счетчик аргументов-файлов
  int fix = 1;
  if (argc < 3) {
    printf("ERROR\n");
  } else {
    if (!parser(f, argc, argv, &r, &q, &count, &fix)) {
      fprintf(stderr, "invalid key\n");
    } else if (fix != 0) {
      open_file(f, &r, q, count);
    }
  }
  return 0;
}
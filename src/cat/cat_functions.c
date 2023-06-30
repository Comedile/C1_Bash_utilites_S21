#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cat.h"

int parser(int argc, char *argv[], Flag *r) {
  int fl = 1;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '-') {  //проверяем на то флаг ли это
      for (int j = 1, n = strlen(argv[i]); j < n;
           j++) {  //проверяем используемые флаги
        if (argv[i][j] == 'b') {
          r->b = 1;
        } else if (argv[i][j] == 'e') {
          r->e = 1;
        } else if (argv[i][j] == 'n') {
          r->n = 1;
        } else if (argv[i][j] == 's') {
          r->s = 1;
        } else if (argv[i][j] == 't') {
          r->t = 1;
        } else if (argv[i][j] == 'v') {
          r->v = 1;
        } else if (argv[i][j] == 'E') {
          r->eB = 1;
        } else if (argv[i][j] == 'T') {
          r->tB = 1;
        } else
          fl = 0;  // ERROR
      }
    } else if (argv[i][0] == '-' && argv[i][1] == '-') {
      if (strcmp(argv[i], "--number-nonblank") == 0) {
        r->b = 1;
      } else if (strcmp(argv[i], "--number") == 0) {
        r->n = 1;
      } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
        r->s = 1;
      } else
        fl = 0;  // ERROR
    }
  }
  return fl;
}

//Нумерация непустых строк
void flag_b_number(char bs, int *j, char a) {
  if ((a != '\n') && (bs == '\n')) {
    printf("%6d\t", *j);
    *j = *j + 1;
  }
}

//Нумерация всех строк ERROR
void flag_n_number(char bs, int *j) {
  if (bs == '\0') {
    *j = *j - 1;
  } else if (bs == '\n') {
    printf("%6d\t", *j);
    *j = *j + 1;
  }
}

//Замена символа конца строки на $
void flag_e_E(char a) {
  if (a == '\n') {
    printf("$");
  }
}

//Замена табов на ^I
void flag_t_T(char a, int *p) {
  if (a == '\t') {
    *p = *p + 1;
    printf("^I");
  } else
    *p = 0;
}

//Вывод скрытых символов
void flag_v(char a, int *u) {
  if (a >= 0 && a < 9) {
    *u = *u + 1;
    printf("^%c", a + 64);

  } else if (a >= 11 && a < 32) {
    printf("^%c", a + 64);
    *u = *u + 1;
  } else if (a == 127) {
    printf("^%c", a - 64);
    *u = *u + 1;
  } else if (a < -96) {
    printf("M-^%c", a + 192);
    *u = *u + 1;
  } else if (a >= -96 && a < -1) {
    printf("M-%c", a + 128);
    *u = *u + 1;
  } else if (a == -1) {
    printf("M-^?");
    *u = *u + 1;
  } else
    *u = 0;
}

void flag_s(char a, char bs, char cs, int *count) {
  if (((a == '\n') && (cs == '\n') && (bs == '\0')) ||
      ((a == '\n') && (bs == '\n'))) {
    *count = *count + 1;
  } else {
    *count = 0;
  }
}

//Функция проверки файла и применения опций
void file_check(FILE *f, Flag *r, int *j, char *a, char *bs, char *cs,
                int *count, char *argv[], int k) {
  int u = 0;  //индикатор для флага v
  int p = 0;  //индикатор для флага t
  int y = 0;  //индикатор для включения флага v
  if (f != NULL) {
    while ((*a = fgetc(f)) != EOF) {
      if (r->s == 1) {
        flag_s(*a, *bs, *cs, count);
      }
      if (*count < 2) {
        if (((r->b == 1) && (r->n == 1)) || ((r->b == 1) && (r->n == 0))) {
          flag_b_number(*bs, j, *a);
        }
        if ((r->b == 0) && (r->n == 1)) {
          flag_n_number(*bs, j);
        }
        if (((r->e == 1) && (r->eB == 1)) || ((r->e == 1) && (r->eB == 0))) {
          flag_e_E(*a);
          y = 1;
        }
        if ((r->eB == 1) && (r->e == 0)) {
          flag_e_E(*a);
        }
        if (((r->t == 1) && (r->tB == 0)) || ((r->t == 1) && (r->tB == 1))) {
          flag_t_T(*a, &p);
          y = 1;
        }
        if ((r->t == 0) && (r->tB == 1)) {
          flag_t_T(*a, &p);
        }
        if (r->v == 1 || y == 1) {
          flag_v(*a, &u);
        }
        if (u < 1 && p < 1) {
          printf("%c", *a);
        }
      }
      *cs = *bs;
      *bs = *a;
    }
    fclose(f);
  } else
    fprintf(stderr, "%s: file or directory doesn`t exist\n", argv[k]);
}

//Функция открывания файлов
void open_file(int argc, char *argv[], FILE *f, Flag *r) {
  int j = 1;  //считает строки, считанные из файла
  char a;
  char bs = '\n';
  char cs = '\0';
  int count = 0;  //счетчик пустых строк для флага S
  for (int k = 1; k < argc; k++) {
    if (argv[k][0] != '-') {  // check is it file
      f = fopen(argv[k], "r");
      file_check(f, r, &j, &a, &bs, &cs, &count, argv, k);
    }
  }
}
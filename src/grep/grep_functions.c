#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grep.h"

void flag_e_parcing(Flag *r, int *i, int j, char *argv[], int *count) {
  r->e = 1;
  if (argv[*i][j + 1] != '\0') {
    int ch = 0;
    for (int y = j + 1, x = strlen(argv[*i]); y < x; y++) {
      r->pattern[*count][ch] = argv[*i][y];
      ch++;
    }
    *count = *count + 1;
  } else if (argv[*i][j + 1] == '\0') {
    strcpy(r->pattern[*count], argv[*i + 1]);
    *count = *count + 1;
    *i = *i + 1;
  }
}

void flag_f_parcing(FILE *f, Flag *r, int *i, int j, char *argv[], int *count,
                    int *fix) {
  r->f = 1;
  if (argv[*i][j + 1] != '\0') {
    int ch = 0;
    for (int y = j + 1, x = strlen(argv[*i]); y < x; y++) {
      r->buf[ch] = argv[*i][y];
      ch++;
    }
  } else if (argv[*i][j + 1] == '\0') {
    strcpy(r->buf, argv[*i + 1]);
    *i = *i + 1;
  }
  f = fopen(r->buf, "r");
  if (f != NULL) {
    char str[1000];
    while (fgets(str, 1000, f)) {
      strcpy(r->pattern[*count], str);
      *count = *count + 1;
    }
    *fix = 1;
    fclose(f);
  } else {
    fprintf(stderr, "%s: file or directory doesn`t exist\n", r->buf);
    *fix = 0;
  }
}

void change_counters(Flag *r, int fla, int *count, int *q, int temp,
                     char *argv[]) {
  if (fla == 1 && r->e == 0 && r->f == 0) {
    strcpy(r->pattern[*count], argv[temp]);
    *count = *count + 1;
    ;
  } else if (fla == 1 && *count > 0) {
    strcpy(r->argf[*q], argv[temp]);
    *q = *q + 1;
  }
  if ((r->c == 1 && r->o == 1) || (r->l == 1 && r->o == 1)) {
    r->o = 0;
  }
}

int parser(FILE *f, int argc, char *argv[], Flag *r, int *q, int *count,
           int *fix) {
  int i = 1;  //счетчик цикла, по аргументам
  int fla = 0;
  int temp = 1;
  int ind = 1;
  for (; i < argc; i++) {
    if (argv[i][0] == '-') {
      for (int j = 1, n = strlen(argv[i]); j < n; j++) {
        if (argv[i][j] == 'e') {
          flag_e_parcing(r, &i, j, argv, count);
          break;
        } else if (argv[i][j] == 'f') {
          flag_f_parcing(f, r, &i, j, argv, count, fix);
          break;
        } else if (argv[i][j] == 'i') {
          r->i = 1;
        } else if (argv[i][j] == 'v') {
          r->v = 1;  //работает только, если флаг с шаблоном не слитно и перед
                     //именем первого файла
        } else if (argv[i][j] == 'c') {
          r->c = 1;  //работает только, если флаг с шаблоном не слитно и перед
                     //именем первого файла
        } else if (argv[i][j] == 'l') {
          r->l = 1;
        } else if (argv[i][j] == 'n') {
          r->n = 1;
        } else if (argv[i][j] == 'h') {
          r->h = 1;
        } else if (argv[i][j] == 's') {
          r->s = 1;
        } else if (argv[i][j] == 'o') {
          r->o = 1;
        } else {
          ind = 0;
        }
      }
    } else if (r->e == 0 && fla == 0 && r->f == 0) {
      temp = i;
      fla = 1;
    } else {
      strcpy(r->argf[*q], argv[i]);  //записываем файлы поочереди в структуру
      *q = *q + 1;
    }
  }
  change_counters(r, fla, count, q, temp, argv);
  return ind;
}

void flag_o(char *a, int count, int q, int k, Flag *r, int cs, int *ch) {
  int j = 0;
  int reg_c;
  int status;
  regex_t reg;
  regmatch_t test[1000];
  int cflags = REG_EXTENDED;
  if (r->i == 1) {
    cflags = cflags | REG_ICASE;
  }
  while (j < count) {
    reg_c = regcomp(&reg, r->pattern[j], cflags);
    if (reg_c == 0) {
      status = regexec(&reg, a, 1, test, 0);
      if (status == 0) {
        *ch = *ch + 1;
        if (q > 1 && r->h == 0) {
          printf("%s:", r->argf[k]);
        }
        if (r->n == 1) {
          printf("%d:", cs);
        }
        for (int i = test[0].rm_so; i < test[0].rm_eo; i++) {
          printf("%c", a[i]);
        }
        printf("\n");
        a = &(a[test[0].rm_eo]);
      } else if (status == REG_NOMATCH) {
        j++;
        continue;
      }
      regfree(&reg);  //освобождаем память от функции
    }
  }
}

void print(Flag *r, int cc, int ch, int k, int q) {
  if (r->c == 1 && r->l == 0 && r->h == 0 && q > 1) {
    printf("%s:", r->argf[k]);
  }
  if (r->l == 1 && ch != 0 && r->v == 0) {
    printf("%s\n", r->argf[k]);
  }
  if (r->l == 1 && cc != 0 && r->v == 1) {
    printf("%s\n", r->argf[k]);
  }
  if (r->c == 1 && r->v == 0 && r->l == 0) {
    printf("%d\n", ch);
  } else if (r->c == 1 && r->v == 1 && r->l == 0) {
    printf("%d\n", cc);
  }
}

void check_pattern(int count, Flag *r, int *ask, char *a) {
  int reg_c;
  int status;
  regex_t reg;
  int cflags = REG_EXTENDED;
  if (r->i == 1) {
    cflags = cflags | REG_ICASE;
  }
  for (int j = 0; j < count; j++) {
    reg_c = regcomp(&reg, r->pattern[j],
                    cflags);  //компилируем регулярное выражение
    if (reg_c == 0) {
      status = regexec(&reg, a, 0, NULL,
                       0);  //если найдено совпадение с шаблоном
      if (status == 0) {
        *ask = *ask + 1;
      }
      regfree(&reg);  //освобождаем память от функции
    }
  }
}

void printing_results(Flag *r, int ask, int q, int k, char *a, int cs) {
  if (r->c == 0 && r->l == 0) {
    if (ask > 0 && r->v == 0) {
      if (q > 1 &&
          r->h == 0) {  //чтобы печатались имена файлов, если их несколько
        printf("%s:", r->argf[k]);
      }
      if (r->n == 1) {
        printf("%d:", cs);
      }
      printf("%s", a);
      if (a[strlen(a) - 1] != '\n') {
        printf("\n");
      }
    }
    if (ask == 0 && r->v == 1) {
      if (q > 1 &&
          r->h == 0) {  //чтобы печатались имена файлов, если их несколько
        printf("%s:", r->argf[k]);
      }
      if (r->n == 1) {
        printf("%d:", cs);
      }
      printf("%s", a);
      if (a[strlen(a) - 1] != '\n') {
        printf("\n");
      }
    }
  }
}

void schetchik(Flag *r, int ask, int *cc, int *ch) {
  if (ask == 0 && r->v == 1) {
    *cc = *cc + 1;
  } else if (ask > 0) {
    *ch = *ch + 1;
  }
}

void open_file(FILE *f, Flag *r, int q, int count) {
  char a[1000];  //симыол для считываниея из файла
  int ch = 0;    //счетчик совпадающих строк
  int cc = 0;    //счетчик несовпадающих строк
  int cs = 0;  //общий счетчик строк, считанных из файла
  int er = 0;  //флаг, сообщающий об ошибке открытия файла
  int erf = 0;  //счетчик ошибочных файлов
  int ask = 0;  //индикатор предотвращения повторного вывода строки при
  for (int k = 0; k < q; k++) {
    f = fopen(r->argf[k], "r");
    if (f != NULL) {
      while (fgets(a, 1000, f)) {
        ask = 0;
        cs++;
        if (r->o == 1 && r->l == 0 && r->c == 0 && r->v == 0) {
          flag_o(a, count, q, k, r, cs, &ch);
        }
        if (r->o == 0) {
          check_pattern(count, r, &ask, a);
          schetchik(r, ask, &cc, &ch);
          printing_results(r, ask, q, k, a, cs);
        }
      }
      print(r, cc, ch, k, q);
      cs = 0;
      fclose(f);
    } else {
      er = 1;
      strcpy(r->erfile[erf], r->argf[k]);
      erf++;
    }
    ch = 0;
    cc = 0;
  }
  if (er == 1 && r->s == 0) {
    for (int p = 0; p < erf; p++) {
      fprintf(stderr, "s21_grep: %s: file or directory doesn't exist\n",
              r->erfile[p]);
    }
  }
}
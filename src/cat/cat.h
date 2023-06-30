#ifndef CAT_H
#define CAT_H

typedef struct {
  int n;
  int b;
  int e;
  int t;
  int v;
  int s;
  int eB;
  int tB;
} Flag;

int parser(int argc, char *argv[], Flag *r);
void flag_b_number(char bs, int *j, char a);
void flag_n_number(char bs, int *j);
void flag_e_E(char a);
void flag_s(char a, char bs, char cs, int *count);
void flag_t_T(char a, int *p);
void flag_v(char a, int *u);
void file_check(FILE *f, Flag *r, int *j, char *a, char *bs, char *cs,
                int *count, char *argv[], int k);
void open_file(int argc, char *argv[], FILE *f, Flag *r);

#endif  // CAT_H
TARGET = s21_cat
cc = gcc
FLAGS = -Wall -Wextra -Werror

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

$(TARGET) : s21_cat.o cat_functions.o
	$(cc) $(FLAGS) s21_cat.o cat_functions.o -o $(TARGET)

#s21_cat.o : s21_cat.c
#	$(cc) -c $(FLAGS) s21_cat.c -o s21_cat.o

#cat_functions.o : cat_functions.c
#	$(cc) -c $(FLAGS) cat_functions.c -o cat_functions.o

%.o : %.c
	$(cc) -c $< -o $@

clean :
	rm -rf $(TARGET) *.o
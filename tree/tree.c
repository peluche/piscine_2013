/* by peluche, */
/* for the swimming pool students of bjtu */
/* hope you enjoyed the week ! :) */

#include <stdlib.h>
#include <time.h>

int spacing;
int decoration_level;

void print_decoration(){
  char s[10] = "\033[22;32m";

  s[6] = '3' + rand() % 6; /* generate a random color for the decoration */
  write(1, s, 8);
  write(1, "o", 1);
}

int rand_it(){
  /* decide if the caracter is a "*" or a decoration "o" */
  return rand() % decoration_level;
}

void print_n_stars(int n){
  int i;

  for (i = 0; i + n / 2 < spacing; ++i)
    write(1, " ", 1);
  for (; n; --n){
    if (rand_it()){
      write(1, "\033[22;32m", 8); /* color the stars "*" in green */
      write(1, "*", 1);
    }
    else
      print_decoration();
  }
  write(1, "\n", 1);
}

void print_n_trunk(int n){
  int i, j, k, thickness;

  write(1, "\033[22;33m", 8); /* color the pipes "|" in "brown"-ish color */
  thickness =  n + ((n % 2) ? 0 : 1);
  for(i = 0; i < n; ++i){
    for (j = 0; j < spacing - thickness / 2; ++j)
      write(1, " ", 1);
    for (k = 0; k < thickness; ++k)
      write(1, "|", 1);
    write(1, "\n", 1);
  }
}

int gen_tree(int taille, int display){
  int i, j, stage = 0, minus = 2, val = 1;

  for (i = 0; i < taille; ++i){
    for (j = 0; j < i + 4; ++j){
      if (display)
        print_n_stars(val);
      val += 2;
    }
    if (i % 2 == 0)
      minus += 2;
    val -= minus;
  }
  if (display)
    print_n_trunk(taille);
  return val += minus;
}

void sapin(int taille){
  spacing = gen_tree(taille, 0) / 2 - 1;
  gen_tree(taille, 1);
}

void print_msg(){
  char s[10] = "\033[22;32m";

  s[6] = '3' + rand() % 6; /* generate a random color for the message */
  write(1, s, 8);
  write(1, "for the 2013 bjtu students from peluche\n", 40);
  write(1, "hope you enjoyed the week ! :)\n", 31);
}

int main(int ac, char **av){
  if (ac < 3){
    write(2, "Usage: ./a.out tree_size decoration_level\n", 43);
    write(2, "Usage: ./a.out 4 5\n", 19);
    return 0;
  }
  srand(time(0));
  decoration_level = (ac > 2) ? atoi(av[2]) : 1;
  while (1){
    write(1, "\033[H\033[2J", 7); /* clear the screen */
    sapin(atoi(av[1]));
    print_msg();
    sleep(1);
  }
  return 0;
}

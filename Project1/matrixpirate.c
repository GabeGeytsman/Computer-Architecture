#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv) {
  if (argc - 1 != 1) {
    printf("Invalid number of arguments");
    return EXIT_SUCCESS;
  }

  FILE *file = fopen(argv[1], "r");

  int size, i;
  int f = fscanf(file, "%d\n", &size);
  printf("Size: %d", size);
  printf("Value of f: %d", f);
  if (f <= 0) {
    return EXIT_SUCCESS;
  }
}
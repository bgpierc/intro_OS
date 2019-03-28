// Chris Fietkiewicz
#include <stdio.h>
#include <omp.h>

int main () {
  int N = 40000;
  #pragma omp parallel
  {
    printf("Running...\n");
    int i, j, sum = 0;
    for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
        sum++;
  }
  return 0;
}


#!/bin/sh
#SBATCH --cpus-per-task=12
#SBATCH --time=0-00:05:00  # 5 minutes

touch output.txt
gcc -o p1 p1.c -lpthread -lrt -lm -fopenmp
for i in {1,12}
  do
    ./p1 $i > output.txt
  done

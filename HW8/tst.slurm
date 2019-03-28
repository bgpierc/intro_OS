#!/bin/sh
#SBATCH --cpus-per-task=2
#SBATCH --time=0-00:05:00  # 5 minutes
#SBATCH --output=output.txt

cp p1.c $PFSDIR/
cd $PFSDIR
gcc -o p1 p1.c -lpthread -lrt -lm -fopenmp
./p1 1






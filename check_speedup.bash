#!/bin/bash

calc(){ awk "BEGIN { print "$*" }"; }

LB='\033[1;34m'
NC='\033[0m'

#make

for i in `seq 1 10`
do
	export OMP_NUM_THREADS=1
	oneTime=`srun -c 2 ./hw2 $1 2 | grep "Parallel version time" | cut -d" " -f4`
	export OMP_NUM_THREADS=4
	fourTime=`srun -c 8 ./hw2 $1 2 | grep "Parallel version time" | cut -d" " -f4`
	export OMP_NUM_THREADS=8
	eightTime=`srun -c 16 ./hw2 $1 2 | grep "Parallel version time" | cut -d" " -f4`
	echo the time are for 1 thread $oneTime, for 4 threads $fourTime and for 8 threads $eightTime
	echo -e "The speed up of run $i is ${LB}`calc $oneTime/$fourTime` and `calc $oneTime/$eightTime` ${NC} "
done

#!/bin/bash

make

if [[ $1 -eq 1 ]] ; then
	export OMP_NUM_THREADS=1
	srun -c 2 ./hw2 $2 1
	export OMP_NUM_THREADS=4
	srun -c 8 ./hw2 $2 1
	export OMP_NUM_THREADS=8
	srun -c 16 ./hw2 $2 1
fi
if [[ $1 -eq 2 ]] ; then
	export OMP_NUM_THREADS=1
	srun -c 2 ./hw2 $2 2
	export OMP_NUM_THREADS=4
	srun -c 8 ./hw2 $2 2
	export OMP_NUM_THREADS=8
	srun -c 16 ./hw2 $2 2
	export OMP_NUM_THREADS=16
	srun -c 32 ./hw2 $2 2
	export OMP_NUM_THREADS=32
	srun -c 64 ./hw2 $2 2
fi
# test for the first dry question
if [[ $1 -eq 3 ]] ; then
	export OMP_NUM_THREADS=1
	srun -c 16 ./hw2 16777216 2
	export OMP_NUM_THREADS=2
	srun -c 16 ./hw2 16777216 2
  	export OMP_NUM_THREADS=4
	srun -c 16 ./hw2 16777216 2
	export OMP_NUM_THREADS=8
 	srun -c 16 ./hw2 16777216 2
 	export OMP_NUM_THREADS=16
 	srun -c 16 ./hw2 16777216 2
 	export OMP_NUM_THREADS=32
 	srun -c 16 ./hw2 16777216 2
  	export OMP_NUM_THREADS=64
  	srun -c 16 ./hw2 16777216 2
fi

if [[ $1 -eq 4 ]] ; then
	export OMP_NUM_THREADS=64
	srun -c 16 ./hw2 262144 2
 	srun -c 16 ./hw2 1048576 2
  	srun -c 16 ./hw2 4194304 2
  	srun -c 16 ./hw2 16777216 2
  	srun -c 16 ./hw2 67108864 2
fi
if [[ $1 -eq 5 ]] ; then
	export OMP_NUM_THREADS=1
	srun -c 16 ./hw2 262144 2 | grep "Parallel version"
        srun -c 16 ./hw2 1048576 2 | grep "Parallel version"
        srun -c 16 ./hw2 4194304 2 |grep "Parallel version"
	export OMP_NUM_THREADS=8
	srun -c 16 ./hw2 262144 2
        srun -c 16 ./hw2 1048576 2
        srun -c 16 ./hw2 4194304 2
fi

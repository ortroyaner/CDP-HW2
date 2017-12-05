#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

int numberOfSetBits(uint32_t i)
{
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

int* createCol(int col, int vecSize){
    int* col = (int*)malloc(sizeof(int)*vecSize);
    if(col==null) exit(1); // it might be !col in C. not sure.
    for(int i=0; i<vecSize; i++){
        col[i] = (numberOfSetBits(i&col) % 2 == 0)*2 - 1;
    }
    return col;
}

void fast_parallel_walsh(int* vec, int vecSize)
{
}

void simple_parallel_walsh(int* vec, int vecSize)
{
    // if the vector is of size 1 or less (0), we dont need to do anything and we can just return it as is
    if(vecSize<=1) return vec;

    //allocate a tmp vector to save the results until we're done.
    int* tmpRes = (int*)malloc(sizeof(int)*vecSize);
    if(tmpRes==null) exit(1);

    // let's calc the value in each cell in the vector
    //in this section, we can create multiple threads to compute this part
    #pragma omp for schedule(static)
    for(int i=0; i<vecSize; i++){
        //first, create the right col from the hadamard matrix
        int* col = createCol(i,vecSize);

        //go over the created col and the original vec to multiple
        for(int j=0; j<vecSize; j++){
            tmpRes[i] += col[j]*vec[j];
        }

        //free the col before next iteration allocation
        free(col);
    }

    //move the results from the tmpVec to vec, and fre tmpVec
    //all threads must finish calculating before moving to copy the results, and free-ing the tmpRes vector
    #pragma omp barrier
    #pragma omp for schedule(static)
    for(int i=0; i<vecSize; i++){
        vec[i]=tmpRes[i];
    }
    free(tmpRes);
}

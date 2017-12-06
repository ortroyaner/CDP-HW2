#include <stdlib.h>
#include <stdint.h>

void fast_parallel_walsh(int* vec, int vecSize)
{
    // if the vector is of size 1 or less (0), we dont need to do anything and we can just return it as is
    if(vecSize<=1) return;

    // start to divide the original vecSize into 2 on every step, until we can't divide any longer
    int partition = vecSize >> 1;
    while(partition>1){
        //how many sections do we have to go over in this iteration
        int sections = vecSize/partition;

        // go over all sections - this section can be parallel!
        //#pragma omp parallel for schedule(static)
        for(int i=1; i<sections; i++) {
            // in here we want to have two indexes to vec: 0 and 0+partitionSize/2
            int secondPart = i*partition;

            // go over all the current vector to calculate the new values
            for (int j = 0; j < partition; j++) {
                vec[j] = vec[j] + vec[j + secondPart];
                vec[j + secondPart] = vec[j] - vec[j + secondPart];
            }
        }
        partition >>= 1;
    }
}

int numberOfSetBits(uint32_t i)
{
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

int* createCol(int colNum, int vecSize){
    int* col = (int*)malloc(sizeof(int)*vecSize);
    if(!col) exit(1);
    for(int i=0; i<vecSize; i++){
        col[i] = (numberOfSetBits(i&colNum) % 2 == 0)*2 - 1;
    }
    return col;
}

void simple_parallel_walsh(int* vec, int vecSize)
{
    // if the vector is of size 1 or less (0), we dont need to do anything and we can just return it as is
    if(vecSize<=1) return;

    //allocate a tmp vector to save the results until we're done.
    int* tmpRes = (int*)malloc(sizeof(int)*vecSize);
    if(!tmpRes) exit(1);

    // let's calc the value in each cell in the vector
    //in this section, we can create multiple threads to compute this part
    //#pragma omp for schedule(static)
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
    //#pragma omp barrier
    //#pragma omp for schedule(static)
    for(int i=0; i<vecSize; i++){
        vec[i]=tmpRes[i];
    }
    free(tmpRes);
}

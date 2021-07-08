#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define upper 1000
#define lower 0

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
sub-array of arr to be sorted */


//int arr[], int l, int r
void* mergeSort(void* args)
{
    int* arr = ((int**)args)[0];
    int l = ((int**)args)[1][0];
    int r = ((int**)args)[1][1];
    //mergeSort(arr,0,size-1);
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        int l_r[2] = {l,m};
        int l_r_2[2] = {m+1,r};

        int* args[] = {arr,l_r};
        int* args2[] = {arr,l_r_2};

        pthread_t tid;
        pthread_t tid2;

        pthread_create(&tid,NULL,mergeSort,(void*)args);
        pthread_create(&tid2,NULL,mergeSort,(void*)args2);
        pthread_join(tid,NULL);
        pthread_join(tid2,NULL);
 
        merge(arr, l, m, r);
        pthread_exit(NULL);
    }
}

int getRandomNumber(){
    return (rand() % (2 * (upper - lower + 1))) + lower - upper;
}

void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void getInput(int* size, int* arr){
    FILE* inputFile;
    inputFile  = fopen ("input.txt", "r");
    
    fscanf (inputFile, "%d", size); 
    int i=0;
    while (!feof (inputFile))
    {  
      //printf ("%d ", i);
      fscanf (inputFile, "%d", &arr[i]);
      ++i;    
    }
    fclose(inputFile);
}

int main(){
    int* size;
    int* arr = (int*)malloc(1000 * sizeof(int));
    getInput(size,arr);
    //int i;
    //int arr[size];
    // for (i=0;i<size;i++){
    //     arr[i] = getRandomNumber();
    // }
    printf("\nArray:\n");
    printArray(arr,*size);
    int l_r[2] = {0,*size-1};
    //mergeSort(arr,0,size-1);

    int* args[] = {arr,l_r};
    pthread_t tid;
    pthread_create(&tid,NULL,mergeSort,(void*)args);
    pthread_join(tid,NULL);
    
    printf("\nSorted Array:\n");
    printArray(arr,*size);
    free(arr);
    return 0;
}
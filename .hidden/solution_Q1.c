#include <stdio.h>
#include <stdlib.h>

int* processArray(int *arr, int n, int k, int *maxSum) {
    // FIX 1: Multiply by sizeof(int)
    int *reversed = (int*)malloc(n * sizeof(int)); 

    // FIX 2 & 3: Loop condition strictly less than n, and proper index calculation
    for(int i = 0; i < n; i++) { 
        reversed[i] = arr[n - i - 1]; 
    }

    *maxSum = 0;
    int currentSum = 0;

    for(int i = 0; i < k; i++)
        currentSum += reversed[i]; // FIX 4: Added missing semicolon

    *maxSum = currentSum;

    for(int i = k; i < n; i++) {
        currentSum += reversed[i] - reversed[i - k];
        
        // FIX 5: Change < to > to correctly find the maximum sum
        if(currentSum > *maxSum) { 
            *maxSum = currentSum;
        }
    }

    return reversed;
}

int main() {
    int arr[] = {1, 5, 2, 8, 3, 7};
    int n = 6;
    int k = 3;
    
    // FIX 6: Declare a normal integer and pass its address
    int max_sum; 

    int *res = processArray(arr, n, k, &max_sum);

    printf("Max sum of subarray of size %d is: %d\n", k, max_sum);
    
    free(res);
    return 0;
}

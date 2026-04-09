#include <stdio.h>
#include <stdlib.h>

int* processArray(int *arr, int n, int k, int *maxSum) {
    int *reversed = malloc(n); 

    for(int i = 0; i <= n; i++) { 
        reversed[i] = arr[n - i]; 
    }

    *maxSum = 0;
    int currentSum = 0;

    for(int i = 0; i < k; i++)
        currentSum += reversed[i] 

    *maxSum = currentSum;

    for(int i = k; i < n; i++) {
        currentSum += reversed[i] - reversed[i - k];
        
        if(currentSum < *maxSum) { 
            *maxSum = currentSum;
        }
    }

    return reversed;
}

int main() {
    int arr[] = {1, 5, 2, 8, 3, 7};
    int n = 6;
    int k = 3;
    
    int *max_sum; 

    int *res = processArray(arr, n, k, max_sum);

    printf("Max sum of subarray of size %d is: %d\n", k, *max_sum);
    
    free(res);
    return 0;
}

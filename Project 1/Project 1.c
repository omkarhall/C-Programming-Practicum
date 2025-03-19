//
//  Project 1.c
//  Omkar_C
//
//  Created by Veena Halleppanavar on 9/3/21.
//

#include <stdio.h>
#include <stdlib.h>
void arrayCopy (int fromArray[], int toArray[], int size){
    for (int i = 0; i < size; i++){
        toArray[i] = fromArray[i];
    }
}
void myFavoriteSort (int arr[], int size){
    for (int i = 0; i < size-1; i++){
        int min = i;
        for (int j = i+1; j < size; j++){
            if (arr[i] < arr[min]){
                min = j;
            }
        }
        int temp = arr[i]; //swap
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void linSearch (int arr[], int size, int target, int* pos, int* linComparisons){
    int found = 0; // 0 if target not found, 1 if found
    *linComparisons = 0; //reset numComparisons
    for (int i = 0; i < size; i++){
        *linComparisons += 1;
        if (target == arr[i]){
            *pos = i;
            found = 1;
            break;
        }
        
    }
    
    if (found == 0){
        *pos = -1;
    }
}

void binSearch (int arr[], int size, int target, int* pos, int* binComparisons){
    int low = 0;
    int high = size-1;
    *binComparisons = 0; //reset numComparisons
    while (low <= high){
        //*binComparisons += 1;
        int mid = (low + high)/2;
        if (arr[mid] == target){
            *pos = mid;
            *binComparisons += 1;
            break;
        }
        else if (arr[mid] < target){
            low = mid + 1;
            *binComparisons += 1;
        }
        else{
            high = mid - 1;
            *binComparisons += 1;
        }
    }
}


int main(){
    int val = 0; //user input
    int ctr = 0; //counter to check if array is full
    int *darr;
    int size = 5;
    darr = (int *) malloc (size * sizeof(int) );
    
    while (val != -999){
        printf("Enter an integer. If you wish to stop entering integers type -999: ");
        scanf("%d", &val);
        printf("\n");
        if (ctr == size - 1){
            int *temp = darr;
            darr = (int *) malloc ( size * 2 * sizeof(int) );
            for (int i = 0 ; i < size ; i++)
            darr[i] = temp[i];
            free (temp);
            size = size * 2;
        }
        if (val != -999){ //dont add val to array if it is -999
            darr[ctr] = val;
            ctr++;
        }
    }
    
    int newSize = ctr + 1;
    int toArr[newSize];
    arrayCopy(darr, toArr, newSize);
    myFavoriteSort (toArr, newSize);
    
    int p = 0;
    int n = 0;
    int *pos = &p;
    int *linComparisons = &n;
    int n2 = 0;
    int *binComparisons = &n2;
    val = 0; //reset val
    while (val != -999){
        printf("Enter an integer target value. If you wish to stop entering integers type -999: ");
        scanf("%d", &val);
        if (val != -999) {
            linSearch(darr, newSize, val, pos, linComparisons);
            printf("For linear search:\n");
            if (*pos != -1){
                printf("The value was found in the array.\n");
                printf("The number of comparisons needed to determine whether the value exists or not was:%d\n", *linComparisons);
                printf("The location in the array where the number is located is:%d\n", *pos);
            }
            else {
                printf("The value was not found in the array.\n");
            }
        
            binSearch(toArr, newSize, val, pos, binComparisons);
            printf("For binary search:\n");
            if (*pos != -1){
                printf("The value was found in the array.\n");
                printf("The number of comparisons needed to determine whether the value exists or not was:%d\n", *binComparisons);
                printf("The location in the array where the number is located is:%d\n", *pos);
            }
            else {
                printf("The value was not found in the array.\n");
            }
        }
        
    }
    
}

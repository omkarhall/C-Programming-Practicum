/**
* File:  prog3.c
*
* Description:  implements the functions described in prog3.h
*  Created by Omkarnath Halleppanawar
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "prog3.h"



/**
*
*  Function "stubs" for Assignment 3 exercises.
*
*  See prog3.h for specifications of function behavior.
*
*/



/***********************************************
*                                             **
*   MATRIX FUNCTIONS                          **
*                                             **
*   NOTE:  parameter n ALWAYS expresses the   **
*     dimensions of the square matrix in      **
*     question.                               **
*                                             **
***********************************************/


char ** alloc_square_mtx(int n) {
    char** matrix = (char**)malloc(n*sizeof(char*));
    for (int i = 0; i < n; i++){
        matrix[i] = (char*)malloc(n*sizeof(char));
    }
    return matrix;

}

void free_square_mtx(char **m, int n) {
    for (int i = 0; i < n; i++){
        free(m[i]);
    }
    free(m);
}

void pop_mtx_alpha(char **m, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            m[i][j] = rand() % (122-97) + 97;
        }
    }
}

void display_mtx(char **m, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%c ", m[i][j]);
        }
        printf("\n");
    }
}

void swap_rows(char **m, int n, int r1, int r2){
    int swap = 0;
    if (r1 < 0 || r2 < 0 || r1 >= n || r2 >= n){
        swap = 1; //do nothing
    }
    if (swap == 0){
        char * rtemp;
        rtemp = m[r1];
        m[r1] = m[r2];
        m[r2] = rtemp;
    }

}

void swap_cols(char **m, int n, int c1, int c2){
    int swap = 0;
    if (c1 < 0 || c2 < 0 || c1 >= n || c2 >= n){
        swap = 1; //do nothing
    }
    if (swap == 0){
        for (int i = 0; i < n; i++){
            char temp = m[i][c1];
            m[i][c1] = m[i][c2];
            m[i][c2] = temp;
        }
    }
}

void rotate_right(char **m, int n){
    //transpose matrix
    for (int i = 0; i < n; i++){
        for (int j = 0; j < i; j++){
            char temp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = temp;
        }
    }
    //swap columns
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n/2; j++){
            swap_cols(m, n, j, n-j-1);
        }
    }
}

void floating_boulders(char **m, int n, int nb){
    if (nb < 0){
        nb = 0;
    }
    if (nb > n*n){
        nb = n*n;
    }
    pop_mtx_alpha(m, n); //called to reset given matrix and get rid of any preexisting '#'
    //place nb boulders into random locations in the matrix
    while (nb > 0){
        //srand(time(NULL));
        int i = rand() % n; //random index for row
        int j = rand() % n; //random index for col
        /*
        if (m[i][j] == NULL){
            m[i][j] = '#';
            nb--;
        }
        else*/
        if (m[i][j] != '#'){
            m[i][j] = '#';
            nb--;
        }
    }
    //fill all remaining spots in matrix with '.'
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            /*
            if (m[i] == NULL){
                m[i][j] = '.';
            }
             
            else*/
            if (m[i][j] != '#'){
                m[i][j] = '.';
            }
        }
    }
}

void mountains(char **m, int n){
    floating_boulders(m, n, rand() % (n*n)); //places random number of boulders into landscape
    //rearrange landscape so that 'air' is above 'land'
    for (int c = 0; c < n; c++){
        int nums = 0; // number of '.' in each column
        for (int r = 0; r < n; r++){
            if (/*m[r][c] != NULL && */m[r][c] == '.'){
                nums++;
            }
        }
        for (int r = 0; r < n; r++){
            if (nums > 0){
                m[r][c] = '.';
                nums--;
            }
            else {
                m[r][c] = '#';
            }
        }
    }
}



void sink(char **m, int n){
    //swap rows starting at botttom until bottom row ends up on top
    for (int i = n - 1; i >= 1; i--){
        swap_rows(m, n, i, i-1);
    }
    //replace all elements in top row with '.'
    for (int k = 0; k < n; k++){
        m[0][k] = '.';
    }
     
}



void gravity(char **m, int n){
    char list[n*n]; //list of all elements of m that are not '.' in order of col top to bottom
    int index = 0; //index for list
    
    for (int c = 0; c < n; c++){
        for (int r = 0; r < n; r++){
            if (m[r][c] != '.'){
                list[index] = m[r][c];
                index++;
            }
        }
    }
    index = 0; //reset index
    for (int c = 0; c < n; c++){
        int nums = 0; //number of '.' in each column
        for (int r = 0; r < n; r++){
            if (/*m[r][c] != NULL && */m[r][c] == '.'){
                nums++;
            }
        }
        for (int r = 0; r < n; r++){
            if (nums > 0){
                m[r][c] = '.';
                nums--;
            }
            else {
                m[r][c] = list[index];
                index++;
            }
        }
    }
}




/***********************************************
*                                             **
*   STRING FUNCTIONS                          **
*                                             **
***********************************************/


void str_trim(char *s) {
    int i, j;
    //increase index of string until reaching first non whitespace character
    for (i = 0; isspace(s[i]); i++);
    
    //remove leading whitespace
    for (j = 0; s[i]; i++){
        s[j++] = s[i];
    }
    s[j] = '\0';
    
    //remove trailing whitespace
    for (i = 0; s[i] != '\0'; i++){
        if (!isspace(s[i])){
            j = i;
        }
    }
    s[j+1] = '\0';
}


int str_search(char *s, char *pattern) {
    int len1 = strlen(pattern); //length of pattern
    int len2 = strlen(s); //length of s
    for (int i = 0; i <= (len2 - len1); i++){
        int j;
        for (j = 0; j < len1; j++){
            if (s[i+j] != pattern[j]){
                break;
            }
        }
        if (j == len1){
            return i;
        }
    }
    return -1;

}





#ifndef _LIB  // DO NOT REMOVE THIS LINE!!!
              // IT DOESN"T CHANGE HOW YOUR PROGRAM
              // WORKS, BUT IT GIVES US A WAY TO CALL
              // YOUR FUNCTIONS FROM OUR CODE FOR
              // TESTING

/**
* Write a test driver in main below to exercise and
*   your function implementations.
*
* Think carefully about your test cases!
*/
int main(){
    //test driver
    ///*
    //tests alloc_square_mtx
    char ** matrix = alloc_square_mtx(3);
    
    srand(time(NULL));
    
    //tests pop_mtx_alpha and display_mtx
    printf("Matrix after running pop_mtx_alpha(): \n");
    pop_mtx_alpha (matrix, 3);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Matrix after running display_mtx() should match: \n");
    display_mtx(matrix, 3);
    
    //tests swap_rows
    printf("\nTests for swap_rows: \n\n");
    //test where row1<0
    swap_rows(matrix, 3, -1, 1);
    printf("Row 1 < 0. Expected output: no changes.\n");
    display_mtx(matrix, 3);
    //test where row1>=n
    swap_rows(matrix, 3, 5, 1);
    printf("Row 1 >= n. Expected output: no changes.\n");
    display_mtx(matrix, 3);
    //test where row2<0
    swap_rows(matrix, 3, 0, -1);
    printf("Row 2 < 0. Expected output: no changes.\n");
    display_mtx(matrix, 3);
    //test where row2>=n
    swap_rows(matrix, 3, 0, 5);
    printf("Row 2 >= n. Expected output: no changes.\n");
    display_mtx(matrix, 3);
    //test where both rows are out of range
    swap_rows(matrix, 3, -1, 5);
    printf("Both rows out of range. Expected output: no changes.\n");
    display_mtx(matrix, 3);
    //swap rows 0 and 0 -- nothing should change
    swap_rows(matrix, 3, 0, 0);
    printf("Swap rows 0 and 0. Expected output: no changes.\n");
    display_mtx(matrix, 3);
    //swap rows 0 and 1
    swap_rows(matrix, 3, 0, 1);
    printf("Expected output: rows 0 and 1 are flipped.\n");
    display_mtx(matrix, 3);
    //swap rows 1 and 0
    swap_rows(matrix, 3, 1, 0);
    printf("Expected output: rows 1 and 0 are flipped.\n");
    display_mtx(matrix, 3);
    //swap rows 0 and 2
    swap_rows(matrix, 3, 0, 2);
    printf("Expected output: rows 0 and 2 are flipped.\n");
    display_mtx(matrix, 3);
    //swap rows 2 and 0
    swap_rows(matrix, 3, 2, 0);
    printf("Expected output: rows 2 and 0 are flipped.\n");
    display_mtx(matrix, 3);
    //swap rows 1 and 2
    swap_rows(matrix, 3, 1, 2);
    printf("Expected output: rows 1 and 2 are flipped.\n");
    display_mtx(matrix, 3);
    //swap rows 2 and 1
    swap_rows(matrix, 3, 2, 1);
    printf("Expected output: rows 2 and 1 are flipped.\n");
    display_mtx(matrix, 3);
    
    
    //tests swap_cols
    printf("\nTests for swap_cols: \n\n");
    //test where col1<0
    swap_cols(matrix, 3, -1, 1);
    printf("Col 1 < 0. Expected output: no changes.\n");
    display_mtx(matrix, 3);
    //test where col1>=n
    swap_cols(matrix, 3, 5, 1);
    printf("Col 1 >= n. Expected output: no changes.\n");
    display_mtx(matrix, 3);
    //test where col2<0
    swap_cols(matrix, 3, 0, -1);
    printf("Col 2 < 0. Expected output: no changes.\n");
    display_mtx(matrix, 3);
    //test where col2>=n
    swap_cols(matrix, 3, 0, 5);
    printf("Col 2 >= n. Expected output: no changes.\n");
    display_mtx(matrix, 3);
    //test where both cols are out of range
    swap_cols(matrix, 3, -1, 5);
    printf("Both cols out of range. Expected output: no changes.\n");
    display_mtx(matrix, 3);
    //swap cols 0 and 0 -- nothing should change
    swap_cols(matrix, 3, 0, 0);
    printf("Swap cols 0 and 0. Expected output: no changes.\n");
    display_mtx(matrix, 3);
    //swap cols 0 and 1
    swap_cols(matrix, 3, 0, 1);
    printf("Expected output: cols 0 and 1 are flipped.\n");
    display_mtx(matrix, 3);
    //swap cols 1 and 0
    swap_cols(matrix, 3, 1, 0);
    printf("Expected output: cols 1 and 0 are flipped.\n");
    display_mtx(matrix, 3);
    //swap cols 0 and 2
    swap_cols(matrix, 3, 0, 2);
    printf("Expected output: cols 0 and 2 are flipped.\n");
    display_mtx(matrix, 3);
    //swap rows 2 and 0
    swap_cols(matrix, 3, 2, 0);
    printf("Expected output: cols 2 and 0 are flipped.\n");
    display_mtx(matrix, 3);
    //swap cols 1 and 2
    swap_cols(matrix, 3, 1, 2);
    printf("Expected output: cols 1 and 2 are flipped.\n");
    display_mtx(matrix, 3);
    //swap cols 2 and 1
    swap_cols(matrix, 3, 2, 1);
    printf("Expected output: cols 1 and 1 are flipped.\n");
    display_mtx(matrix, 3);
    
    //tests rotate right
    printf("\nTests for rotate_right: \n\n");
    //original matrix
    printf("Original matrix: \n");
    display_mtx(matrix, 3);
    //rotate once - total of 90 degrees
    rotate_right(matrix, 3);
    printf("Expected output: matrix rotated 90 degrees to the right.\n");
    display_mtx(matrix, 3);
    //rotate again - total of 180 degrees
    rotate_right(matrix, 3);
    printf("Expected output: matrix rotated 90 degrees to the right.\n");
    display_mtx(matrix, 3);
    //rotate 3rd time - total of 270 degrees
    rotate_right(matrix, 3);
    printf("Expected output: matrix rotated 90 degrees to the right.\n");
    display_mtx(matrix, 3);
    //rotate 4th time - matrix should be back in original position.
    rotate_right(matrix, 3);
    printf("Expected output: matrix back in original position.\n");
    display_mtx(matrix, 3);
    
    //tests free_square_mtx
    free_square_mtx(matrix, 3);
    
    //create new matrix to test other functions
    char ** new_matrix = alloc_square_mtx(4);
    
    //tests floating boulders
    printf("\nTests for floating_boulders: \n\n");
    //test where nb<0
    floating_boulders(new_matrix, 4, -1);
    printf("Expected output: Random landscape with 0 boulders.\n");
    display_mtx(new_matrix, 4);
    //tests where nb is in range
    //test where nb = 5
    floating_boulders(new_matrix, 4, 5);
    printf("Expected output: Random landscape with 5 boulders.\n");
    display_mtx(new_matrix, 4);
    //test where nb = 8
    floating_boulders(new_matrix, 4, 8);
    printf("Expected output: Random landscape with 8 boulders.\n");
    display_mtx(new_matrix, 4);
    //test where nb>n*n
    floating_boulders(new_matrix, 4, 18);
    printf("Expected output: Random landscape with 16 boulders.\n");
    display_mtx(new_matrix, 4);
    
    //tests mountains
    printf("\nTests for mountains: \n\n");
    mountains(new_matrix, 4);
    printf("Expected output: Random landscape with no 'air' below 'land'.\n");
    display_mtx(new_matrix, 4);
    //run again, should get different landscape
    mountains(new_matrix, 4);
    printf("Expected output: Different random landscape with no 'air' below 'land'.\n");
    display_mtx(new_matrix, 4);
    
    
    //tests sink
    printf("\nTests for sink: \n\n");
    //original matrix
    printf("Original matrix: \n");
    display_mtx(new_matrix, 4);
    //call sink
    sink(new_matrix, 4);
    printf("Expected output: matrix shifted down one with row of 'air' on top.\n");
    display_mtx(new_matrix, 4);
    //sink again, should shift one more row down
    sink(new_matrix, 4);
    printf("Expected output: matrix shifted down one with row of 'air' on top.\n");
    display_mtx(new_matrix, 4);
    //sink 3rd time, should shift one more row down
    sink(new_matrix, 4);
    printf("Expected output: matrix shifted down one with row of 'air' on top.\n");
    display_mtx(new_matrix, 4);
    //sink 4th time, matrix should be fully air
    sink(new_matrix, 4);
    printf("Expected output: matrix shifted down one with row of 'air' on top.\n");
    display_mtx(new_matrix, 4);
    
    //tests gravity
    printf("\nTests for gravity: \n\n");
    //matrix with no air should not change
    pop_mtx_alpha(new_matrix, 4);
    printf("Matrix before gravity is called:\n");
    display_mtx(new_matrix, 4);
    gravity(new_matrix, 4);
    printf("Matrix after gravity is called:\n");
    display_mtx(new_matrix, 4);
    
    //matrix with only air should not change
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            new_matrix[i][j] = '.';
        }
    }
    printf("Matrix before gravity is called:\n");
    display_mtx(new_matrix, 4);
    gravity(new_matrix, 4);
    printf("Matrix after gravity is called:\n");
    display_mtx(new_matrix, 4);
    
    //test for matrix with some air and some objects
    pop_mtx_alpha(new_matrix, 4);
    new_matrix[0][2] = '.';
    new_matrix[0][3] = '.';
    new_matrix[1][1] = '.';
    new_matrix[1][3] = '.';
    new_matrix[3][0] = '.';
    new_matrix[2][2] = '.';
    printf("Matrix before gravity is called:\n");
    display_mtx(new_matrix, 4);
    gravity(new_matrix, 4);
    printf("Matrix after gravity is called:\n");
    display_mtx(new_matrix, 4);
    
    //test for matrix with more air and some objects
    pop_mtx_alpha(new_matrix, 4);
    new_matrix[0][2] = '.';
    new_matrix[0][3] = '.';
    new_matrix[1][1] = '.';
    new_matrix[1][0] = '.';
    new_matrix[2][2] = '.';
    new_matrix[2][3] = '.';
    new_matrix[3][0] = '.';
    new_matrix[3][2] = '.';
    printf("Matrix before gravity is called:\n");
    display_mtx(new_matrix, 4);
    gravity(new_matrix, 4);
    printf("Matrix after gravity is called:\n");
    display_mtx(new_matrix, 4);
    printf("\n");
    //*/
    
    //tests str_trim using user input
    char string[100];
    while (strcmp(string, "quit") != 0){
        printf("Enter a string for str_trim (100 char or less) ('quit' to quit): ");
        gets(string);
        if (strcmp(string, "quit") != 0){
            printf("String before calling str_trim: '%s'", string);
            str_trim(string);
            printf("\nString after calling str_trim: '%s'\n\n", string);
        }
    }
    
    //tests str_search using user input
    char new_string[100];
    char pattern[100];
    while (strcmp(new_string, "quit") != 0){
        printf("\nEnter a string for str_search to search (100 char or less) ('quit' to quit): ");
        gets(new_string);
        if (strcmp(new_string, "quit") != 0){
            printf("Enter a pattern (100 char or less): ");
            gets(pattern);
            printf("String: '%s' and Pattern: '%s'\n", new_string, pattern);
            int result = str_search(new_string, pattern);
            printf("Result: %d\n", result);
        }
    }
}


#endif        // DO NOT REMOVE THIS LINE!!!

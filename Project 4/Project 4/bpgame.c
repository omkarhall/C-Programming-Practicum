//
//
//  Project 4
//
//  Author: Sammy Dandu and Omkar Hallepenawar, UIC, Fall 2021
//
//  Description: Simple version of playing Balloon Pop

//


// file:  bpgame.c


/** #include statements... **/
#include <stdio.h>
#include <stdlib.h>
#include "bpgame.h"
#include <time.h>
/** TYPEDEFS / STRUCTs HERE ***/


struct bpgame{
    char ** board;
    int cols;
    int rows;
    int score;
    
    char*** change_array; //stores boards for undo
    int score_array[100]; //stores scores for undo
    int top; //top of change array
    int size; //size of change array
   // YOU DECIDE WHAT TO PUT IN HERE TO CAPTURE THE STATE OF
   //   A "RUN" OF THE GAME.....
};

//struct for friendBoard
struct cell{
    int visited;
    int friend;
};

BPGame * bp_create(int nrows, int ncols){
    //check if parameters are out of range
    if (nrows < 0 || ncols < 0 || nrows >= MAX_ROWS || ncols >= MAX_COLS){
        fprintf(stderr, "ncols or nrows is out of range");
        return NULL;
    }

    BPGame* bpgame = malloc(sizeof(BPGame));
    bpgame->change_array = (char***)malloc(100*sizeof(char**));
    for (int i = 0; i < 100; i++){
        bpgame->change_array[i] = (char **)malloc(nrows*sizeof(char*));
        for (int j = 0; j < nrows; j++){
            bpgame->change_array[i][j] = (char*)malloc(ncols*sizeof(char));
        }
        
    }
    
    char** matrix = (char**)malloc(nrows*sizeof(char*));
    for (int i = 0; i < nrows; i++){
        matrix[i] = (char*)malloc(ncols*sizeof(char));
    }
    char array[4] = {Red,Blue,Green,Yellow};
    srand(time(NULL));
    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){
            //int random = rand() % 4 + 1;
            matrix[i][j] = array[rand() % 4];
            bpgame->change_array[0][i][j] = matrix[i][j];
        }
    }
    bpgame -> board = matrix;
    bpgame -> score = 0;
    bpgame -> cols = ncols;
    bpgame -> rows = nrows;
    bpgame -> top = 0;
    bpgame -> size = 1;
    bpgame->score_array[bpgame->top]=0;
    return bpgame;
    
}

BPGame * bp_create_from_mtx(char mtx[][MAX_COLS], int nrows, int ncols){
    //check if parameters are out of range
    if (nrows < 0 || ncols < 0 || nrows >= MAX_ROWS || ncols >= MAX_COLS){
        fprintf(stderr, "ncols or nrows is out of range");
        return NULL;
    }
    //check if contents of mtx are valid
    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){
            if (mtx[i][j] != Blue && mtx[i][j] != Red && mtx[i][j] != Green && mtx[i][j] != Yellow
                && mtx[i][j] != None){
                fprintf(stderr, "Not all elements of array are understood color symbols");
                return NULL;
            }
        }
    }
    BPGame* bpgame = malloc(sizeof(BPGame));
    bpgame->change_array = (char***)malloc(100*sizeof(char**));
    for (int i = 0; i < 100; i++){
        bpgame->change_array[i] = (char **)malloc(nrows*sizeof(char*));
        for (int j = 0; j < nrows; j++){
            bpgame->change_array[i][j] = (char*)malloc(ncols*sizeof(char));
        }
        
    }

    char** matrix = (char**)malloc(nrows*sizeof(char*));
    for (int i = 0; i < nrows; i++){
        matrix[i] = (char*)malloc(ncols*sizeof(char));
    }
    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){
            matrix[i][j] = mtx[i][j];
            bpgame->change_array[0][i][j] = matrix[i][j];
        }
    }
    bpgame -> board = matrix;
    bpgame -> score = 0;
    bpgame -> cols = ncols;
    bpgame -> rows = nrows;
    bpgame -> top = 0;
    bpgame -> size = 1;
    bpgame->score_array[bpgame->top]=0;
    
    return bpgame;
    
}

void bp_destroy(BPGame * b){
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < b->rows; j++){
            free(b->change_array[i][j]);
        }
        free(b->change_array[i]);
      }
      free(b->change_array);
    
    for (int i = 0; i < b->rows; i++){
        free(b->board[i]);
    }
    free(b->board);
    free(b);
    //Need to destroy change_array, board, and b
}

void bp_display(BPGame * b){
    printf("  +");
    for (int i = 0; i < b->cols*3; i++){
        printf("-");
    }
    printf("+\n");
    for (int i = 0; i < b->rows; i++){
        if (i < 10)
            printf("%d |",i);
        else
            printf("%d|",i);
        for (int j = 0; j < b->cols; j++){
            printf(" %c ",b->board[i][j]);
        }
        printf("|\n");
    }
    printf("  +");
    for (int i = 0; i < b->cols*3; i++){
        printf("-");
    }
    printf("+\n");
    printf("   ");
    for (int i = 0; i < b->cols; i++){
        if (i < 10){
            printf(" %d ",0);
        }
        else{
            int num = i;
            while (num >= 10){
                num/=10;
            }
            printf(" %d ",num);
        }
    }
    printf("\n");
    printf("   ");
    for (int i = 0; i < b->cols; i++){
        if (i < 10){
            printf(" %d ",i);
        }
        else{
            int num = i;
            printf(" %d ",num%10);
        }
    }
}
/*
struct cell{
    int visited;
    int friend;
};
*/
void findFriend(BPGame * b, struct cell friendBoard[b->rows][b->cols], int row, int col, char color){
    if (row >= b->rows || row < 0 || col >= b->cols || col < 0){
        return;
    }
    if (friendBoard[row][col].visited == 1){
        return;
    }
    else{
        friendBoard[row][col].visited = 1;
        if (b->board[row][col] == color){
            friendBoard[row][col].friend = 1;
            if ((col - 1) >= 0)
                findFriend(b, friendBoard, row, col-1, color);
            if ((col + 1) <= b->cols)
                findFriend(b, friendBoard, row, col+1, color);
            if ((row + 1) <= b->rows)
                findFriend(b, friendBoard, row+1, col, color);
            if ((row - 1) >= 0)
                findFriend(b, friendBoard, row-1, col, color);
        }
    }
    return;
}

int bp_pop(BPGame * b, int r, int c){
    int count = 0;
    struct cell friendBoard[b->rows][b->cols];
    if (b->board[r][c] == None){
        return count;
    }
    for (int i = 0; i < b->rows; i++){
        for (int j = 0; j < b->cols; j++){
            friendBoard[i][j].visited = -1;
            friendBoard[i][j].friend = -1;
        }
    }
    findFriend(b, friendBoard, r, c, b->board[r][c]);
    for (int i = 0; i < b->rows; i++){
        for (int j = 0; j < b->cols; j++){
            if (friendBoard[i][j].friend == 1){
                count++;
            }
        }
    }

    if (count > 1){
        for (int i = 0; i < b->rows; i++){
            for (int j = 0; j < b->cols; j++){
                b->change_array[b->top][i][j] = b->board[i][j];
            }
        }
        for (int i = 0; i < b->rows; i++){
            for (int j = 0; j < b->cols; j++){
                if (friendBoard[i][j].friend == 1){
                    b->board[i][j] = None;
                }
            }
        }
        b->score_array[b->top]=b->score;
        b->top++;
        b->size++;
    }
    else if (count == 1){
        return 0;
    }
    b->score += count*(count-1);
    return count;
}

int bp_is_compact(BPGame * b){
    for (int i = 0; i < b->cols; i++){
        for (int j = 1; j < b->rows; j++){
            if (b->board[j-1][i] == None && b->board[j][i] != None){
                return 0;
            }
        }
    }
    return 1;
}

void bp_float_one_step(BPGame * b){
    for (int i = 0; i < b->cols; i++){
        for (int j = 1; j < b->rows; j++){
            if (b->board[j-1][i] == None && b->board[j][i] != None){
                char temp = b->board[j-1][i];
                b->board[j-1][i] = b->board[j][i];
                b->board[j][i] = temp;
            }
        }
    }
}

int bp_score(BPGame * b){
    return b->score;
}

int bp_get_balloon(BPGame * b, int r, int c){
    if (r < 0 || c < 0 || r >= b->rows || r >= b->cols){
        return -1;
    }
    return (b->board[r][c]);
}

int bp_can_pop(BPGame * b){
    int count = 0;
    struct cell friendBoard[b->rows][b->cols];
    for (int i = 0; i < b->rows; i++){
        for (int j = 0; j < b->cols; j++){
            friendBoard[i][j].visited = -1;
            friendBoard[i][j].friend = -1;
        }
    }
    //findFriend(b, friendBoard, r, c, b->board[r][c]);
    for (int i = 0; i < b->rows; i++){
        for (int j = 0; j < b->cols; j++){
            if (b->board[i][j] != None){
                findFriend(b, friendBoard, i, j, b->board[i][j]);
                if (friendBoard[i][j].friend == 1){
                    count++;
                }
            }
            if (count > 1){
                return 1;
            }
        }
    }
    return 0;
}

int bp_undo(BPGame * b){
    if (b->size == 1){
        return 0;
    }
    b->top--;
    b->size--;
    for (int i = 0; i < b->rows; i++){
        for (int j = 0; j < b->cols; j++){
            b->board[i][j] = b->change_array[b->top][i][j];
        }
    }
    b->score = b->score_array[b->top];
    return 1;
}

void bp_display_STD(BPGame *b) {
    for (int i = 0; i < b->rows; i++){
        for (int j = 0; j < b->cols; j++){
            printf("%c",b->board[i][j]);
        }
        printf("\n");
    }
    
}

/*** IMPLEMENTATION OF bp_XXXX FUNCTIONS HERE  ****/

/*
int main(int argc, const char * argv[]) {
    // insert code here...
    BPGame* bpgame = bp_create(5,5);
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            printf("%c",bpgame->board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    char array[3][40] = {{Green,Blue,Red},
                         {Red,Blue,Yellow},
                         {Blue,Yellow,Green}};
    BPGame* bpgame2 = bp_create_from_mtx(array, 3, 3);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%c",bpgame2->board[i][j]);
        }
        printf("\n");
    }
    
    
    bp_display(bpgame);
    printf("\n");
    printf("\nUndo: %d\n", bp_undo(bpgame));
    printf("\n");
    bp_display(bpgame);
    int count = bp_pop(bpgame, 3, 2);
    printf("\nCount: %d\n", count);
    printf("\nScore: %d\n", bp_score(bpgame));
    bp_display(bpgame);
    printf("\nUndo: %d\n", bp_undo(bpgame));
    printf("\n");
    bp_display(bpgame);
    printf("\nUndo: %d\n", bp_undo(bpgame));
    printf("\n");
    bp_display(bpgame);
    
    int compact = bp_is_compact(bpgame);
    printf("\nIs compact: %d\n", compact);
    
    bp_float_one_step(bpgame);
    bp_display(bpgame);
    printf("\nCan pop: %d\n", bp_can_pop(bpgame));
    
    char new_array[3][40] = {{None,None,None},
                         {None,None,None},
                         {None,None,None}};
    BPGame* bpgame3 = bp_create_from_mtx(new_array, 3, 3);
    printf("\n");
    bp_display(bpgame3);
    printf("\nCan pop: %d\n", bp_can_pop(bpgame3));
    
    bp_destroy(bpgame);
    
    
    return 0;
}
*/

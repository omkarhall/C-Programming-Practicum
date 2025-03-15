//
//  expand.c
//  Project 7
//
//  Created by Omkar Halleppanavar on 12/1/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Struct for nodes of linked list used to make stack
 */
struct node {
    char val[250];
    struct node* next;
};
typedef struct node node;

/*
 * Struct for stack
 */
struct stack {
    struct node* head;
    int size;
};
typedef struct stack stack;

/*
 * Helper function that adds new nodes to queue
 */
node* newNode(char* filename){
    node* temp = malloc(sizeof(node));
    strcpy(temp->val,filename);
    temp->next = NULL;
    return temp;
}

/*
 * Helper function that pushes new node onto front of stack
 */
void push(stack* s, char* filename){
    node* node = newNode(filename);
    if (s->size == 0){
        s->head = node;
    }
    else{
        node->next = s->head;
        s->head = node;
    }
    s->size++;
}

/*
 * Helper function that pops node from front of stack
 */
void pop(stack* s){
    if (s->size == 1){
        node* temp = s->head;
        free(temp);
        s->head = NULL;
        s->size--;
    }
    else{
        node* temp = s->head;
        s->head = s->head->next;
        free(temp);
        s->size--;
    }
}

/*
 * Checks whether the filename is present in stack
 */
int searchStack(stack* s, char* filename){
    node* current = s->head;  // Initialize current
    while (current != NULL)
    {
        if (strcmp(current->val, filename) == 0){
            return 1;
        }
        current = current->next;
    }
    return 0;
}

/*
 * Function that expands file into final form
 */
int expand(stack* s, char* filename){
    char line[257];
    int returnVal = 0;
    
    //open the file for reading
    FILE *fp = fopen(filename, "r");
    //if filepointer is null return error
    if(fp == NULL){
        returnVal = -1;
        fprintf(stderr, "**error: File '%s' doesn't exist!\nExpansion terminated.", filename);
    }
    
    while(returnVal == 0 && fgets(line, 256, fp) != NULL ){
        char line2[257];
        strcpy(line2,line);
        
        //get first string token with space as delimiter
        char* token = strtok(line2," ");
        
        //if first character in the line is # and first string token is = #include
        if(line[0] == '#' && strcmp(token,"#include") == 0){
            
            //then get 2nd token with space as delimiter
            token = strtok(NULL," ");
            
            //if there is no 2nd token then return error
            if(token == NULL){
                returnVal = -1;
                fprintf(stderr, "No filename specified.\n");
                break;
            }
            //confirm first and last character of 2nd token is double quote or else return error
            if((token[0] == '"' && token[strlen(token)-2] == '"') || (token[0] == '"' && token[strlen(token)-1] == '"')){
                
                //remove the double quotes from 2nd token and save it in variable called filename2
                char * filename2 = strtok(token, "\"");
                
                //if filename2 in stack
                //print error message and return -1
                if(searchStack(s, filename2) == 1){
                    fprintf(stderr, "**error: Infinite recursion detected!\nExpansion terminated.");
                    returnVal = -1;
                    break;
                }
                //else
                else {
                    //push filename onto stack
                    push(s, filename2);
                    //expand (stack, new filename)
                    returnVal = expand(s, filename2);
                }
            }
            else{
                returnVal = -1;
                fprintf(stderr, "**error: No file found after '#include'!\nExpansion terminated.");
                break;
            }
        }
        //else (not #include then just print the line)
        else{
            printf("%s", line);
        }
    }
    //pop filename off the stack
    pop(s);
    
    if(fp != NULL){
        //close the file
        fclose(fp);
    }
    return returnVal;
}

int main(int argc, char* argv[]) {
    //check if argc != 2
    if(argc != 2){
        printf("%d\n",argc);
        fprintf(stderr, "Incorrect number of command line arguments.\n");
    }
    else {
        stack* s = malloc(sizeof(stack));
        s->head = NULL;
        s->size = 0;
        //push argv[1] to stack
        char* filename = argv[1];
        push(s, filename);
        //call expand pass filename and stack
        expand(s, filename);
        free(s);
    }
    return 0;
}

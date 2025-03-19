
//
//  ohalle2.proj2.c
//  Project 2
//
//  Created by Omkar Halleppanavar on 9/19/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE  1
#define FALSE 0

int DebugMode;

/* Stack struct */
struct my_stack {
    char *array;
    int top;
    int size;
};

/* Function that initializes stack */
struct my_stack* init(){
     struct my_stack* stack = malloc(sizeof(struct my_stack));
     
     stack -> array = malloc(2 * sizeof(char));
     stack -> top = -1; //stack starts off empty
     stack -> size = 2; //starting size is 2
     return stack;
}

/* Function that returns 1 if stack is empty 0 otherwise */
int is_empty(struct my_stack* stack){
    if (stack -> top == -1){
        return 1;
    }
    return 0;
}

/* Function to double size of stack */
static void grow(struct my_stack* stack){
    char* new_array;
    int count = 0; //count values copied for DebugMode
    if (DebugMode == TRUE){
        printf("Old size: %d\n", stack->size); //print old size for DebugMode
    }
    stack->size = 2 * stack->size;
    new_array = malloc(stack->size * sizeof(char));
    for (int i = 0; i <= stack->top; i++){
        new_array[i] = stack->array[i];
        count++;
    }
    
    free(stack->array);
    stack->array = new_array;
    
    if (DebugMode == TRUE){
        printf("New size: %d\n", stack->size);
        printf("Number of values copied from the current to the new dynamic array: %d\n", count);
    }
}

/* Function to push value onto stack */
int push(struct my_stack* stack, char c){
    if (stack->top == (stack->size-1)){
        grow(stack);
    }
    stack->top++;
    stack->array[stack->top] = c;
    if (DebugMode == TRUE){
        printf("A value has been pushed onto the stack : %c\n", c);
    }
    return 1;
}

/* Function that pops the top of the stack */
char pop(struct my_stack* stack){
    if (stack->top == -1){
        return -1;
    }
    stack->top--;
    if (DebugMode == TRUE){
        printf("A value has been popped from the stack: %c\n", stack->array[stack->top+1]);
    }
    return stack->array[stack->top+1];
}

/* Function that returns top of stack */
char top(struct my_stack* stack){
    if (stack->top == -1){
        return -1;
    }
    return stack->array[stack->top];
}

/* Function that clears stack */
void clearStack(struct my_stack* stack){
    //I had to change the function name because of a conflicting type error in my IDE
    stack->top = -1;
}

/* Function that returns 1 if char1 and char2 are brackets that match, 0 otherwise */
int isMatching(char char1, char char2)
{
    if (char1 == '(' && char2 == ')')
        return 1;
    else if (char1 == '{' && char2 == '}')
        return 1;
    else if (char1 == '[' && char2 == ']')
        return 1;
    else if (char1 == '<' && char2 == '>')
        return 1;
    else
        return 0;
}

/* Function that returns 1 if the brackets are balanced, 0 otherwise */
int balancedBrackets(char input[], struct my_stack* stack)
{
    int i = 0;
    
    //Go through the input to check matching brackets
    while (input[i])
    {
        //push opening brackets
        if (input[i] == '{' || input[i] == '(' || input[i] == '[' || input[i] == '<'){
            push(stack, input[i]);
        }
        if (input[i] == '}' || input[i] == ')' || input[i] == ']' || input[i] == '>'){
            //ending bracket without a pair, return 2 for error 1
            if (is_empty(stack) == 1){
                return 2;
            }
            //mismatch brackets, return 3 for error 2
            char c = pop(stack);
            if (isMatching(c, input[i]) == 0){
                return 3;
            }
        }
        i++;
    }
    
    if (is_empty(stack) == 1)
        return 1; // balanced
    else
        //line ends while stack is not empty, return 4 for error 3
        return 4;
}

int main (int argc, char** argv)
{
 char input[301];

 /* check for command line argument of -d */
 DebugMode = FALSE;
 int i;
 for ( i = 0; i < argc; i++)
    if ( strcmp (argv[i], "-d") == 0)
       DebugMode = TRUE;

 /* set up an infinite loop */
 while (1)
 {
   /* get line of input from standard input */
   printf ("\nEnter input to check or q to quit\n");
   fgets(input, 300, stdin);

   /* remove the newline character from the input */
   int i = 0;
   while (input[i] != '\n' && input[i] != '\0')
   {
      i++;
   }
   input[i] = '\0';

   /* check if user enter q or Q to quit program */
   if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
     break;
 
   printf ("%s\n", input);

   /* run the algorithm to determine is input is balanced */
     struct my_stack* stack = init();
     int value = balancedBrackets(input,stack);
     if (value == 1){
         printf("The input is balanced.");
     }
     else if (value == 2){
         printf("The input is unbalanced because it is missing an opening symbol."); //Error 1
     }
     else if (value == 3){
         printf("The input is unbalanced because it it is expecting a different closing symbol."); //Error 2
     }
     else if (value == 4){
         printf("The input unbalanced because it is missing a closing symbol."); //Error 3
     }
     clearStack(stack);
 }

 printf ("\nGoodbye\n");
 return 0;
}

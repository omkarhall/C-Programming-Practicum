/*
 * file: rsort.c
 * description:
 *   implementation of the radix sort algorithm
 *
 *   usage:  ./rsort -i <input-file> -o <output-file> [-l <log-file>] [-r <radix>]
 *
 *          The "-i <input-file>" and "-o <output-file>" command-line
 *          arguments are required and may appear in any order.
 *
 *          The "[-l <log-file>] is optional (square brackets used to
 *          indicate that it is an option).
 *
 *          The "[-r <radix>] is also optional. It allows the user to specify the
 *          radix to be used (overriding the default radix of N where N is the number
 *          of elements being sorted).
 *
 *   Details:
 *
 *      input and output file formats:  simply a sequence of white-space separated
 *      unsigned integers.  No commas or anything like that (which would be considered
 *      a format error).
 *
 *      The -l flag:  when a log-file is specified on the command-line, the program
 *      runs in "verbose mode" and records the following information in the specified
 *      log file:
 *
 *              During a "pass", every element is assigned to a target "bucket".
 *
 *              For every such assignment during the run of the program, a line summarizing
 *              the operation is appended to the log file.  These lines are formatted
 *              as
 *
 *                p <pass-number> v <value-being-sorted> b <target-bucket-index>
 *
 *              Examples:
 *
 *                suppose we are processing an element 10294 during pass 0.  The
 *                resulting line in the output file would be the following:
 *
 *                  p 0 v 10294 b 4
 *
 *                for the same value, but during pass 2, the resulting line is:
 *
 *                  p 2 v 10294 b 2
 *
 *      IMPORTANT NOTE:  passes start with pass 0 (not 1).
 *
 *      If the -l flag is not given, the program simply saves the sorted data in the
 *      given output file (all logging is disabled).
 *
 *  ERROR CONDITIONS:
 *
 *      With respect to input and output files:
 *
 *          o if neither or both filenames are not given, the program reports the
 *            error and terminates.  NOTE:  the -i and -o flags are REQUIRED.
 *
 *          o if an input, output or log file cannot be opened in the correct mode,
 *            the program reports the error and terminates.  NOTE that the input file
 *            must be opened for reading and the output and log files for writing.
 *
 *
 *  READING INPUT:
 *
 *      The program reads non-negative integers from the input file until it reaches
 *      EOF or an attempt to read an unsigned int fails (e.g., there is a “token”
 *      in the input that cannot be parsed as a non-negative integer).  In the
 *      latter case, the program itself does NOT “fail”; it simply sorts the
 *      values it did successfully read and writes the sorted sequence to the
 *      given output file.
 *
 *  EXAMPLES OF CORRECT USAGE:
 *
 *       ./rsort -i data.txt -o data_sorted.txt
 *
 *       ./rsort -o data_sorted.txt -i data.txt -r 16
 *
 *       ./rsort -o data_sorted.txt -i data.txt -l data_log.txt
 *
 *       ./rsort -r 2 -o data_sorted.txt -i data.txt -l data_log.txt
 *
 *  EXAMPLE OF INCORRECT USAGE:
 *
 *       ./rsort data.txt data_sorted.txt
 *
 *                  (must use -i and -o flags)
 *
 *  TIPS:
 *
 *    library functions for opening, reading from, writing to and closing
 *    files:
 *
 *       fopen: takes a filename (as a C string) and a "mode" (also as a
 *         C string which specifies the permissions being
 *         requested ("r" for read permission; "w" for write permission).
 *         If file is successfully opened, a pointer (FILE *) is returned.
 *
 *         man page:  https://man7.org/linux/man-pages/man3/fopen.3.html
 *
 *       fclose: if you open a file, you MUST close it eventually!
 *
 *         man page:  https://man7.org/linux/man-pages/man3/fclose.3.html
 *
 *       fscanf:  this is handy!  behaves like scanf, but requires a FILE
 *         pointer be explicitly specified.
 *
 *         NOTE:  the format specifier for an unsigned integer is %u
 *
 *         man page:  https://man7.org/linux/man-pages/man3/fscanf.3p.html
 *
 *       fprintf:  similarly, fprintf behaves like printf, but takes a
 *         FILE pointer specifying where the output goes.
 *
 *         man page:  https://man7.org/linux/man-pages/man3/fprintf.3p.html
 */


#include "q.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int logMode = 0; // 1 if logging is enabled, 0 otherwise
FILE *flog = NULL; // logging file

/*
 * Helper function to calculate exponents
 */
int power(int x, int y){
    int power = 1;
    for (int i = 1; i <= y; i++){
        power = power*x;
    }
    return power;
}
/*
 * Helper function that finds number of digits in largest element
 * Input: largest element (unsigned int), radix (int)
 * Output: number of digits in largest element (int)
 */
int maxDigits(unsigned int n, int radix){
    int i = 1;
    if (n < radix){
        return 1;
    }
    while (n > (unsigned int)power(radix,i)){
        i++;
    }
    return i;
}


/*
 * Function that performs radix sort
 * Input: array containing numbers to be sorted (int*)
 *        size of array (int)
 *        radix used for sort (int)
 *        File *fwrite - output file
 */
void radixSort(unsigned int input[], int size, int radix, FILE *fwrite){
    
    unsigned int maxValue = input[0];
    for (int i = 0; i < size; i++){
        if (input[i] > maxValue){
            maxValue = input[i];
        }
    }
    int max_digits = maxDigits(maxValue, radix);
    //allocate number of buckets based on radix
    QUEUE ** array = malloc(radix*sizeof(QUEUE*));
    for (int i = 0; i < radix; i++){
        array[i] = q_create();
    }
    
    for (int i = 0; i < max_digits; i++) {
        for (int j = 0; j < size; j++) {
            int bucket = (input[j] / (int)power(radix, i)) % radix; //index of bucket
            q_enqueue(array[bucket], input[j]); //add value to proper bucket
            if (flog != NULL && logMode == 1){
                fprintf(flog, "p %d v %u b %d\n",i, input[j], bucket);
            }
        }
        int x = 0, y = 0;
        // write back to input after each pass
        while (x < radix) {
            while (q_is_empty(array[x]) == 0){
                unsigned int val;
                unsigned int *pval = &val;
                q_dequeue(array[x], pval);
                input[y++] = *pval;
            }
            x++;
        }
    }
    //write to output file
    for (int i = 0; i < size; i++){
        fprintf(fwrite, "%u ", input[i]);
        printf("%u ", input[i]);
    }
    //free buckets used for sort
    for (int i = 0; i < radix; i++){
        q_destroy(array[i]);
    }
    free(array);
}

int main(int argc, char *argv[]) {
    
    int argI = 0; //count for -i flag
    int argO = 0; //count for -o flag
    int input = -1; //index of input file
    int output = -1; //index of output file
    int log = -1; //index of log file
    int radix = -1; //value of radix number
    logMode = 0;
    FILE *fread = NULL;
    FILE *fwrite = NULL;
    //checks which command line arguments are present
    for (int i = 0; i < argc; i++){
        if (strcmp (argv[i], "-o") == 0){
            argO++;
            output = i+1;
        }
        if (strcmp (argv[i], "-i") == 0){
            argI++;
            input = i+1;
        }
        if (strcmp (argv[i], "-l") == 0){
            log = i+1;
            logMode = 1; //-l flag is present
        }
        if (strcmp (argv[i], "-r") == 0){
            radix = atoi(argv[i+1]);
        }
    }
    //check if -i and -o flags are present
    if (argI == 0 || argO == 0){
        printf("Error. '-i' and '-o' flags required.\n");
        return 0; //terminate
    }
    //check if input/output files open
    if (input != -1 && output != -1) {
        fread = fopen(argv[input], "r");
        fwrite = fopen(argv[output], "w");
        if (fread == NULL || fwrite == NULL) {
            printf("Error. Could not open I/O files.\n");
            return 0; //terminate
        }
    }
    //check if log file opens
    if (logMode == 1){
        flog = fopen(argv[log], "w");
        if (flog == NULL){
            printf("Error. Could not open log file.\n");
            return 0; //terminate
        }
    }
    
    unsigned int val;
    int n = 0; //number of unsigned ints in file
    //count number of unsigned ints in the file
    while (fscanf(fread, "%u", &val) == 1 && !feof(fread)) {
        n++;
    }
    //empty file
    if (n == 0){
        fclose(fread);
        fclose(fwrite);
        if (flog != NULL){
            fclose(flog);
        }
    }
    else{
        unsigned int array[n]; //array that contains elements to be sorted
        rewind(fread); //rewind file back to beginning
        for (int i = 0; i < n; i++){
            fscanf(fread, "%u", &array[i]);
        }
        if (radix == -1){
            radix = n; //-r flag is not present, radix is set to n as default
        }
        radixSort(array, n, radix, fwrite);
        fclose(fread);
        fclose(fwrite);
        //only close log file if -l flag is called, otherwise the log file is NULL
        if (flog != NULL){
            fclose(flog);
        }
    }
    return 0;
}

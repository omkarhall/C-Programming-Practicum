


/**
* File:  prog3.h
*
* Description:  contains function prototypes and
*         behavioral specifications of
*        the functions you are to implement
*        in prog3.c
*
* Note:  you should NOT modify this file!
*/


/***********************************************
*                                             **
*   MATRIX FUNCTIONS                          **
*                                             **
***********************************************/

/**
* Function:  alloc_square_mtx
* Description:  Dynamically allocates a square nxn 2D
*       matrix of characters.  The individual matrix
*       elements need not be initialized.
*
*       The matrix is returned as a char **
*
* Estimated Difficulty:  LEVEL-1
*/
char ** alloc_square_mtx(int n);

/**
* Function:  free_square_mtx
* Description:  deallocates all dyanamically allocated
*       components of a matrix previously produced by
*       alloc_square_mtx.
*
* Estimated Difficulty:  LEVEL-1
*/
void free_square_mtx(char **m, int n);

/**
* Function:  pop_mtx_alpha
* Description:  populates square matrix of characters
*        with random, lower-case letters a..z
*
*        TIP:  srand() and rand() might be handy
*
* Estimated Difficulty:  LEVEL-1
*/
void pop_mtx_alpha(char **m, int n);


/**
* Function:  display_mtx
* Description:  prints given square matrix row-by-row (printing
*        a newline after each row).
*
* Estimated Difficulty:  LEVEL-1
*
* TIPS:  putchar or the %c specifier in printf might be handy
*
* Comments:  don't overthink this; just print each char
*    one by one.  Don't worry about what those chars are.
*
*/
void display_mtx(char **m, int n);

/**
* Function:  swap_rows
* Description:  swaps the contents of rows r1 and r2 of
*               square matrix m.  Ordering of characters
*                within rows are preserved.
*
*               If r1 or r2 is out of range no modifications
*                are made.
*
* Estimated Difficulty:  LEVEL-2
*/
void swap_rows(char **m, int n, int r1, int r2);

/**
* Function:  swap_cols
* Description:  swaps the contents of column c1 and c2 of
*               square matrix m.  Ordering of characters
*                within rows are preserved.
*
*               If c1 or c2 is out of range no modifications
*                are made.
*
* Estimated Difficulty:  LEVEL-2
*/
void swap_cols(char **m, int n, int c1, int c2);



/**
* Function:  rotate_right
* Description:  "rotates" square matrix m 90 degrees right
*        (clockwise).
*
*        Example:  consider the 3x3 matrix below:
*
            abc
            def
            hij
*
*        After one rotation, the matrix contents are:
*
*            hda
*            ieb
*            jfc
*
* Estimated Difficulty:  LEVEL-3
*
*/
void rotate_right(char **m, int n);


/**
* Function:  floating_boulders
*
* Parameters:  m - the matrix to populate
*              nb - the number of boulders to place.
*
* Description:  popluates the given matrix with with the specified
*        number of  "boulders" randomly placed.
*        All other matrix entries are set to "air"
*
*        A boulder is represented by the character '#'
*        "Air" is represented by the character '.'
*
*        As long as the matrix is made up of nb boulders and
*        N*N-m air symbols, the result is valid.
*
*        If nb is negative, the result will be the same as
*        when nb==0 (all air)
*
*        If nb>N*N (too big), the result should be same as
*        when nb==N*N (all boulders)

* Estimated Difficulty:  LEVEL-1.5
*
* Examples:
*
*     possible configuration for 4x4 with nb==5

       .#..
       ....
       #.##
       ..#.

*     possible configuration for 4x4 with nb==10

       .#.#
       ###.
       #.##
       .##.
*
*/
void floating_boulders(char **m, int n, int nb);


/**
* Function:  mountains
* Description:  populates the given matrix with a random ASCII
*        "landscape"
*
*        - Air is represented by just periods '.'
*        - Land is represnted by pound-symbols '#' (boulders?)
*        - "Air" is always above "Land", so each column of
*           the image from bottom-to-top has some number of
*           Land symbols above which is just air.
*        - As long as these rules are followed, the matrix
*          is valid.
*
* Estimated Difficulty:  LEVEL 2
*
* Examples (6x6):
*
        ......
        ...#..
        ..##..
        #.##..
        ####.#
        ######

        #.....
        #.....
        #.....
        #..#..
        ##.#.#
        ##.#.#


  Notice that a column may be all "land" (no air); similarly, a column
  can be all air (no land).  This means that even the following are
  valid configurations (don't try to prevent them):

        ######
        ######
        ######
        ######
        ######
        ######

        ......
        ......
        ......
        ......
        ......
        ......

  These might be improbable, but the point is that you don't have
  to "prevent" them somehow.

*/
void mountains(char **m, int n);



/**
* Function:  sink
* Description:  "sinks" the given matrix/image by one layer and introduces
*               "air" as a new top layer.
*
*               Air is represented by the '.' character as in the mountains
*               function.
*
*               In other words:  the contents row 0 "sink" to row 1;
*               row 1 sinks to row 2 and so on.
*               Row N-1 "disappears"
*               Row 0 becomes "Air"
*
* Estimated Difficulty:  LEVEL 2.5
*
* Example:
*
    Before sink:

        ......
        ...#..
        ..##..
        #.##..
        ####.#
        ######

    After sink:

        ......
        ......
        ...#..
        ..##..
        #.##..
        ####.#
*
*  Note:  the example above is based on a result of the mountains
*         function, but the operation is still well-defined for any
*         matrix of characters.  For example, consider the 3x3
*      example below:

  Before sink:

       abc
       def
       hij

  After sink

       ...
       abc
       def

*/
void sink(char **m, int n);



/**
* Function:  gravity
* Description:  "compacts" the matrix/image downward according to the
*        following rules:
*
*        - The character '.' represents Air
*        - All other characters are assumed to be "heavier than air" --
*            i.e., they will fall when the force of gravity is
*            applied.
*            Let's call them "blocks"
*        - All blocks fall as far as possible as you might expect...
*
* Estimated Difficulty:  LEVEL 3
*
* Example

         Before Gravity:

            .^..8.
            .^##..
            #....#
            #.#@.$
            &###.#
            ..##*.

         After Gravity:
            ......
            ......
            ..##..
            #^#@.#
            #^##8$
            &###*#

*/
void gravity(char **m, int n);




/***********************************************
*                                             **
*   STRING FUNCTIONS                          **
*                                             **
***********************************************/


/**
* Function:  str_trim
*
* Description:  effectively removes all leading and trailing
*               whitespace from the given string s.
*
*        Examples:
*
*                    BEFORE        AFTER
*
*                 "  abc"                "abc"
*                 "  abc  "              "abc"
*                 "  hello there  "      "hello there"
*                 "       a   b   "      "a   b"
*
* Estimated Difficulty:  LEVEL 3
*
* NOTES/COMMENTS:
*
*    Notice that "internal" whitespace is not removed!
*       Modifications are made to the given string -- you are
*          not creating a new string.
*             Use the library function isspace to test if a character
*          is whitespace or not.  While the usual space character
*       ' ' is whitespace, it is not the only whitespace char;
*       the tab character '\t' for example is considered
*       whitespace.  Let the isspace function figure this out
*       for you.
*/
void str_trim(char *s);


/**
* FUNCTION:  str_search
*
* DESCRIPTION:  takes two C strings:  a "source string" s[] and
*               a "pattern string" and determines if the given
*               pattern is a substring of s.
*
*               If the pattern is a substring of s, the index into s where
*        the first match occurs is returned (note that the
*        pattern may occur multiple times in s).
*
*        Otherwise, -1 is returned (note that a match could
*        start at index 0, so we can't use 0 for "false").
*
* Estimated Difficulty:  LEVEL 3
*
*        Examples:
*
*                  source string s         pattern      return-value
*
*                  "abcd"                  "ab"             0
*                  "abcd"                  "aa"             -1
*                  "abc bc d"              "bc"             1
*                  "abcd"                  "bcd"            1
*                  "abcd"                  "bcd"            1
*                  "abracadabra"           "dab"            6
*                  "abc"                   "abc"            0
*                  "abc"                   "abcd"           -1
*
*   NOTES:
*        - every string is a substring of itself
*        - if the pattern is longer than the source string,
*           of course there can be no match.
*        - remember there may be multiple matches - you want
*           the index of the first match.
*
*   RULES:  You may use the strlen library function (but you don't
        really need it) but all other library functions
        operating on strings are off limits!
*/
int str_search(char *s, char *pattern);





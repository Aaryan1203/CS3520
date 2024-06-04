#include <stdio.h>

#define MAX_LETTERS 26

char alphabet[MAX_LETTERS];

void initialize_array(char *a) {
    char *p;
    char current_letter = 'a';

    // changes <= to <
    for (p = a; p < (a + MAX_LETTERS); p++) {
        *p = current_letter++;
    }
}

void print_characters_in_reverse(char *b) {
    char *p;

    // removed var variable as it was unecessary
    
    printf("\nReversing alphabets...\n");

    for (p = (b + MAX_LETTERS - 1); p >= b; p--) {
        printf("%c ", *p);
    }
    printf("\n");
}

int main(void) {
    // moved initialize array to the main function
    initialize_array(alphabet);

    // changed the for loop from 5 to 10
    for (int i = 1; i <= 10; i++) {
        print_characters_in_reverse(alphabet);
    }

    return 0;
}

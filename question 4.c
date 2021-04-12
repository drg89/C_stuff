#include <stdlib.h>
#include <stdio.h>

int
main(int argc, const char * argv[]){
    int c, characters, lines;
    characters = lines = 0; 
    printf("enter text: ");
    while ((c = getchar()) != EOF) {
        
        if (c == '\n') {
            lines++;
        }
        else {
            characters++;
        }
    }
    printf("Lines: %d\nCharacters: %d",lines,characters);
    return 0;
}
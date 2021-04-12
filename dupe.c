#include <string.h>
#include <stdio.h>

char *string_dupe(char *s){
    char *ptr = (char*)malloc(strlen(s));
    strcpy(ptr, s);
    return ptr;
}

int
main(int argc, char *argv[]) {
    char s[] = "hello world";
    printf("%s", string_dupe(s));
	return 0;
}
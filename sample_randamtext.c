#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void rand_text(int length, char *result) {
    int i, rand_int;
    char char_set[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (i = 0; i < length; i++) {
        result[i] = char_set[rand() % (sizeof(char_set) - 1)];
    }
    result[length] = 0;
}

int main(void){
    int length = 10;
    char result[length + 1];
    srand(time(NULL));

    rand_text(length, result);
    printf("%s\n", result);
}

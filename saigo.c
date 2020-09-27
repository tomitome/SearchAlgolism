#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include <string.h>

# define NO_OF_CHARS 256

int max (int a, int b){
    return (a > b)? a: b;
}

void SIMPLE(char *pattern, char *text){
    int M = strlen(pattern);
    int N = strlen(text);
    int j = 0;
    int flag = 0;
    int i = 0;
    while (i <= N-M){
        while(j < M && text[i+j] == pattern[j])j++;
        if (j == M){
        flag = 1;
        printf("%d番目からpatternが出現しています。\n", i);
        }
        i = i + 1;
        j = 0;
    }
    if(flag == 0)printf("文字列は見つかりませんでした。\n");
}

void badCharHeuristic( char *str, int size, int badchar[NO_OF_CHARS]){
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)badchar[i] = -1;
    for (i = 0; i < size; i++)badchar[(int) str[i]] = i;
}

void BM(char *pattern,char *text){
    int m = strlen(pattern);
    int n = strlen(text);
    int flag = 0;
    int badchar[NO_OF_CHARS];
    badCharHeuristic(pattern, m, badchar);
    int i = 0;
    while(i <= (n - m))
    {
        int j = m-1;
        while(j >= 0 && pattern[j] == text[i+j]){
        j--;
        }
        if (j < 0){
            flag = 1;
            printf("%d番目からpatternが出現しています。\n", i);
            i += (i+m < n)? m-badchar[text[i+m]] : 1;
        }
        else{
            i += max(1, j - badchar[text[i+j]]);
        }
    }
    if(flag == 0)printf("文字列は見つかりませんでした。\n");
}

void calcSKIP(char *pattern, int M, int *skip){
    int len = 0;
    int i;
    skip[0] = 0;
    i = 1;
    while (i < M){
        if (pattern[i] == pattern[len]){
            len++;
            skip[i] = len;
            i++;
        }
        else{
            if( len != 0 ){
                len = skip[len-1];
            }
            else{
                skip[i] = 0;
                i++;
            }
        }
    }
}

void KMP(char *pattern, char *text){
    int M = strlen(pattern);
    int N = strlen(text);
    int *skip = (int *)malloc(sizeof(int)*M);
    int j = 0;
    int flag = 0;
    calcSKIP(pattern, M, skip);
    int i = 0;
    while (i < N){
        if (text[i] == pattern[j]){
            i++;
            j++;
        }
        if (j == M){
            flag = 1;
            printf("%d番目からpatternが出現しています。\n", i-j);
            j = skip[j-1];
        }
        else if(text[i] != pattern[j]){
            if(j != 0){
            j = skip[j-1];
            }
            else{
            i = i+1;
            }
        }
    }
    if(flag == 0){
    printf("文字列は見つかりませんでした。\n");
    }
    free(skip);
}

void rand_text(int length, char *text) {
    int i;
    //char char_set[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char char_set[] = "ABCD";
    for (i = 0; i < length; i++) {
        text[i] = char_set[rand() % (sizeof(char_set) - 1)];
    }
    text[length] = 0;
}

int main(void){
    struct timeval s,e;
    int length = 1000;
    char *pattern = "ABDDA";
    char text[length + 1];
    srand(time(NULL));
    rand_text(length, text);
    printf("%s\n", text);

    printf("\n普通\n");
    gettimeofday(&s,NULL);
    SIMPLE(pattern, text);
    gettimeofday(&e,NULL);
    printf("%lf\n",(e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);

    printf("\nKMP\n");
    gettimeofday(&s,NULL);
    KMP(pattern, text);
    gettimeofday(&e,NULL);
    printf("%lf\n",(e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);

    printf("\nBm\n");
    gettimeofday(&s,NULL);
    BM(pattern, text);
    gettimeofday(&e,NULL);
    printf("%lf\n",(e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);

    return 0;
}
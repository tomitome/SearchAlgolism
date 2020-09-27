/* 原始的な方法による文字列検索用プログラム */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void SIMPLE(char *pattern, char *text);

void SIMPLE(char *pattern, char *text)
{
    int M = strlen(pattern);
    int N = strlen(text);

    int j = 0;  // patternの検索開始位置を初期化
    int k = 0;
    int flag = 0;

    int i = 0;  // textの照合開始位置の初期化
    while (i <= N-M)
    {
      // printf("照合位置：%d, 検索位置：%d\n", i, i+j);
      while(j < M && text[i+j] == pattern[j])
      {
        j++;
      }
      // j=Mなら一致する文字列があるので、その位置を返す
      if (j == M)
      {
        flag = 1;
        printf("%d番目からpatternが出現しています。\n", i);
      }
      i = i + 1;
      j = 0;
      // textの要素とpatternの要素が一致しなかった
    }
    if(flag == 0)
    {
      printf("文字列は見つかりませんでした。\n");
    }
}

int main()
{
   char *text = "ABABDABACDABABCABAB";
   char *pattern = "ABAB";
   SIMPLE(pattern, text);
   return 0;
}

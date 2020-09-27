/* KMPアルゴリズムの習作 */
// 参考：https://riptutorial.com/algorithm/example/23880/kmp-algorithm-in-c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void calcSKIP(char *pattern, int M, int *skip);
void KMP(char *pattern, char *text);

void KMP(char *pattern, char *text)
{
    int M = strlen(pattern);
    int N = strlen(text);

    // SKIP表用の配列作成
    int *skip = (int *)malloc(sizeof(int)*M);
    int j = 0;  // patternの検索開始位置を初期化
    int k = 0;
    int flag = 0;
    // 検索文字列に対するSKIP表用の作成
    calcSKIP(pattern, M, skip);
    // for(k=0;k<M;k++){
    //   printf("SKIP配列： ");
    //   printf("%d ", skip[k]);
    //   printf("\n");
    // }
    int i = 0;  // textの照合開始位置の初期化
    while (i < N)
    {
      // printf("照合位置：%d, 検索位置：%d\n", i, i+j);
      if (text[i] == pattern[j])
      {
        i++;
        j++;
      }
      // j=Mなら一致する文字列があるので、その位置を返す
      if (j == M)
      {
        flag = 1;
        printf("%d番目からpatternが出現しています。\n", i-j);
        j = skip[j-1];
      }
      else if(text[i] != pattern[j])
      {
        if(j != 0)
        {
          j = skip[j-1];
        }
        else
        {
          i = i+1;
        }
      }
      // textの要素とpatternの要素が一致しなかった
    }
    if(flag == 0)
    {
      printf("文字列は見つかりませんでした。\n");
    }
    free(skip); // to avoid memory leak
}

void calcSKIP(char *pattern, int M, int *skip)
{
    int len = 0;
    int i;

    skip[0] = 0; // skipの先頭は必ず0
    i = 1;

    // skipの先頭から末尾まで繰り返す
    while (i < M)
    {
       if (pattern[i] == pattern[len])
       {
         len++;
         skip[i] = len;
         i++;
       }
       else // (pattern[i] != pattern[len])
       {
       if( len != 0 )
       {
         len = skip[len-1];
       }
       else
       {
         skip[i] = 0;
         i++;
       }
       }
    }
}

int main()
{
   char *text = "ABABDABACDABABCABAB";
   char *pattern = "ABAB";
   KMP(pattern, text);
   return 0;
}

/* BMアルゴリズムの習作 */
// 参考URL: https://www.wikitechy.com/technology/c-programming-for-pattern-searching-set-7-boyer-moore-algorithm-bad-character-heuristic-2/
# include <limits.h>
# include <string.h>
# include <stdio.h>

# define NO_OF_CHARS 256

void badCharHeuristic( char *str, int size, int badchar[NO_OF_CHARS]);
void BM( char *text,  char *pattern);
// A utility function to get maximum of two integers
int max (int a, int b) { return (a > b)? a: b; }

// The preprocessing function for Boyer Moore's bad character heuristic
void badCharHeuristic( char *str, int size, int badchar[NO_OF_CHARS])
{
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)badchar[i] = -1;
    for (i = 0; i < size; i++)badchar[(int) str[i]] = i;
}

void BM( char *text,  char *pattern)
{
    int m = strlen(pattern);
    int n = strlen(text);
    int flag = 0;
    int s;

    int badchar[NO_OF_CHARS];

    badCharHeuristic(pattern, m, badchar);

    int i = 0;  // 照合位置の初期化
    while(i <= (n - m))
    {
        int j = m-1;

        /* pattern末尾から先頭に向かって比較を開始 */
        while(j >= 0 && pattern[j] == text[i+j])
        {
        j--;
        }

        /* もしpatternが現在の照合開始位置に存在するならば、jには-1が代入されている */
        if (j < 0)
        {
            flag = 1;
            printf("%d番目からpatternが出現しています。\n", i);

            /* 照合開始位置が右ではなく左にずれるようであれば
            強制的に右に一つずらすために設定された関数である。. */
            s += (s+m < n)? m-badchar[text[s+m]] : 1;

        }

        else
            /* ここでのmax関数は照合開始位置が右ではなく
            左にずれるようであれば強制的に右に一つずらすために
            設定された関数である。. */
            s += max(1, j - badchar[text[s+j]]);
    }
    if(flag == 0)
    {
      printf("文字列は見つかりませんでした。\n");
    }
    return;
}

/* Driver program to test above funtion */
int main()
{
    char *text = "ABABDABACDABABCABAB";
    char *pattern = "ABAB";
    BM(text, pattern);
    return 0;
}

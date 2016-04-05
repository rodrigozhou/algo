/**
 * Longest Common Subsequence
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;

char a[MAXN], b[MAXN];
int lena, lenb, t[MAXN][MAXN];

void lcs() {
    for (int i = 0; i <= lena; i++)
        t[i][0] = 0;
    for (int i = 0; i <= lenb; i++)
        t[0][i] = 0;
    for (int i = 1; i <= lena; i++) {
        for (int j = 1; j <= lenb; j++) {
            if (a[i] == b[j]) {
                t[i][j] = t[i-1][j-1] + 1;
            }
            else {
                t[i][j] = max(t[i-1][j], t[i][j-1]);
            }
        }
    }
}

void print_lcs(int i, int j) {
    if (i == 0 || j == 0)
        return;
    if (a[i] == b[j]) {
        print_lcs(i-1, j-1);
        printf("%c", a[i]);
    }
    else if (t[i-1][j] > t[i][j-1]) {
        print_lcs(i-1, j);
    }
    else {
        print_lcs(i, j-1);
    }
}

int main() {
    a[0] = b[0] = '\0';
    scanf("%s %s", a+1, b+1);
    lena = strlen(a+1);
    lenb = strlen(b+1);
    lcs();
    printf("Length: %d\n", t[lena][lenb]);
    print_lcs(lena, lenb);
    printf("\n");
}

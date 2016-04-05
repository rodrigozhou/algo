/**
 * Longest Common Substring
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;

char a[MAXN], b[MAXN];
int lena, lenb, lenlcs, t[MAXN][MAXN];

void lcs() {
    lenlcs = 0;
    for (int i = 0; i <= lena; i++)
        t[i][0] = 0;
    for (int i = 0; i <= lenb; i++)
        t[0][i] = 0;
    for (int i = 1; i <= lena; i++) {
        for (int j = 1; j <= lenb; j++) {
            if (a[i] == b[j]) {
                t[i][j] = t[i-1][j-1] + 1;
                lenlcs = max(lenlcs, t[i][j]);
            }
            else {
                t[i][j] = 0;
            }
        }
    }
}

void print_lcs(int i, int j) {
    if (t[i][j] != 0) {
        print_lcs(i-1, j-1);
        printf("%c", a[i]);
    }
}

void find_lcs() {
    for (int i = lena; i >= lenlcs; i--) {
        for (int j = lenb; j >= lenlcs; j--) {
            if (t[i][j] == lenlcs) {
                print_lcs(i, j);
                printf("\n");
            }
        }
    }
}

int main() {
    a[0] = b[0] = '\0';
    scanf("%s %s", a+1, b+1);
    lena = strlen(a+1);
    lenb = strlen(b+1);
    lcs();
    printf("Length: %d\n", lenlcs);
    find_lcs();
}

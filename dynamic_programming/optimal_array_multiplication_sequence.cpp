#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 1010
const int INF = 1<<30;

int n, m[MAXN], c[MAXN][MAXN];

void oams() {
    for (int i = 1; i <= n; i++)
        c[i][i] = 0;

    for (int d = 1; d < n; d++) {
        for (int i = 1; i <= n-d; i++) {
            int j = i+d;
            c[i][j] = INF;
            for (int k = i; k < j; k++)
                c[i][j] = min(c[i][j], c[i][k] + c[k+1][j] + m[i-1]*m[k]*m[j]);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++)
        scanf("%d", &m[i]);

    oams();
    printf("%d\n", c[1][n]);
}

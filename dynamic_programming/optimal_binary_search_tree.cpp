#include <cstdio>
using namespace std;

#define MAXN 1010
const int INF = 1<<30;

int n, p[MAXN];
int c[MAXN][MAXN], f[MAXN][MAXN], r[MAXN][MAXN];

void obst() {
    for (int i = 1; i <= n; i++)
        c[i][i-1] = 0;
    c[n+1][n] = 0;

    for (int i = 1; i <= n; i++) {
        c[i][i] = p[i];
        f[i][i] = p[i];
        r[i][i] = i;
    }

    for (int d = 1; d < n; d++) {
        for (int i = 1; i <= n-d; i++) {
            int j = i+d;
            c[i][j] = INF;
            f[i][j] = f[i][j-1] + p[j];
            int rmin = r[i][j-1], rmax = r[i+1][j];
            for (int k = rmin; k <= rmax; k++) {
                int t = c[i][k-1] + c[k+1][j];
                if (t < c[i][j]) {
                    c[i][j] = t;
                    r[i][j] = k;
                }
            }
            c[i][j] += f[i][j];
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &p[i]);

    obst();
    printf("%d\n", c[1][n]);
}

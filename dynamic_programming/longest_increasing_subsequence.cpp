/**
 * Longest Increasing Subsequence
 */

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int n, m, a[MAXN], b[MAXN], p[MAXN];

void lis() {
    int u, v;
    b[m++] = 0;
    for (int i = 1; i < n; i++) {
        if (a[b[m-1]] < a[i]) {
            p[i] = b[m-1];
            b[m++] = i;
            continue;
        }
        for (u = 0, v = m-1; u < v; ) {
            int c = (u + v)/2;
            if (a[b[c]] < a[i])
                u = c + 1;
            else
                v = c;
        }
        if (a[i] < a[b[u]]) {
            if (u > 0)
                p[i] = b[u-1];
            b[u] = i;
        }
    }
    for (u = m, v = b[m-1]; u--; v = p[v]) {
        b[u] = v;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    m = 0;
    lis();
    for (int i = 0; i < m; i++) {
        printf("%d ", a[b[i]]);
    }
    printf("\n");
}

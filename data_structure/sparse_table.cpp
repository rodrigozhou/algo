/**
 * Sparse Table
 */

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX 100005
#define LOGMAX 20

int n, v[MAX];
int tb[LOGMAX][MAX];

void init() {
    for (int i = 0; i < n; i++)
        tb[0][i] = v[i];
    for (int k = 1; (1 << k) < n; k++)
        for (int i = 0; i + (1 << k) <= n; i++)
            tb[k][i] = max(tb[k-1][i], tb[k-1][i + (1 << (k-1))]);
}

/**
 * query interval [a, b)
 */
int query(int a, int b) {
    int k = 31 - __builtin_clz(b - a);
    return max(tb[k][a], tb[k][b - (1 << k)]);
}

int main() {
}

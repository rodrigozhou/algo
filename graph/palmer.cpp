/**
 * Palmer's algorithm
 *
 * Description: find a Hamiltonian cycle in a graph satisfying Ore's theorem
 * Complexity: O(n^2)
 *
 * Ore's theorem
 * Let G = (V, E) be a graph with n >= 3.
 * If deg(u) + deg(v) >= n for every pair (u, v) not in E,
 * then G is Hamiltonian.
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 256

int n, m;
int g[MAXN][MAXN];
int cycle[MAXN];

void palmer() {
    for (int i = 0; i < n; i++)
        cycle[i] = i;
    cycle[n] = cycle[0];
    for (int i = 0; i < n; i++) if (!g[cycle[i]][cycle[i+1]])
        for (int j = 0; j < n; j++) if (j < i-1 || j > i+1)
            if (g[cycle[i]][cycle[j]] && g[cycle[i+1]][cycle[j+1]])
                reverse(cycle + min(i+1, j+1), cycle + max(i+1, j+1));
}

int main() {
    int u, v;
    scanf("%d %d", &n, &m);
    memset(g, 0, sizeof(g));
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        g[u][v] = g[v][u] = 1;
    }
    palmer();
    for (int i = 0; i <= n; i++)
        printf(" %d", cycle[i]);
    puts("");
}

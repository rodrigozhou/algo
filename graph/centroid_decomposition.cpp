/**
 * Centroid Decomposition
 *
 * Problems: CF/342E, SPOJ/QTREE5
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 100005

int n;
vector<int> g[MAX];
int subsize[MAX], cpar[MAX];

void dfs(int u, int p) {
    subsize[u] = 1;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v != p && cpar[v] == -1) {
            dfs(v, u);
            subsize[u] += subsize[v];
        }
    }
}

int find_centroid(int u, int p, int sz) {
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v != p && cpar[v] == -1 && 2 * subsize[v] > sz)
            return find_centroid(v, u, sz);
    }
    return u;
}

void decompose(int u, int cp) {
    dfs(u, u);
    int c = find_centroid(u, u, subsize[u]);
    cpar[c] = cp;
    for (int i = 0; i < g[c].size(); i++)
        if (cpar[g[c][i]] == -1)
            decompose(g[c][i], c);
}

void init() {
    memset(cpar, -1, sizeof(cpar));
    decompose(0, -2);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    init();
}

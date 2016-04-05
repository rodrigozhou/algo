#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 50000
#define LOGMAXN 16

typedef pair<int, int> pii;

int n, m, u, v, w;
int ancestor[MAXN][LOGMAXN], parent[MAXN], level[MAXN], dist[MAXN];
vector<pii> g[MAXN];

void dfs(int u) {
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].first, w = g[u][i].second;
        if (v != parent[u]) {
            parent[v] = u;
            level[v] = level[u] + 1;
            dist[v] = dist[u] + w;
            dfs(v);
        }
    }
}

void pre() {
    for (int i = 0; i < n; i++)
        ancestor[i][0] = parent[i];
    for (int j = 1; 1<<j < n; j++)
        for (int i = 0; i < n; i++)
            ancestor[i][j] = ancestor[ancestor[i][j-1]][j-1];
}

int lca(int u, int v) {
    if (level[u] < level[v])
        swap(u, v);

    int log;
    for (log = 1; 1<<log <= level[u]; log++);
    log--;

    for (int i = log; i >= 0; i--)
        if (level[u] - (1<<i) >= level[v])
            u = ancestor[u][i];

    if (u == v)
        return u;

    for (int i = log; i >= 0; i--)
        if (ancestor[u][i] != ancestor[v][i])
            u = ancestor[u][i], v = ancestor[v][i];

    return parent[u];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));
    }

    parent[0] = 0;
    level[0] = 0;
    dist[0] = 0;
    dfs(0);
    pre();

    scanf("%d", &m);
    while (m--) {
        scanf("%d %d", &u, &v);
        printf("%d\n", dist[u] + dist[v] - (dist[lca(u, v)]<<1));
    }
}

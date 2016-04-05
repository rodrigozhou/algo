#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 1001

int n, m;
vector<int> g[MAXN];
int lbl[MAXN], low[MAXN], parent[MAXN], idx;
bool art[MAXN], has_art;

void dfs(int u) {
    int cnt = 0;
    lbl[u] = low[u] = idx++;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (lbl[v] == -1) {
            parent[v] = u;
            dfs(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= lbl[u])
                cnt++;
        } else if (v != parent[u]) {
            low[u] = min(low[u], lbl[v]);
        }
    }

    if (cnt > 1 || (lbl[u] != 0 && cnt > 0)) {
        art[u] = 1;
        has_art = 1;
    }
}

void articulation() {
    for (int i = 1; i <= n; i++) {
        lbl[i] = -1;
        art[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        if (lbl[i] == -1) {
            idx = 0;
            parent[i] = i;
            dfs(i);
        }
    }
}

int main() {
    int u, v;
    scanf("%d %d", &n, &m);
    while (m--) {
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    has_art = 0;
    articulation();
    if (has_art) {
        for (int i = 1; i <= n; i++) {
            if (art[i]) {
                printf("%d ", i);
            }
        }
        putchar('\n');
    } else {
        printf("no articulations\n");
    }
}

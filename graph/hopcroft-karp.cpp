/**
 * Hopcroft-Karp Algorithm
 *
 * Complexity: O(E sqrt(V))
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF  0x3f3f3f3f
#define MAXN 1001
#define MAXM 1001

int n, m;
vector<int> g1[MAXN];
int pair_g1[MAXN], pair_g2[MAXM], dist[MAXN];

bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
        dist[u] = INF;
        if (pair_g1[u] == 0) {
            dist[u] = 0;
            q.push(u);
        }
    }

    dist[0] = INF;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < g1[u].size(); i++) {
            int v = g1[u][i];
            if (dist[pair_g2[v]] == INF) {
                dist[pair_g2[v]] = dist[u] + 1;
                q.push(pair_g2[v]);
            }
        }
    }
    return dist[0] != INF;
}

bool dfs(int u) {
    if (u == 0)
        return 1;
    for (int i = 0; i < g1[u].size(); i++) {
        int v = g1[u][i];
        if (dist[pair_g2[v]] == dist[u] + 1 && dfs(pair_g2[v])) {
            pair_g1[u] = v;
            pair_g2[v] = u;
            return 1;
        }
    }
    dist[u] = INF;
    return 0;
}

int hk() {
    memset(pair_g1, 0, sizeof(pair_g1));
    memset(pair_g2, 0, sizeof(pair_g2));

    int matching = 0;
    while (bfs())
        for (int u = 1; u <= n; u++)
            if (pair_g1[u] == 0 && dfs(u))
                matching++;
    return matching;
}

int main() {
    int p, a, b;
    scanf("%d %d %d", &n, &m, &p);
    while (p--) {
        scanf("%d %d", &a, &b);
        g1[a].push_back(b);
    }
    printf("%d\n", hk());
}

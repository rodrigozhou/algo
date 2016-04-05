/**
 * Edmonds-Karp Max Flow Algorithm
 *
 * Complexity: O(V E^2)
 */

#include <cstdio>
#include <queue>
using namespace std;

#define INF  0x3f3f3f3f
#define MAXN 1010

int n, m, g[MAXN][MAXN];
int parent[MAXN];
bool visited[MAXN];

bool bfs(int s, int t) {
    queue<int> q;
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    visited[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (g[u][v] && !visited[v]) {
                parent[v] = u;
                if (v == t)
                    return 1;
                q.push(v);
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        int f = INF;
        for (int v = t, u = parent[v]; v != s; v = u, u = parent[v])
            f = min(f, g[u][v]);
        for (int v = t, u = parent[v]; v != s; v = u, u = parent[v]) {
            g[u][v] -= f;
            g[v][u] += f;
        }
        flow += f;
    }
    return flow;
}

int main() {
    int s, t;
    int u, v, w;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g[i][j] = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        g[u][v] = w;
    }
    printf("%d\n", maxflow(s, t));
}

/**
 * Bellman-Ford Algorithm
 *
 * Complexity: O(VE)
 */

#include <cstdio>
using namespace std;

#define INF  0x3f3f3f3f

#define MAXN 20005
#define MAXM 1000000

struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

int n, m;
Edge e[MAXM];
int dist[MAXN], parent[MAXN];

int bellman_ford(int s) {
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    dist[s] = 0;
    parent[s] = s;
    int flag = 1;
    for (int i = 0; flag && i < n; i++) {
        flag = 0;
        for (int j = 0; j < m; j++)
            if (dist[e[j].u] + e[j].w < dist[e[j].v]) {
                dist[e[j].v] = dist[e[j].u] + e[j].w;
                parent[e[j].v] = e[j].u;
                flag = 1;
            }
    }
    return flag;
}

int main() {
    int s, u, v, w;
    scanf("%d %d %d", &n, &m, &s);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        e[i] = Edge(u, v, w);
    }
    if (bellman_ford(s))
        puts("negative cycle");
}

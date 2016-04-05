/**
 * Johnson Algorithm
 *
 * Complexity: O(VE + VE log V)
 */

#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

#define INF  0x3f3f3f3f
#define MAXN 20005
#define MAXM 1000000

struct Edge {
    int u, v, w;
    Edge () {}
    Edge (int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator< (const Edge &o) const {
        return w != o.w ? w < o.w : v < o.v;
    }
};

int n, m;
Edge e[MAXM];
vector<Edge> g[MAXN];
int d[MAXN][MAXN];
bool visited[MAXN];

int bellman_ford(int s, int *d) {
    for (int i = 1; i <= n; i++)
        d[i] = 0;
    d[s] = 0;
    int flag = 1;
    for (int i = 0; flag && i < n; i++) {
        flag = 0;
        for (int j = 0; j < m; j++) {
            if (d[e[j].u] + e[j].w < d[e[j].v]) {
                d[e[j].v] = d[e[j].u] + e[j].w;
                flag = 1;
            }
        }
    }
    return flag;
}

void dijkstra(int s, int *d) {
    set<Edge> pq;
    vector<Edge>::iterator it;
    for (int i = 1; i <= n; i++) {
        d[i] = INF;
        visited[i] = 0;
    }
    d[s] = 0;
    pq.insert(Edge(s, s, 0));
    while (!pq.empty()) {
        Edge e = *pq.begin();
        pq.erase(pq.begin());
        if (visited[e.v])
            continue;
        visited[e.v] = 1;
        for (it = g[e.v].begin(); it != g[e.v].end(); it++)
            if (!visited[it->v] && e.w + it->w < d[it->v])
                pq.insert(Edge(it->u, it->v, d[it->v] = e.w + it->w));
    }
}

int johnson() {
    if (bellman_ford(0, d[0]))
        return 1;
    for (int i = 0; i < m; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        g[u].push_back(Edge(u, v, w + d[0][u] - d[0][v]));
    }
    for (int i = 1; i <= n; i++)
        dijkstra(i, d[i]);
    return 0;
}

int main() {
    int u, v, w;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        e[i] = Edge(u, v, w);
    }
    if (johnson())
        puts("negative cycle");
}

#include <cstdio>
#include <vector>
#include <set>
using namespace std;

#define INF  0x3f3f3f3f
#define MAXN 1001

struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator< (const Edge &o) const {
        return w != o.w ? w < o.w : v < o.v;
    }
};

int n, m, dist[MAXN];
vector<Edge> g[MAXN];

void dijkstra(int u) {
    bool chosen[MAXN];
    set<Edge> s;
    for (int i = 1; i <= n; i++) {
        chosen[i] = 0;
        dist[i] = INF;
    }
    dist[u] = 0;
    s.insert(Edge(u, u, 0));
    while (!s.empty()) {
        int u = s.begin()->v;
        s.erase(s.begin());
        if (chosen[u]) continue;
        chosen[u] = 1;
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].v, w = dist[u] + g[u][i].w;
            if (w < dist[v]) {
                dist[v] = w;
                s.insert(Edge(u, v, w));
            }
        }
    }
}

int main() {
    int u, v, w;
    scanf("%d %d", &n, &m);

    while (m--) {
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back(Edge(u, v, w));
        g[v].push_back(Edge(v, u, w));
    }

    dijkstra(1);
    printf("%d\n", dist[n]);
}

#include <cstdio>
#include <vector>
#include <set>
using namespace std;

#define MAXN 1001

struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator< (const Edge &o) const {
        return w != o.w ? w < o.w : v < o.v;
    }
};

int n, m;
vector<Edge> g[MAXN];

int prim() {
    int sum = 0;
    set<Edge> s;
    bool chosen[MAXN];
    for (int i = 1; i <= n; i++)
        chosen[i] = 0;
    s.insert(Edge(1, 1, 0));
    while (!s.empty()) {
        Edge e = *s.begin();
        s.erase(s.begin());
        if (chosen[e.v]) continue;
        chosen[e.v] = 1;
        sum += e.w;
        for (int i = 0; i < g[e.v].size(); i++)
            if (!chosen[g[e.v][i].v])
                s.insert(g[e.v][i]);
    }
    return sum;
}

int main() {
    int u, v, w;
    scanf("%d %d", &n, &m);

    while (m--) {
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back(Edge(u, v, w));
        g[v].push_back(Edge(v, u, w));
    }

    printf("%d\n", prim());
}

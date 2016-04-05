#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 1001
#define MAXM 1000001

struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator< (const Edge &o) const {
        return w < o.w;
    }
};

int n, m, root[MAXN];
Edge e[MAXM];

int find_set(int x) {
    if (x != root[x])
        root[x] = find_set(root[x]);
    return root[x];
}

bool union_set(int u, int v) {
    int ru = find_set(u), rv = find_set(v);
    if (ru == rv)
        return 0;
    root[ru] = rv;
    return 1;
}

int kruskal() {
    int sum = 0;
    sort(e, e+m);
    for (int i = 1; i <= n; i++)
        root[i] = i;
    for (int i = 0; i < m; i++)
        if (union_set(e[i].u, e[i].v))
            sum += e[i].w;
    return sum;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
    printf("%d\n", kruskal());
}

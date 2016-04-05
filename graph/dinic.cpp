/**
 * Dinic Max Flow Algorithm
 *
 * Source: https://gist.github.com/icyrhyme/3177630
 *
 * Complexity: O(V^2 E)
 *
 * Problems: SPOJ/FASTFLOW
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

#define INF  0x3f3f3f3f
#define MAXN 5005
#define MAXM 60005

struct Edge {
    int v, c, f, next;
    Edge() {}
    Edge(int v, int c, int f, int next) : v(v), c(c), f(f), next(next) {}
};

int n, m, head[MAXN], lvl[MAXN], src, snk, work[MAXN];
Edge e[MAXM];

void init(int _n, int _src, int _snk) {
    n = _n;
    m = 0;
    src = _src;
    snk = _snk;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int c) {
    e[m] = Edge(v, c, 0, head[u]);
    head[u] = m++;
    e[m] = Edge(u, 0, 0, head[v]);
    head[v] = m++;
}

bool bfs() {
    queue<int> q;
    memset(lvl, -1, n * sizeof(int));
    lvl[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i != -1; i = e[i].next) {
            if (e[i].f < e[i].c && lvl[e[i].v] == -1) {
                lvl[e[i].v] = lvl[u] + 1;
                q.push(e[i].v);
                if (e[i].v == snk)
                    return 1;
            }
        }
    }
    return 0;
}

int dfs(int u, int f) {
    if (u == snk)
        return f;
    for (int &i = work[u]; i != -1; i = e[i].next) {
        if (e[i].f < e[i].c && lvl[u] + 1 == lvl[e[i].v]) {
            int minf = dfs(e[i].v, min(f, e[i].c - e[i].f));
            if (minf > 0) {
                e[i].f += minf;
                e[i^1].f -= minf;
                return minf;
            }
        }
    }
    return 0;
}

int dinic() {
    int f, ret = 0;
    while (bfs()) {
        memcpy(work, head, n * sizeof(int));
        while (f = dfs(src, INF))
            ret += f;
    }
    return ret;
}

int main() {
    int N, M, a, b, c;
    scanf("%d %d", &N, &M);
    init(N, 0, N-1);
    while (M--) {
        scanf("%d %d %d", &a, &b, &c);
        a--, b--;
        addEdge(a, b, c);
    }
    printf("%d\n", dinic());
}

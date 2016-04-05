/**
 * Min Cost Max Flow Problem
 * Successive Shortest Path Algorithm using Dijkstra's Algorithm
 *
 * Bellman-Ford's Algorithm used once to deal with negative costs
 *
 * Complexity: O(V * E + f * E * log V), f = maximum flow
 *
 * Problems: SPOJ/SCITIES, SPOJ/GREED
 */

#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f

#define MAXN 505
#define MAXM 100005

#define mp make_pair
#define fi first
#define se second

typedef pair<int, int> pii;

struct Edge {
    int u, v, cap, flow, cost, next;
    Edge() {}
    Edge(int u, int v, int cap, int flow, int cost, int next)
        : u(u), v(v), cap(cap), flow(flow), cost(cost), next(next) {}
};

int n, m, head[MAXN], src, snk;
Edge e[MAXM];
int pi[MAXN], dist[MAXN], path[MAXN], mincap[MAXN], vis[MAXN];

void init(int _n, int _src, int _snk) {
    n = _n;
    m = 0;
    src = _src;
    snk = _snk;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int cap, int cost) {
    e[m] = Edge(u, v, cap, 0, cost, head[u]);
    head[u] = m++;
    e[m] = Edge(v, u, 0, 0, -cost, head[v]);
    head[v] = m++;
}

int bellman_ford() {
    memset(pi, INF, sizeof(pi));
    pi[src] = 0;
    int flag = 1;
    for (int i = 0; flag && i < n; i++) {
        flag = 0;
        for (int j = 0; j < m; j++) {
            if (e[j].cap == e[j].flow)
                continue;
            if (pi[e[j].u] + e[j].cost < pi[e[j].v]) {
                pi[e[j].v] = pi[e[j].u] + e[j].cost;
                flag = 1;
            }
        }
    }
    return flag;
}

int dijkstra() {
    priority_queue<pii, vector<pii>, greater<pii> > heap;
    memset(dist, INF, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[src] = 0;
    mincap[src] = INF;
    heap.push(mp(0, src));
    while (!heap.empty()) {
        int u = heap.top().se;
        heap.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (vis[v] || e[i].flow == e[i].cap)
                continue;
            int w = dist[u] + e[i].cost + pi[u] - pi[v];
            if (w < dist[v]) {
                dist[v] = w;
                path[v] = i;
                mincap[v] = min(mincap[u], e[i].cap - e[i].flow);
                heap.push(mp(dist[v], v));
            }
        }
    }
    // update potencials
    for (int i = 0; i < n; i++)
        pi[i] += dist[i];
    return dist[snk] < INF;
}

pii mcmf() {
    // set potencials
    if (bellman_ford())
        return mp(-1, -1);
    int cost = 0, flow = 0;
    while (dijkstra()) {
        // augment path and update cost
        int f = mincap[snk];
        for (int v = snk; v != src; ) {
            int idx = path[v];
            e[idx].flow += f;
            e[idx^1].flow -= f;
            cost += e[idx].cost * f;
            v = e[idx].u;
        }
        flow += f;
    }
    return mp(cost, flow);
}

int main() {
    int T, c1, c2, u, v, w;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &c1, &c2);
        init(c1+c2+2, 0, c1+c2+1);
        for (int i = 1; i <= c1; i++)
            addEdge(src, i, 1, 0);
        for (int i = 1; i <= c2; i++)
            addEdge(c1+i, snk, 1, 0);
        while (scanf("%d %d %d", &u, &v, &w), u)
            addEdge(u, c1+v, 1, w);
        pii cf = mcmf();
    }
}

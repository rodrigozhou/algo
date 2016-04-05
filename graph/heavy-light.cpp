/**
 * Heavy-Light Decomposition
 *
 * Problems: SPOJ/QTREE
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 10005

struct SegTree {
    vector<int> data, tree;
    int sz;

    SegTree(int tsz) : sz(1) {
        while (sz < tsz) sz *= 2;
        data.resize(sz);
        tree.resize(2*sz);
    }

    inline int left(int u) { return u << 1; }
    inline int right(int u) { return left(u) + 1; }

    void init(int u, int l, int r) {
        if (l == r) { tree[u] = data[l]; return; }
        int m = (l + r) >> 1;
        init(left(u), l, m);
        init(right(u), m+1, r);
        tree[u] = max(tree[left(u)], tree[right(u)]);
    }
    void init() { init(1, 0, sz-1); }

    int query(int u, int l, int r, int a, int b) {
        if (a <= l && r <= b) return tree[u];
        int m = (l + r) >> 1, ret = 0;
        if (a <= m) ret = query(left(u), l, m, a, b);
        if (m < b) ret = max(ret, query(right(u), m+1, r, a, b));
        return ret;
    }
    int query(int a, int b) { return query(1, 0, sz-1, a, b); }

    void update(int u, int l, int r, int pos, int val) {
        if (l == r) { tree[u] = val; return; }
        int m = (l + r) >> 1;
        if (pos <= m) update(left(u), l, m, pos, val);
        else update(right(u), m+1, r, pos, val);
        tree[u] = max(tree[left(u)], tree[right(u)]);
    }
    void update(int pos, int val) { update(1, 0, sz-1, pos, val); }
};

struct edge {
    int u, v, w, next;
    edge() {}
    edge(int u, int v, int w, int next) : u(u), v(v), w(w), next(next) {}
};

int n, m, head[MAX];
edge e[2*MAX];
int dad[MAX], lvl[MAX], chd[MAX], sz[MAX], heavy[MAX];
int nump, psize[MAX], pfirst[MAX], path[MAX], offset[MAX];
vector<int> walk;
vector<SegTree> ptree;

void init() {
    m = 0;
    memset(head, -1, sizeof(head));
    memset(dad, 0, sizeof(dad));
}

void addEdge(int u, int v, int w, bool rev = false) {
    e[m] = edge(u, v, w, head[u]);
    head[u] = m++;
    if (!rev) addEdge(v, u, w, true);
}

void dfs(int u) {
    walk.push_back(u);
    sz[u] = 1;
    for (int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (!dad[v]) {
            dad[v] = u;
            lvl[v] = lvl[u] + 1;
            dfs(v);
            sz[u] += sz[v];
        }
    }
    for (int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (dad[v] == u && 2*sz[v] >= sz[u]) {
            heavy[v] = 1;
            break;
        }
    }
    heavy[u] = 0;
}

void hl_init() {
    walk.clear();
    dad[1] = 1;
    lvl[1] = 0;
    dfs(1);

    nump = 0;
    for (int i = 0; i < n; i++) {
        int u = walk[i];
        if (!heavy[u]) {
            offset[u] = 0;
            path[u] = nump;
            pfirst[nump] = u;
            psize[nump++] = 1;
        }
        else {
            offset[u] = offset[dad[u]] + 1;
            path[u] = path[dad[u]];
            psize[path[u]]++;
        }
    }

    ptree.clear(); ptree.reserve(nump);
    for (int i = 0; i < nump; i++)
        ptree.push_back(SegTree(psize[i]));

    for (int i = 0; i < m; i += 2) {
        int u = e[i].u, v = e[i].v;
        if (u != dad[v]) swap(u, v);
        ptree[path[v]].data[offset[v]] = e[i].w;
    }

    for (int i = 0; i < nump; i++)
        ptree[i].init();
}

int lca(int u, int v) {
    int fpu = pfirst[path[u]], fpv = pfirst[path[v]];
    while (fpu != fpv) {
        if (lvl[fpu] > lvl[fpv])
            u = dad[fpu], fpu = pfirst[path[u]];
        else
            v = dad[fpv], fpv = pfirst[path[v]];
    }
    return lvl[u] < lvl[v] ? u : v;
}

void update(int idx, int val) {
    int u = e[idx].u, v = e[idx].v;
    if (u != dad[v]) swap(u, v);
    ptree[path[v]].update(offset[v], val);
}

int query(int u, int v, bool up = false) {
    if (!up) {
        int w = lca(u, v);
        return max(query(u, w, true), query(v, w, true));
    }
    int ret = 0;
    int fpu = pfirst[path[u]], fpv = pfirst[path[v]];
    while (fpu != fpv) {
        ret = max(ret, ptree[path[u]].query(0, offset[u]));
        u = dad[fpu];
        fpu = pfirst[path[u]];
    }
    if (u != v)
        ret = max(ret, ptree[path[u]].query(offset[v]+1, offset[u]));
    return ret;
}

int main() {
    int T, u, v, w, a, b;
    char op[8];
    scanf("%d", &T);
    while (T--) {
        init();
        scanf("%d", &n);
        for (int i = 1; i < n; i++) {
            scanf("%d %d %d", &u, &v, &w);
            addEdge(u, v, w);
        }
        hl_init();
        while (scanf("%s", op), op[0] != 'D') {
            scanf("%d %d", &a, &b);
            if (op[0] == 'C')
                update(2*a - 2, b);
            else
                printf("%d\n", query(a, b));
        }
        if (T) puts("");
    }
}

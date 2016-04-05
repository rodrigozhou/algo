/**
 * Persistent Segment Tree
 *
 * Problems: SPOJ/COT
 */

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 100005
#define LOGMAX 18

int n, val[MAX];
int aux[MAX], dict[MAX], rdict[MAX], maxval;
vector<int> g[MAX];
int anc[MAX][LOGMAX], dad[MAX], lvl[MAX];

struct Node {
    int count;
    Node *left, *right;

    Node(int count, Node *left, Node *right)
        : count(count), left(left), right(right) {}

    Node *insert(int l, int r, int w);
};

Node *nullNode = new Node(0, NULL, NULL);

Node* Node::insert(int l, int r, int w) {
    if (l <= w && w < r) {
        if (r - l == 1)
            return new Node(this->count + 1, nullNode, nullNode);
        int m = (l + r) / 2;
        return new Node(this->count + 1,
                        this->left->insert(l, m, w),
                        this->right->insert(m, r, w));
    }
    return this;
}

Node *root[MAX];

void dfs(int u, int p) {
    dad[u] = p;
    lvl[u] = p == -1 ? 0 : lvl[p] + 1;

    root[u] = (p == -1 ? nullNode : root[p])->insert(0, maxval, dict[u]);

    for (int i = 0; i < g[u].size(); i++)
        if (g[u][i] != p)
            dfs(g[u][i], u);
}

void prelca() {
    memset(anc, -1, sizeof(anc));
    for (int i = 0; i < n; i++)
        anc[i][0] = dad[i];
    for (int j = 1; 1<<j < n; j++)
        for (int i = 0; i < n; i++)
            if (anc[i][j-1] != -1)
                anc[i][j] = anc[anc[i][j-1]][j-1];
}

int lca(int u, int v) {
    if (lvl[u] < lvl[v])
        swap(u, v);
    int log;
    for (log = 1; 1<<log <= lvl[u]; log++);
    log--;
    for (int i = log; i >= 0; i--)
        if (lvl[u] - (1 << i) >= lvl[v])
            u = anc[u][i];
    if (u == v)
        return u;
    for (int i = log; i >= 0; i--)
        if (anc[u][i] != anc[v][i])
            u = anc[u][i], v = anc[v][i];
    return dad[u];
}

int query(Node *a, Node *b, Node *c, Node *d, int l, int r, int k) {
    if (r - l == 1)
        return l;
    int count = a->left->count + b->left->count - c->left->count - d->left->count;
    int m = (l + r) / 2;
    if (count >= k)
        return query(a->left, b->left, c->left, d->left, l, m, k);
    return query(a->right, b->right, c->right, d->right, m, r, k - count);
}

int main() {
    int q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
        aux[i] = val[i];
    }

    sort(aux, aux+n);
    maxval = unique(aux, aux+n) - aux;
    for (int i = 0; i < n; i++) {
        dict[i] = lower_bound(aux, aux+maxval, val[i]) - aux;
        rdict[dict[i]] = i;
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    nullNode->left = nullNode->right = nullNode;
    dfs(0, -1);
    prelca();

    while (q--) {
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        u--, v--;
        int w = lca(u, v);
        int ans = query(root[u], root[v], root[w], dad[w] == -1 ? nullNode : root[dad[w]], 0, maxval, k);
        printf("%d\n", val[rdict[ans]]);
    }
}

/**
 * Persistent Segment Tree
 *
 * Problems: SPOJ/MKTHNUM, SPOJ/COT
 */

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX 100005

struct Node {
    int cnt, l, r;
    Node () : cnt(0), l(0), r(0) {}
    Node (int cnt, int l, int r) : cnt(cnt), l(l), r(r) {}
};

int n, a[MAX], b[MAX];
Node tree[20*MAX];
int root[MAX], id = 1;

int update(int no, int l, int r, int x) {
    if (x < l || x > r) return no;
    if (l == r) {
        tree[id] = Node(1, 0, 0);
        return id++;
    }
    int m = (l + r) / 2;
    int ll = update(tree[no].l, l, m, x);
    int rr = update(tree[no].r, m+1, r, x);
    tree[id] = Node(tree[ll].cnt + tree[rr].cnt, ll, rr);
    return id++;
}

int query(int a, int b, int l, int r, int k) {
    if (l == r) return l;
    int m = (l + r) / 2;
    int cnt = tree[tree[b].l].cnt - tree[tree[a].l].cnt;
    if (k <= cnt)
        return query(tree[a].l, tree[b].l, l, m, k);
    return query(tree[a].r, tree[b].r, m+1, r, k-cnt);
}

int main() {
    int q, l, r, k;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b+1, b+n+1);
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(b+1, b+n+1, a[i]) - b;
        root[i] = update(root[i-1], 1, n, a[i]);
    }
    while (q--) {
        scanf("%d %d %d", &l, &r, &k);
        printf("%d\n", b[query(root[l-1], root[r], 1, n, k)]);
    }
}

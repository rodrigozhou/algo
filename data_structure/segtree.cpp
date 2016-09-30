/**
 * Segment Tree
 *
 * Problems: SPOJ/HORRIBLE
 */

#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 100005

#define left(x)  ((x) << 1)
#define right(x) (left(x) + 1)

typedef long long ll;

ll tree[4*MAXN], lazy[4*MAXN];

void propagate(int node, int lo, int hi) {
    tree[node] += lazy[node] * (hi-lo+1);
    if (lo != hi) {
        lazy[left(node)] += lazy[node];
        lazy[right(node)] += lazy[node];
    }
    lazy[node] = 0;
}

void update(int node, int lo, int hi, int a, int b, int val) {
    if (a <= lo && hi <= b) {
        lazy[node] += val;
        return;
    }
    propagate(node, lo, hi);
    int mid = (lo + hi)/2;
    if (a <= mid)
        update(left(node), lo, mid, a, b, val);
    if (b > mid)
        update(right(node), mid+1, hi, a, b, val);
    propagate(left(node), lo, mid);
    propagate(right(node), mid+1, hi);
    tree[node] = tree[left(node)] + tree[right(node)];
}

ll query(int node, int lo, int hi, int a, int b) {
    propagate(node, lo, hi);
    if (a <= lo && hi <= b)
        return tree[node];
    ll ret = 0;
    int mid = (lo + hi)/2;
    if (a <= mid)
        ret = query(left(node), lo, mid, a, b);
    if (b > mid)
        ret += query(right(node), mid+1, hi, a, b);
    return ret;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, c;
        scanf("%d %d", &n, &c);
        memset(tree, 0, sizeof(tree));
        memset(lazy, 0, sizeof(lazy));
        while (c--) {
            int op, p, q, v;
            scanf("%d", &op);
            if (op == 0) {
                scanf("%d %d %d", &p, &q, &v);
                update(1, 1, n, p, q, v);
            }
            else {
                scanf("%d %d", &p, &q);
                printf("%lld\n", query(1, 1, n, p, q));
            }
        }
    }
}

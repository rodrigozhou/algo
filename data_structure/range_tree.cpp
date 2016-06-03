/**
 * Range Tree 2D with Fractional Cascading
 *
 * Complexity: O(n log n), O(log n)
 *
 * Problems: SPOJ/MKTHNUM
 */

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define INF 0x3f3f3f3f
#define MAX 100005

struct Point {
    int x, y;
    Point () {}
    Point (int x, int y) : x(x), y(y) {}
    bool operator<(const Point &o) const {
        return x != o.x ? x < o.x : y < o.y;
    }
};

bool cmpy(const Point &a, const Point &b) {
    return a.y != b.y ? a.y < b.y : a.x < b.x;
}

vector<int> xs;
vector<Point> pnts;
vector<Point> tree[4*MAX];
vector<int> link[4*MAX][2];

int init(int node, int left, int right) {
    if (right - left == 1) {
        vector<Point>::iterator it;
        it = lower_bound(pnts.begin(), pnts.end(), Point(xs[left], -INF));
        for (; it != pnts.end() && it->x == xs[left]; it++)
            tree[node].push_back(*it);
        return tree[node].size();
    }

    int mid = (left + right) / 2, cl = 2*node + 1, cr = cl + 1;
    int szl = init(cl, left, mid);
    int szr = init(cr, mid, right);

    tree[node].reserve(szl + szr);
    link[node][0].reserve(szl + szr + 1);
    link[node][1].reserve(szl + szr + 1);

    int l = 0, r = 0, llink = 0, rlink = 0;
    while (l < szl || r < szr) {
        Point last;
        if (r == szr || (l < szl && cmpy(tree[cl][l], tree[cr][r])))
            tree[node].push_back(last = tree[cl][l++]);
        else
            tree[node].push_back(last = tree[cr][r++]);

        while (llink < szl && cmpy(tree[cl][llink], last))
            llink++;
        while (rlink < szr && cmpy(tree[cr][rlink], last))
            rlink++;

        link[node][0].push_back(llink);
        link[node][1].push_back(rlink);
    }

    link[node][0].push_back(szl);
    link[node][1].push_back(szr);

    return tree[node].size();
}

void build() {
    sort(pnts.begin(), pnts.end());
    xs.clear();
    for (int i = 0; i < pnts.size(); i++)
        xs.push_back(pnts[i].x);
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    init(0, 0, xs.size());
}

// query on [a, b] x [c, d]
int query(int node, int l, int r, int a, int b, int c, int d,
        int posl = -1, int posr = -1) {
    if (node == 0) {
        posl = lower_bound(tree[0].begin(), tree[0].end(), Point(a, c), cmpy)
            - tree[0].begin();
        posr = upper_bound(tree[0].begin(), tree[0].end(), Point(b, d), cmpy)
            - tree[0].begin();
    }

    if (posl == posr)
        return 0;
    if (a <= xs[l] && xs[r-1] <= b)
        return posr - posl;
    if (b < xs[l] || a > xs[r-1])
        return 0;

    int m = (l + r) / 2, ret = 0;
    if (a < xs[m])
        ret += query(2*node+1, l, m, a, b, c, d,
                     link[node][0][posl], link[node][0][posr]);
    if (xs[m] <= b)
        ret += query(2*node+2, m, r, a, b, c, d,
                     link[node][1][posl], link[node][1][posr]);
    return ret;
}

int n, a[MAX], q;

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        pnts.push_back(Point(a[i], i));
    }
    build();
    while (q--) {
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        int lo = 0, hi = xs.size() - 1;
        while (lo < hi) {
            int mi = (lo + hi) / 2;
            int cnt = query(0, 0, xs.size(), xs[0], xs[mi], i-1, j-1);
            if (cnt < k)
                lo = mi + 1;
            else
                hi = mi;
        }
        printf("%d\n", xs[lo]);
    }
}

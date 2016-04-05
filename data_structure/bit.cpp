/**
 * Binary Indexed Tree
 * Range query with any function in O(log n)
 *
 * Problems: SPOJ/RPLN
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

#define INF 0x3f3f3f3f
#define MAX 100005

struct _BIT {
    int n, bit[2*MAX];

    _BIT(int n = 0) {
        init(n);
    }

    void init(int _n) {
        n = _n;
        memset(bit, INF, (n+1)*sizeof(int));
    }

    void update(int x, int val) {
        for (; x <= n; x += x & -x)
            bit[x] = min(bit[x], val);
    }

    int query(int x) const {
        int ret = INF;
        for (; x > 0; x -= x & -x)
            ret = min(ret, bit[x]);
        return ret;
    }

    int query(int l, int r, int &ret) const {
        while (r - (r & -r) >= l) {
            ret = min(ret, bit[r]);
            r -= r & -r;
        }
        return r;
    }
};

struct BIT {
    int n, a[MAX];
    int pow2n;
    _BIT bf, br;

    BIT(int n = 0) {
        init(n);
    }

    void init(int _n) {
        n = _n;
        memset(a, INF, (n+1)*sizeof(int));
        for (pow2n = 1; pow2n <= n; pow2n <<= 1);
        bf.init(n);
        br.init(pow2n-1);
    }

    void update(int x, int val) {
        a[x] = val;
        bf.update(x, val);
        br.update(pow2n - x, val);
    }

    int query(int x) const {
        return bf.query(x);
    }

    int query(int l, int r) const {
        int ret = INF;
        int x = bf.query(l, r, ret);
        int y = br.query(pow2n - r, pow2n - l, ret);
        assert(x+y == pow2n);
        return min(ret, a[x]);
    }
};

BIT bit;

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        int n, q, x;
        scanf("%d %d", &n, &q);
        bit.init(n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            bit.update(i, x);
        }
        printf("Scenario #%d:\n", t);
        while (q--) {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%d\n", bit.query(a, b));
        }
    }
}

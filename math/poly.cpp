#include <algorithm>
#include <vector>
#include "fft.h"
using namespace std;

#define MAXN 1000
#define MAXX 1000

int cmp(double x, double y, double eps = 1e-8) {
    return x + eps > y ? y + eps > x ? 0 : 1 : -1;
}

struct Poly {
    int n;
    double a[MAXN];
    Poly(int n = 0) : n(n) {
        memset(a, 0, sizeof(a));
    }
    Poly(const Poly &o) : n(o.n) {
        memcpy(a, o.a, sizeof(a));
    }
    const double& operator[] (int i) const {
        return a[i];
    }
    double& operator[] (int i) {
        return a[i];
    }
    double operator() (double x) const {
        double ret = 0;
        for (int i = n; i >= 0; i--)
            ret = ret * x + a[i];
        return ret;
    }
    Poly operator+ (const Poly &o) const {
        Poly ret = o;
        for (int i = 0; i <= n; i++)
            ret[i] += a[i];
        ret.n = max(n, o.n);
        return ret;
    }
    Poly operator- (const Poly &o) const {
        Poly ret = o;
        for (int i = 0; i <= n; i++)
            ret[i] -= a[i];
        ret.n = max(n, o.n);
        return ret;
    }
    Poly operator* (const Poly &o) const {
        Poly ret(n + o.n);
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= o.n; j++)
                ret[i+j] += a[i] * o[j];
        return ret;
    }
};

Poly fastMul(const Poly &p, const Poly &q) {
    int sz = 1 << (32 - __builtin_clz(p.n + q.n + 1));
    vector<pt> pin(sz), qin(sz);
    for (int i = 0; i < p.n; i++)
        pin[i] = p[i];
    for (int i = 0; i < q.n; i++)
        qin[i] = q[i];
    convolve(pin, qin);
    Poly ret(p.n + q.n);
    while (ret.n > 0 && cmp(ret[ret.n], 0) == 0)
        ret.n--;
    return ret;
}

Poly diff(const Poly &p) {
    Poly ret(p.n-1);
    for (int i = 1; i <= p.n; i++)
        ret[i-1] = i * p[i];
    return ret;
}

pair<Poly, double> ruffini(const Poly &p, double x) {
    if (p.n == 0)
        return make_pair(Poly(), 0);
    Poly ret(p.n-1);
    for (int i = p.n; i > 0; i--)
        ret[i-1] = ret[i] * x + p[i];
    return make_pair(ret, ret[0] * x + p[0]);
}

/**
 * Find a root in range [lo, hi] assuming that exists only one root in [lo, hi]
 * pair::second is true if exists a root in the given range or false otherwise
 * pair::first is the root if pair::second is true or 0 if false
 */
pair<double, int> findRoot(const Poly &p, double lo, double hi) {
    if (cmp(p(lo), 0) == 0)
        return make_pair(lo, 1);
    if (cmp(p(hi), 0) == 0)
        return make_pair(hi, 1);
    if (cmp(p(lo), 0) == cmp(p(hi), 0))
        return make_pair(0, 0);
    if (cmp(p(lo), p(hi)) > 0)
        swap(lo, hi);
    while (cmp(lo, hi) != 0) {
        double mid = (lo + hi) / 2;
        double val = p(mid);
        if (cmp(val, 0) == 0)
            lo = hi = mid;
        else if (cmp(val, 0) < 0)
            lo = mid;
        else
            hi = mid;
    }
    return make_pair(lo, 1);
}

/**
 * Return a vector of all real roots with their multiplicity in ascending order
 */
vector<double> roots(const Poly &p) {
    vector<double> ret;
    if (p.n == 1) {
        ret.push_back(-p[0] / p[1]);
    }
    else {
        vector<double> r = roots(diff(p));
        r.push_back(-MAXX);
        r.push_back(MAXX);
        sort(r.begin(), r.end());
        for (int i = 0, j = 1; j < (int) r.size(); i++, j++) {
            pair<double, int> pr = findRoot(p, r[i], r[j]);
            if (pr.second)
                ret.push_back(pr.first);
        }
    }
    return ret;
}

int main() {
}

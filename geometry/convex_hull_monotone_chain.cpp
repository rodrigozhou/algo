#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define INF  0x3f3f3f3f
#define MAXN 1010

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    Point operator- (const Point &o) const {
        return Point(x - o.x, y - o.y);
    }
    int operator% (const Point &o) const {
        return x * o.y - o.x * y;
    }
    bool operator< (const Point &o) const {
        return x != o.x ? x < o.x : y < o.y;
    }
};

int ccw(const Point &p, const Point &q, const Point &r) {
    return (q - p) % (r - p);
}

int sqr(int x) {
    return x*x;
}

int n, k;
Point p[MAXN], h[MAXN];

void convex_hull() {
    sort(p, p+n);
    k = 0;
    h[k++] = p[0];
    for (int i = 1; i < n; i++) {
        if (i != n-1 && ccw(p[0], p[n-1], p[i]) >= 0) continue;
        while (k > 1 && ccw(h[k-2], h[k-1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    for (int i = n-2; i >= 0; i--) {
        if (i != 0 && ccw(p[n-1], p[0], p[i]) >= 0) continue;
        while (ccw(h[k-2], h[k-1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &p[i].x, &p[i].y);

    convex_hull();

    double d = 0;
    for (int i = 1; i < k; i++)
        d += sqrt(sqr(h[i].x - h[i-1].x) + sqr(h[i].y - h[i-1].y));
    printf("%lf\n", d);

    for (int i = 0; i < k; i++)
        printf("(%d,%d)\n", h[i].x, h[i].y);
    printf("\n");
}

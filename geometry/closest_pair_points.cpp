/**
 * Closest Pair of Points
 *
 * Complexity: O(n log n)
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <set>
using namespace std;

#define MAXN 100005

const double inf = 1.0/0.0;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    Point operator- (const Point &o) const { return Point(x - o.x, y - o.y); }
    int operator* (const Point &o) const { return x * o.x + y * o.y; }
    bool operator< (const Point &o) const {
        return y != o.y ? y < o.y : x < o.x;
    }
};
bool cmpx(const Point &p, const Point &q) {
    return p.x != q.x ? p.x < q.x : p.y < q.y;
}

double abs(const Point &p) {
    return sqrt(p*p);
}

int main() {
    int n;
    Point pnts[MAXN];
    set<Point> box;
    set<Point>::iterator it;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &pnts[i].x, &pnts[i].y);
    sort(pnts, pnts+n, cmpx);
    double best = inf;
    box.insert(pnts[0]);
    for (int i = 1, j = 0; i < n; i++) {
        while (j < i && pnts[i].x - pnts[j].x > best)
            box.erase(pnts[j++]);
        for (it = box.lower_bound(Point(pnts[i].x-best, pnts[i].y-best));
             it != box.end() && it->y <= pnts[i].y + best; it++) {
            best = min(best, abs(pnts[i] - *it));
        }
        box.insert(pnts[i]);
    }
    printf("%.2lf\n", best);
}

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAXN 1000000

int cmp(double a, double b, double eps = 1e-9) {
    return a+eps > b ? b+eps > a ? 0 : 1 : -1;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator+ (const Point &o) const { return Point(x+o.x, y+o.y); }
    Point operator- (const Point &o) const { return Point(x-o.x, y-o.y); }
    Point operator* (const double &o) const { return Point(x*o, y*o); }
    Point operator/ (const double &o) const { return Point(x/o, y/o); }
    double operator* (const Point &o) const { return x*o.x + y*o.y; }
    double operator% (const Point &o) const { return x*o.y - y*o.x; }
};

struct Circle {
    Point p;
    double r;
    Circle(Point p, double r) : p(p), r(r) {}
};

double abs(const Point &p) {
    return sqrt(p*p);
}

bool in_circle(const Circle &c, const Point &p) {
    return cmp(abs(c.p - p), c.r) <= 0;
}

Point circumcenter(const Point &p, const Point &q, const Point &r) {
    Point a = p-r, b = q-r, c = Point(a*(p+r)/2, b*(q+r)/2);
    return Point(c % Point(a.y, b.y), Point(a.x, b.x) % c)/(a % b);
}

int n;
Point p[MAXN];

Circle spanning_circle() {
    random_shuffle(p, p+n);
    Circle c(Point(), -1);
    for (int i = 0; i < n; i++) if (!in_circle(c, p[i])) {
        c = Circle(p[i], 0);
        for (int j = 0; j < i; j++) if (!in_circle(c, p[j])) {
            c = Circle((p[i] + p[j])/2, abs(p[i] - p[j])/2);
            for (int k = 0; k < j; k++) if (!in_circle(c, p[k])) {
                Point o = circumcenter(p[i], p[j], p[k]);
                c = Circle(o, abs(o - p[k]));
            }
        }
    }
    return c;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf %lf", &p[i].x, &p[i].y);
    
    Circle c = spanning_circle();
    printf("%lf\n%lf %lf\n", c.r, c.p.x, c.p.y);
}

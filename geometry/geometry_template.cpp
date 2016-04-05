/**
 * Geometry Template
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double inf = 1.0/0.0;

int cmp_double(double a, double b, double eps = 1e-6) {
    return a + eps > b ? b + eps > a ? 0 : 1 : -1;
}

struct Point {
    double x, y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    Point operator+ (const Point &o) const { return Point(x + o.x, y + o.y); }
    Point operator- (const Point &o) const { return Point(x - o.x, y - o.y); }
    Point operator* (const double &o) const { return Point(x * o, y * o); }
    Point operator/ (const double &o) const { return Point(x / o, y / o); }
    double operator* (const Point &o) const { return x * o.x + y * o.y; }
    double operator% (const Point &o) const { return x * o.y - o.x * y; }

    bool operator== (const Point &o) const {
        return cmp_double(x, o.x) == 0 && cmp_double(y, o.y) == 0;
    }

    bool operator< (const Point &o) const {
        return x != o.x ? x < o.x : y < o.y;
    }
};

typedef Point Vector;

double abs(Point p) {
    return sqrt(p * p);
}

Vector norm(Vector v) {
    return v / abs(v);
}

double ccw(Point p, Point q, Point r) {
    return (q - p) % (r - p);
}

struct Segment {
    Point p, q;

    Segment() {}
    Segment(Point p, Point q) : p(p), q(q) {}
};

bool in_segment(Point p, Segment s) {
    double t;
    Vector v = s.q - s.p;
    if (cmp_double(v.x, 0) != 0)
        t = (p.x - s.p.x) / v.x;
    else
        t = (p.y - s.p.y) / v.y;
    return cmp_double(t, 0) >= 0 && cmp_double(t, 1) <= 0 && s.p + v * t == p;
}

struct Line {
    Vector v;
    Point p;
    int a, b, c;

    void init() {
        a = -v.y;
        b = v.x;
        c = a * p.x + b * p.y;
        int d = abs(__gcd(a, __gcd(b, c)));
        if (d != 1)
            a /= d, b /= d, c /= d;
        if (a < 0)
            a = -a, b = -b, c = -c;
        else if (a == 0 && b < 0)
            b = -b, c = -c;
    }

    Line() {}
    Line(Point p, Point q) : v(q-p), p(p) {
        init();
    }
    Line(Segment s) : v(s.q-s.p), p(p) {
        init();
    }

    Point operator() (double t) const { return p + v * t; }

    Vector normal() {
        return Vector(-v.y, v.x);
    }
};

pair<double, double> line_intersection(Line a, Line b) {
    double den = a.v % b.v;
    if (den == 0)
        return make_pair(inf, inf);
    double t = -(b.v % (b.p - a.p)) / den;
    double s = -(a.v % (b.p - a.p)) / den;
    return make_pair(t, s);
}

Point segment_intersection(Segment a, Segment b) {
    Line la = Line(a), lb = Line(b);
    pair<double, double> pdd = line_intersection(la, lb);
    double t = pdd.first, s = pdd.second;
    if (t == inf) {
        if (in_segment(b.p, a))
            return b.p;
        if (in_segment(b.q, a))
            return b.q;
        if (in_segment(a.p, b))
            return a.p;
        if (in_segment(a.q, b))
            return a.q;
        return Point(inf, inf);
    }
    if (cmp_double(t, 0) < 0 || cmp_double(t, 1) > 0)
        return Point(inf, inf);
    if (cmp_double(s, 0) < 0 || cmp_double(s, 1) > 0)
        return Point(inf, inf);
    return la(t);
}

double distPointToLine(Point p, Line l) {
    Vector n = l.normal();
    return abs((l.p - p) * n / abs(n));
}

struct Circle {
    Point p;
    double r;

    Circle() {}
    Circle(Point p, double r) : p(p), r(r) {}
};

bool in_circle(const Circle &c, const Point &p) {
    return cmp(abs(c.p - p), c.r) <= 0;
}

Point circumcenter(Point p, Point q, Point r) {
    Point a = p - r, b = q - r, c = Point(a*(p+r)/2, b*(q+r)/2);
    return Point(c % Point(a.y, b.y), Point(a.x, b.x) % c)/(a % b);
}

Point incenter(Point p, Point q, Point r) {
    double a = abs(r - q), b = abs(r - p), c = abs(q - p);
    return (p * a + q * b + r * c) / (a + b + c);
}

int main() {
}

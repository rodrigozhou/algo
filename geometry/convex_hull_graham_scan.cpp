/**
 * Convex Hull
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int INF = 1<<30;
const int MAXDOTS = 1001;

struct tdot {
    int x, y;
    tdot() {}
    tdot(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

int n;
tdot dot[MAXDOTS], s[MAXDOTS];

bool cmp(const tdot &a, const tdot &b) {
    return atan2(a.y - dot[0].y, a.x - dot[0].x) < atan2(b.y - dot[0].y, b.x - dot[0].x);
}

int find_area(const tdot &a, const tdot &b, const tdot &c) {
    return (a.x*b.y + b.x*c.y + c.x*a.y) - (a.y*b.x + b.y*c.x + c.y*a.x);
}

int convex_hull() {
    int idx = 2;
    s[0] = dot[0];
    s[1] = dot[1];
    for (int i = 2; i < n; i++) {
        if (find_area(s[idx-2], s[idx-1], dot[i]) >= 0) {
            s[idx++] = dot[i];
        }
        else {
            do {
                idx--;
            } while (find_area(s[idx-2], s[idx-1], dot[i]) < 0);
            s[idx++] = dot[i];
        }
    }
    return idx;
}

int main() {
    int mindot = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &dot[i].x, &dot[i].y);
        if (dot[i].x < dot[mindot].x)
            mindot = i;
        else if (dot[i].x == dot[mindot].x && dot[i].y < dot[mindot].y)
            mindot = i;
    }
    swap(dot[mindot], dot[0]);
    sort(dot+1, dot+n, cmp);
    int qnt = convex_hull();
    for (int i = 0; i < qnt; i++) {
        printf("(%d, %d)\n", s[i].x, s[i].y);
    }
}

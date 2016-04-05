#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

#define MAXN 10010
#define MAXM 30005
#define left(x)  (x << 1)
#define right(x) ((x << 1) + 1)

struct Event {
    int type; // 0 = ending ; 1 = beginning
    int x;
    int y0, y1;
    Event () {}
    Event (int type, int x, int y0, int y1) :
        type(type), x(x), y0(y0), y1(y1) {}
};

bool cmp(const Event& a, const Event& b) {
    if (a.x != b.x)
        return a.x < b.x;
    return a.type < b.type;
}

struct Node {
    int cnt, length;
};

int n, n2, id;
Node tree[4*MAXM];
Event ev[2*MAXN];
map<int, int> dict;
int rdict[2*MAXN];
int area = 0;

void update(int node, int lo, int hi, int i, int j, int val) {
    if (i >= hi || j <= lo)
        return;
    if (i <= lo && hi <= j) {
        tree[node].cnt += val;
        if (tree[node].cnt)
            tree[node].length = rdict[hi] - rdict[lo];
        else
            tree[node].length = tree[left(node)].length + tree[right(node)].length;
        return;
    }
    int mid = (lo + hi) >> 1;
    update(left(node), lo, mid, i, j, val);
    update(right(node), mid, hi, i, j, val);
    if (tree[node].cnt)
        tree[node].length = rdict[hi] - rdict[lo];
    else
        tree[node].length = tree[left(node)].length + tree[right(node)].length;
}

int main() {
    int x0, y0, x1, y1;
    int ys[2*MAXN];
    scanf("%d", &n);
    n2 = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &x0, &y0, &x1, &y1);
        ys[n2] = y0;
        ev[n2++] = Event(1, x0, y0, y1);
        ys[n2] = y1;
        ev[n2++] = Event(0, x1, y0, y1);
    }
    id = 0;
    sort(ys, ys+n2);
    for (int i = 0; i < n2; ) {
        dict[ys[i]] = id;
        rdict[id] = ys[i];
        id++;
        i++;
        while (i < n2 && ys[i] == ys[i-1])
            i++;
    }
    for (int i = 0; i < n2; i++) {
        ev[i].y0 = dict[ev[i].y0];
        ev[i].y1 = dict[ev[i].y1];
    }
    sort(ev, ev+n2, cmp);
    for (int i = 0, x = ev[0].x; i < n2; i++) {
        area += tree[1].length * (ev[i].x - x);
        x = ev[i].x;
        if (ev[i].type == 1)
            update(1, 0, id, ev[i].y0, ev[i].y1, 1);
        else
            update(1, 0, id, ev[i].y0, ev[i].y1, -1);
    }
    printf("%d\n", area);
}

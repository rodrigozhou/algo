/**
 * Weighted Activity Selection Algorithm
 * Complexity: O(n log n)
 */

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 10005

struct Event {
    int b, e, w;
    Event () {}
    Event (int b, int e, int w) : b(b), e(e), w(w) {}
    bool operator< (const Event& o) const {
        if (e != o.e)
            return e < o.e;
        return b < o.b;
    }
};

int n;
Event e[MAXN];

int dp[MAXN];

int main() {
    scanf("%d", &n);
    e[0] = Event(0, 0, 0);
    for (int i = 1; i <= n; i++)
        scanf("%d %d %d", &e[i].b, &e[i].e, &e[i].w);
    sort(e+1, e+n+1);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int lo = 0, hi = i-1;
        while (lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if (e[mid].e > e[i].b)
                hi = mid - 1;
            else
                lo = mid;
        }
        dp[i] = max(dp[i-1], e[i].w + dp[lo]);
    }
    printf("Max weight: %d\n", dp[n]);
}

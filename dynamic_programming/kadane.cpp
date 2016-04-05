/**
 * Kadane's Algorithm
 *
 * Maximum subarray problem
 */

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int n, a[MAXN];

int kadane() {
    int maxsum = 0, maxi = 0;
    for (int i = 0; i < n; i++) {
        maxi = max(0, maxi + a[i]);
        maxsum = max(maxsum, maxi);
    }
    return maxsum;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    printf("%d\n", kadane());
}

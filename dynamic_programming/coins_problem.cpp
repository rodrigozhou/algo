#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 110
#define MAXM 10010
const int INF = 1<<30;

int m, n, coin[MAXN], sum[MAXM];

void solve() {
    sum[0] = 0;
    for (int i = 1; i <= m; i++)
        sum[i] = INF;
    for (int i = 0; i < n; i++)
        for (int j = coin[i]; j <= m; j++)
            sum[j] = min(sum[j], sum[j-coin[i]]+1);
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &coin[i]);

    solve();
    if (sum[m] != INF)
        printf("%d\n", sum[m]);
    else
        printf("impossible\n");
}

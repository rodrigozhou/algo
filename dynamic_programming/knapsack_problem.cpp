#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXP 110
#define MAXW 1010

int p, w, value[MAXP], weight[MAXP], m[MAXP][MAXW];

void solve() {
    for (int i = 0; i <= p; i++)
        m[i][0] = 0;
    for (int j = 0; j <= w; j++)
        m[0][j] = 0;
    for (int i = 1; i <= p; i++) {
        for (int j = 1; j <= w; j++) {
            if (j >= weight[i]) {
                m[i][j] = max(m[i-1][j], m[i-1][j-weight[i]] + value[i]);
            } else {
                m[i][j] = m[i-1][j];
            }
        }
    }
}

int main() {
    scanf("%d %d", &p, &w);
    for (int i = 1; i <= p; i++)
        scanf("%d %d", &value[i], &weight[i]);

    solve();
    printf("%d\n", m[p][w]);
}

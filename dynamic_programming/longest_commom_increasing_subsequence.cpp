#include <cstdio>
using namespace std;

#define MAXN 1000

int n, m, a[MAXN], b[MAXN];
int c[MAXN], prev[MAXN], seq[MAXN];

void lcis() {
    for (int j = 0; j < m; j++)
        c[j] = 0;
    for (int i = 0; i < n; i++) {
        int actual = 0, last = -1;
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j] && actual+1 > c[j]) {
                c[j] = actual+1;
                prev[j] = last;
            } else if (a[i] > b[j] && actual < c[j]) {
                actual = c[j];
                last = j;
            }
        }
    }

    int length = 0, index = -1;
    for (int j = 0; j < m; j++) {
        if (c[j] > length) {
            length = c[j];
            index = j;
        }
    }

    int len = length;
    while (index != -1) {
        seq[--len] = b[index];
        index = prev[index];
    }

    printf("length: %d\n", length);
    for (int i = 0; i < length; i++)
        printf("%d ", seq[i]);
    printf("\n");
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    scanf("%d", &m);
    for (int j = 0; j < m; j++)
        scanf("%d", &b[j]);

    lcis();
}

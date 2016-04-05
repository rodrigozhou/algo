#include <cstdio>
using namespace std;

#define MAXN 1000010

int a[MAXN], tmp[MAXN];

void merge(int l, int m, int r) {
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (a[i] < a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }
    while (i < m)
        tmp[k++] = a[i++];
    while (j < r)
        tmp[k++] = a[j++];
    for (k = l; k < r; k++)
        a[k] = tmp[k];
}

void merge_sort(int l, int r) {
    if (r - l > 1) {
        int m = (l + r)/2;;
        merge_sort(l, m);
        merge_sort(m, r);
        merge(l, m, r);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    merge_sort(0, n);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

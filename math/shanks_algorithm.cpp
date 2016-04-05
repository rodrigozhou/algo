/**
 * Shanks Baby-Step Giant-Step Algorithm
 */

#include <cstdio>
#include <cmath>
using namespace std;

#define MAXN 100010

/**
 * @return x such that a*x = 1 (mod n)
 */
int modinv(int a, int n) {
    int b = n;
    int x = 0, lastx = 1, aux;
    int q, r;
    while (b) {
        q = a / b;
        r = a % b;
        a = b; b = r;
        aux = x;
        x = lastx - q * x;
        lastx = aux;
    }
    while (lastx < 0)
        lastx += n;
    return lastx;
}

/**
 * @return x^e mod n
 */
int modpow(int x, int e, int n) {
    int ret = 1;
    while (e) {
        if (e & 1)
            ret = (ret * x) % n;
        x = (x * x) % n;
        e >>= 1;
    }
    return ret;
}

/**
 * @param   a   generator of group Z_n
 * @param   n   group Z_n
 * @return x such that a^x = b (mod n) or -1
 */
int shanks_algorithm(int a, int b, int n) {
    int m = ceil(sqrt(n));
    int table[MAXN];
    for (int i = 0; i < n; i++)
        table[i] = -1;
    int aux = 1;
    for (int j = 0; j < m; j++) {
        table[aux] = j;
        aux = (aux * a) % n;
    }
    aux = modpow(modinv(a, n), m, n);
    for (int i = 0; i < m; i++) {
        if (table[b] != -1)
            return i*m + table[b];
        b = (b * aux) % n;
    }
    return -1;
}

int main() {
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    printf("%d\n", shanks_algorithm(a, b, n));
}

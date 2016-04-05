/**
 * Miller-Rabin primality test
 *
 * This implementation is deterministic for n < 4,759,123,141
 */

#include <cstdio>

int powmod(int a, int e, int n) {
    int ret = 1;
    for (long long pow = a; e > 0; e >>= 1, pow = pow * pow % n)
        if (e & 1)
            ret = ret * pow % n;
    return ret;
}

int miller_rabin(int n, int a) {
    if (n <= 1) return 0;
    if (!(n & 1)) return n == 2;

    int d = n - 1, s = 0;
    while (!(d & 1)) {
        d >>= 1;
        s++;
    }

    int x = powmod(a, d, n);
    if (x == 1) return 1;

    for (int i = 0; i < s; i++) {
        if (x == 1) return 0;
        if (x == n-1) return 1;
        x = (long long)x * x % n;
    }

    return 0;
}

int isprime(int n) {
    if (n == 2 || n == 7 || n == 61) return 1;
    return miller_rabin(n, 2) && miller_rabin(n, 7) && miller_rabin(n, 61);
}

int main() {
}

/**
 * Miller-Rabin primality test
 *
 * This implementation is deterministic for n < 3,825,123,056,546,413,051
 */

long long multmod(long long a, long long b, long long mod) {
    long long ret = 0;
    int msb = 64 - __builtin_clzll(b);
    for (int bit = msb-1; bit >= 0; bit--) {
        ret <<= 1;
        if (ret >= mod) ret -= mod;
        if (b >> bit & 1) {
            ret += a;
            if (ret >= mod) ret -= mod;
        }
    }
    return ret;
}

long long powmod(long long a, long long e, long long mod) {
    long long ret = 1;
    for (a %= mod; e > 0; e >>= 1, a = multmod(a, a, mod))
        if (e & 1)
            ret = multmod(ret, a, mod);
    return ret;
}

int miller_rabin(long long n, int a) {
    if (n <= 1) return 0;
    if (n % 2 == 0) return n == 2;
    long long s = __builtin_ctzll(n-1), d = (n-1) >> s;
    long long x = powmod(a, d, n);
    if (x == 1) return 1;
    for (int i = 0; i < s; i++) {
        if (x == 1) return 0;
        if (x == n-1) return 1;
        x = multmod(x, x, n);
    }
    return 0;
}

int isprime(long long n) {
    const int a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (int i = 0; i < 9; i++) {
        if (n == a[i]) return 1;
        if (!miller_rabin(n, a[i])) return 0;
    }
    return 1;
}

int main() {
}

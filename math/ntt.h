#ifndef _NTT_H_
#define _NTT_H_

#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 1000005

typedef long long ll;

inline ll powmod(ll a, ll e, ll n) {
    ll ret = 1;
    while (e > 0) {
        if (e & 1)
            ret = (ret * a) % n;
        a = (a * a) % n;
        e >>= 1;
    }
    return ret;
}

inline ll invmod(ll a, ll p) {
    return powmod(a, p-2, p);
}

bool isp[4000000];
int lsp[400000], np;

void sieve(int n) {
    memset(isp, 0, sizeof(isp));
    for (int i = 3; i < n; i += 2)
        isp[i] = 1;
    for (ll i = 3, lim = sqrt(n); i < lim; i += 2) if (isp[i])
        for (ll j = i * i; j < n; j += i)
            isp[j] = 0;
    np = 0;
    lsp[np++] = 2;
    for (int i = 3; i < n; i += 2)
        if (isp[i])
            lsp[np++] = i;
}

int isprime(int p) {
    if (p < 4000000)
        return isp[p];
    for (int i = 0, lim = sqrt(p); lsp[i] <= lim; i++)
        if (p % lsp[i] == 0)
            return 0;
    return 1;
}

int prim_root(int p) {
    if (p == 2)
        return 1;
    vector<int> f;
    for (int i = 0, m = p-1; i < np && m > 1; i++) {
        if (m % lsp[i] == 0) {
            f.push_back(lsp[i]);
            while (m % lsp[i] == 0)
                m /= lsp[i];
        }
    }
    for (int i = 0; i < np; i++) {
        bool flag = 1;
        for (int j = 0; flag && j < f.size(); j++)
            flag = powmod(lsp[i], (p-1)/f[j], p) != 1;
        if (flag)
            return lsp[i];
    }
    return 0;
}

/**
 * Number Theoretic Transform: radix-2 Cooley-Tukey algorithm
 * @param   in      input with size n = 2^k
 * @param   inv     evaluate inverse transformation
 * @param   p       p is a prime st. n | p-1
 * @param   root    primitive root of p
 */
void ntt_radix2(vector<ll> &in, bool inv, ll p, ll root) {
    int n = in.size();
    for (int i = 0; i < n; i++) {
        in[i] %= p;
        if (in[i] < 0) in[i] += p;
    }

    // bit reversal
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(in[i], in[j]);
    }

    // ntt
    for (int len = 2, half = 1; len <= n; len <<= 1, half <<= 1) {
        ll wlen = powmod(inv ? invmod(root, p) : root, (p-1)/len, p);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < half; j++) {
                ll u = in[i+j], v = (w * in[i+j+half]) % p;
                in[i+j] = u+v < p ? u+v : u+v-p;
                in[i+j+half] = u-v >= 0 ? u-v : u-v+p;
                w = (w * wlen) % p;
            }
        }
    }

    if (inv) {
        ll inv_n = invmod(n, p);
        for (int i = 0; i < n; i++)
            in[i] = (inv_n * in[i]) % p;
    }
}

void convolve(vector<ll> &a1, vector<ll> &b1) {
    ll prime1 = 134348801, root1 = 3;
    ll prime2 = 537133057, root2 = 5;

    int n = a1.size();
    vector<ll> a2 = a1, b2 = b1;

    ntt_radix2(a1, 0, prime1, root1);
    ntt_radix2(b1, 0, prime1, root1);
    ntt_radix2(a2, 0, prime2, root2);
    ntt_radix2(b2, 0, prime2, root2);

    for (int i = 0; i < n; i++) {
        a1[i] = (a1[i] * b1[i]) % prime1;
        a2[i] = (a2[i] * b2[i]) % prime2;
    }

    ntt_radix2(a1, 1, prime1, root1);
    ntt_radix2(a2, 1, prime2, root2);

    // chinese remainder algorithm
    ll inv_prime1 = invmod(prime1, prime2);
    for (int i = 0; i < n; i++) {
        ll aux = ((a2[i] - a1[i]) * inv_prime1) % prime2;
        if (aux < 0) aux += prime2;
        a1[i] = a1[i] + aux * prime1;
    }
}

/**
 * Number Theoretic Transform: Bluestein algorithm
 * @param   in      input with size n
 * @param   p       p is prime st. 2*n | p-1 (p > 10^6 is recommended)
 * @param   root    primitive root of p
 */
void ntt_bluestein(vector<ll> &in, ll p, ll root) {
    int n = in.size();
    for (int i = 0; i < n; i++) {
        in[i] %= p;
        if (in[i] < 0) in[i] += p;
    }

    int m = 1;
    while (m < (n<<1))
        m <<= 1;

    vector<ll> a(m), b(m);

    ll w_h = powmod(root, (p-1)/(2*n), p);
    ll inv_w_h = invmod(w_h, p);
    for (int i = 0; i < n; i++) {
        a[i] = (in[i] * powmod(w_h, i*i, p)) % p;
        b[i] = powmod(inv_w_h, i*i, p);
        if (i) b[m-i] = b[i];
    }

    convolve(a, b);

    for (int i = 0; i < n; i++)
        in[i] = (powmod(w_h, i*i, p) * (a[i] % p)) % p;
}

#endif // _NTT_H_

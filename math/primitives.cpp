#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 1000000

int np, p[MAXN];
int lp[MAXN];

void sieve(int n) {
    for (int i = 2; i < n; i++)
        lp[i] = i;
    for (int i = 4; i < n; i += 2)
        lp[i] = 2;
    for (int i = 3; i*i < n; i += 2)
        if (lp[i] == i)
            for (int j = i*i; j < n; j += i)
                lp[j] = i;

    np = 0;
    p[np++] = 2;
    for (int i = 3; i < n; i += 2)
        if (lp[i] == i)
            p[np++] = i;
}

int nf, f[MAXN], e[MAXN];

void factor(int n) {
    nf = 0;
    for (int i = 0; n != 1 && p[i]*p[i] <= n; i++) {
        if (n % p[i] == 0) {
            f[nf] = p[i];
            e[nf] = 1;
            n /= p[i];
            while (n % p[i] == 0) {
                e[nf]++;
                n /= p[i];
            }
            nf++;
        }
    }
    if (n != 1) {
        f[nf] = n;
        e[nf] = 1;
        nf++;
    }
}

int _phi(int n) {
    int ret = 1;
    for (int i = 0; n != 1 && p[i]*p[i] <= n; i++) {
        if (n % p[i] == 0) {
            int pk = p[i];
            n /= p[i];
            while (n % p[i] == 0) {
                pk *= p[i];
                n /= p[i];
            }
            ret *= pk - pk/p[i];
        }
    }
    if (n != 1)
        ret *= n-1;
    return ret;
}

int phi[MAXN];

void build_phi(int n) {
    for (int i = 0; i < n; i++)
        phi[i] = i;
    for (int i = 2; i < n; i++) if (phi[i] == i)
        for (int j = i; j < n; j += i)
            phi[j] = phi[j] / i * (i-1);
}

int main() {
}

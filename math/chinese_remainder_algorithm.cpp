#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

typedef pair<int, int> tpii;

struct teq {
    // x = r (mod n)
    int r, n;
};

int qnt, n;
teq eqs[MAXN];

tpii egcd(int a, int b) {
    int x = 0, lastx = 1, auxx;
    int y = 1, lasty = 0, auxy;
    while (b) {
        int q = a / b, r = a % b;
        a = b, b = r;
        auxx = x;
        x = lastx - q*x, lastx = auxx;
        auxy = y;
        y = lasty - q*y, lasty = auxy;
    }
    return make_pair(lastx, lasty);
}

int chinese_remainder_algorithm() {
    int beta, sum = 0;
    for (int i = 0; i < qnt; i++) {
        beta = egcd(eqs[i].n, n/eqs[i].n).second;
        while (beta < 0)
            beta += eqs[i].n;
        sum += (eqs[i].r * beta * n/eqs[i].n) % n;
    }
    return sum;
}

int main() {
    scanf("%d", &qnt);
    n = 1;
    for (int i = 0; i < qnt; i++) {
        scanf("%d %d", &eqs[i].r, &eqs[i].n);
        n *= eqs[i].n;
    }
    printf("%d\n", chinese_remainder_algorithm());
}

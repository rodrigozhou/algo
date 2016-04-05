/**
 * Bignum implementation
 */

#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 10010;

struct bignum {
    char n[MAXN];
    int lenn;
    bignum () {
        strcpy(n, "0");
        lenn = 1;
    }
    int reverse_number(char *num) {
        int i = 0, j = strlen(num) - 1;
        char aux;
        while (num[j] == '0')
            j--;
        num[j+1] = '\0';
        while (i < j) {
            aux = num[i];
            num[i] = num[j];
            num[j] = aux;
            i++, j--;
        }
        return i+j+1;
    }
    int remove_leading_zeros(char *num) {
        int i = 0, j = 0;
        while (num[i] == '0')
            i++;
        if (i > 0) {
            while (num[i] != '\0') {
                num[j++] = num[i++];
            }
            num[j] = '\0';
        }
        return j;
    }
    bignum& operator= (const char *_n) {
        strcpy(n, _n);
        lenn = strlen(n);
        return *this;
    }
    bignum operator+ (const bignum &a) {
        bignum s;
        int in, ia, is, flag = 0;
        for (in = lenn-1, ia = a.lenn-1, is = 0; in >= 0 && ia >= 0; in--, ia--, is++) {
            s.n[is] = n[in] + a.n[ia] - '0' + flag;
            flag = 0;
            if (s.n[is] > '9') {
                s.n[is] -= 10;
                flag = 1;
            }
        }
        for ( ; in >= 0; in--, is++) {
            s.n[is] = n[in] + flag;
            flag = 0;
            if (s.n[is] > '9') {
                s.n[is] -= 10;
                flag = 1;
            }
        }
        for ( ; ia >= 0; ia--, is++) {
            s.n[is] = a.n[ia] + flag;
            flag = 0;
            if (s.n[is] > '9') {
                s.n[is] -= 10;
                flag = 1;
            }
        }
        if (flag > 0)
            s.n[is++] = '1';
        s.n[is] = '\0';
        s.lenn = reverse_number(s.n);
        return s;
    }
    bignum operator- (const bignum &a) {
        bignum s;
        int in, ia, is, flag = 0;
        for (in = lenn-1, ia = a.lenn-1, is = 0; in >= 0 && ia >= 0; in--, ia--, is++) {
            s.n[is] = n[in] - a.n[ia] + '0' - flag;
            flag = 0;
            if (s.n[is] < '0') {
                s.n[is] += 10;
                flag = 1;
            }
        }
        for ( ; in >= 0; in--, is++) {
            s.n[is] = n[in] - flag;
            flag = 0;
            if (s.n[is] < '0') {
                s.n[is] += 10;
                flag = 1;
            }
        }
        for ( ; ia >= 0; ia--, is++) {
            s.n[is] = a.n[ia] + flag;
            flag = 0;
            if (s.n[is] > '9') {
                s.n[is] -= 10;
                flag = 1;
            }
        }
        s.n[is] = '\0';
        s.lenn = reverse_number(s.n);
        return s;
    }
    bignum operator* (const int &k) {
        bignum s;
        int in, is, tmp, flag = 0;
        for (in = lenn-1, is = 0; in >= 0; in--, is++) {
            tmp = (n[in] - '0')*k + flag;
            flag = tmp/10;
            tmp %= 10;
            s.n[is] = '0' + tmp;
        }
        while (flag > 0) {
            s.n[is++] = '0' + flag % 10;
            flag /= 10;
        }
        s.n[is] = '\0';
        s.lenn = reverse_number(s.n);
        return s;
    }
    bignum operator/ (const int &k) {
        bignum s;
        int in, is, mod = 0;
        for (in = 0, is = 0; in < lenn; in++, is++) {
            mod = 10*mod + n[in] - '0';
            if (mod >= k) {
                s.n[is] = '0' + mod/k;
                mod %= k;
            }
            else {
                s.n[is] = '0';
            }
        }
        s.n[is] = '\0';
        s.lenn = remove_leading_zeros(s.n);
        return s;
    }
    int operator% (const int &k) {
        int in, mod = 0;
        for (in = 0; in < lenn; in++) {
            mod = 10*mod + n[in] - '0';
            if (mod >= k) {
                mod %= k;
            }
        }
        return mod;
    }
};

int main() {
    return 0;
}

/**
 * BigNum
 * Author: Neal Wu
 *
 * Support for negative numbers and fast multiplication (Rodrigo Zhou)
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <limits>
#include <algorithm>
#include <vector>
#include "fft.h"
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int MAXD = 1005, DIG = 9, BASE = 1000000000;
const ull BOUND = numeric_limits<ull>::max() - (ull) BASE * BASE;

struct bignum {
    int D, digits[MAXD / DIG + 2];
    int sign;

    inline void trim() {
        while (D > 1 && digits[D - 1] == 0)
            D--;
    }

    inline void init(ll x) {
        memset(digits, 0, sizeof(digits));
        D = 0;

        if (x < 0) {
            sign = -1;
            x = -x;
        }
        else {
            sign = 1;
        }

        do {
            digits[D++] = x % BASE;
            x /= BASE;
        } while (x > 0);
    }

    inline bignum(ll x) {
        init(x);
    }

    inline bignum(int x = 0) {
        init(x);
    }

    inline bignum(const char *s) {
        memset(digits, 0, sizeof(digits));

        if (s[0] == '-') {
            sign = -1;
            s++;
        }
        else {
            sign = 1;
        }

        int len = strlen(s), first = (len + DIG - 1) % DIG + 1;
        D = (len + DIG - 1) / DIG;

        for (int i = 0; i < first; i++)
            digits[D - 1] = digits[D - 1] * 10 + s[i] - '0';

        for (int i = first, d = D - 2; i < len; i += DIG, d--)
            for (int j = i; j < i + DIG; j++)
                digits[d] = digits[d] * 10 + s[j] - '0';

        trim();
    }

    inline char *str() {
        trim();
        char *buf = new char[DIG * D + 2];
        int pos = 0, d = digits[D - 1];

        if (sign == -1)
            buf[pos++] = '-';

        do {
            buf[pos++] = d % 10 + '0';
            d /= 10;
        } while (d > 0);

        reverse(buf + (sign == -1 ? 1 : 0), buf + pos);

        for (int i = D - 2; i >= 0; i--, pos += DIG) {
            for (int j = DIG - 1, t = digits[i]; j >= 0; j--) {
                buf[pos + j] = t % 10 + '0';
                t /= 10;
            }
        }

        buf[pos] = '\0';
        return buf;
    }

    inline bool operator<(const bignum &o) const {
        if (sign != o.sign)
            return sign < o.sign;

        if (D != o.D)
            return sign * D < o.sign * o.D;

        for (int i = D - 1; i >= 0; i--)
            if (digits[i] != o.digits[i])
                return sign * digits[i] < o.sign * o.digits[i];

        return false;
    }

    inline bool operator>(const bignum &o) const {
        if (sign != o.sign)
            return sign > o.sign;

        if (D != o.D)
            return sign * D > o.sign * o.D;

        for (int i = D - 1; i >= 0; i--)
            if (digits[i] != o.digits[i])
                return sign * digits[i] > o.sign * o.digits[i];

        return false;
    }

    inline bool operator==(const bignum &o) const {
        if (sign != o.sign)
            return false;

        if (D != o.D)
            return false;

        for (int i = 0; i < D; i++)
            if (digits[i] != o.digits[i])
                return false;

        return true;
    }

    inline bignum operator<<(int p) const {
        bignum temp;
        temp.D = D + p;

        for (int i = 0; i < D; i++)
            temp.digits[i + p] = digits[i];

        for (int i = 0; i < p; i++)
            temp.digits[i] = 0;

        return temp;
    }

    inline bignum operator>>(int p) const {
        bignum temp;
        temp.D = D - p;

        for (int i = 0; i < D - p; i++)
            temp.digits[i] = digits[i + p];

        for (int i = D - p; i < D; i++)
            temp.digits[i] = 0;

        return temp;
    }

    inline bignum range(int a, int b) const {
        bignum temp = 0;
        temp.D = b - a;

        for (int i = 0; i < temp.D; i++)
            temp.digits[i] = digits[i + a];

        return temp;
    }

    inline bignum abs() const {
        bignum temp = *this;
        temp.sign = 1;
        return temp;
    }

    inline bignum operator+(const bignum &o) const {
        if (sign != o.sign) {
            if (sign == 1)
                return *this - o.abs();
            return o - this->abs();
        }

        bignum sum = o;
        int carry = 0;

        for (sum.D = 0; sum.D < D || carry > 0; sum.D++) {
            sum.digits[sum.D] += (sum.D < D ? digits[sum.D] : 0) + carry;

            if (sum.digits[sum.D] >= BASE) {
                sum.digits[sum.D] -= BASE;
                carry = 1;
            }
            else {
                carry = 0;
            }
        }

        sum.D = max(sum.D, o.D);
        sum.trim();
        return sum;
    }

    inline bignum operator-(const bignum &o) const {
        if (sign != o.sign) {
            if (sign == 1)
                return *this + o.abs();
            return -(this->abs() + o);
        }
        else if (sign == -1) {
            return o.abs() - this->abs();
        }

        bignum diff, temp;

        if (o > *this) {
            diff = o;
            diff.sign = -1;
            temp = *this;
        }
        else {
            diff = *this;
            temp = o;
        }

        for (int i = 0, carry = 0; i < temp.D || carry > 0; i++) {
            diff.digits[i] -= (i < temp.D ? temp.digits[i] : 0) + carry;

            if (diff.digits[i] < 0) {
                diff.digits[i] += BASE;
                carry = 1;
            }
            else {
                carry = 0;
            }
        }

        diff.trim();
        return diff;
    }

    inline bignum operator-() const {
        bignum temp = *this;
        temp.sign = -temp.sign;
        return temp;
    }

    inline bignum operator*(const bignum &o) const {
        bignum prod = 0;
        ull sum = 0, carry = 0;

        for (prod.D = 0; prod.D < D + o.D - 1 || carry > 0; prod.D++) {
            sum = carry % BASE;
            carry /= BASE;

            for (int j = max(prod.D - o.D + 1, 0); j <= min(D - 1, prod.D); j++) {
                sum += (ull) digits[j] * o.digits[prod.D - j];

                if (sum >= BOUND) {
                    carry += sum / BASE;
                    sum %= BASE;
                }
            }

            carry += sum / BASE;
            prod.digits[prod.D] = sum % BASE;
        }

        prod.sign = sign * o.sign;
        prod.trim();
        return prod;
    }

    inline double double_div(const bignum &o) const {
        double val = 0, oval = 0;
        int num = 0, onum = 0;

        for (int i = D - 1; i >= max(D - 3, 0); i--, num++)
            val = val * BASE + digits[i];

        for (int i = o.D - 1; i >= max(o.D - 3, 0); i--, onum++)
            oval = oval * BASE + o.digits[i];

        return (sign * o.sign) * val / oval * (D - num > o.D - onum ? BASE : 1);
    }

    inline pair<bignum, bignum> divmod(const bignum &o) const {
        if (sign != o.sign) {
            pair<bignum, bignum> p = (this->abs()).divmod(o.abs());
            p.first.sign = -1;
            p.second.sign = sign;
            return p;
        }
        else if (sign == -1) {
            pair<bignum, bignum> p = (this->abs()).divmod(o.abs());
            p.second.sign = sign;
            return p;
        }

        bignum quot = 0, rem = *this, temp;

        for (int i = D - o.D; i >= 0; i--) {
            temp = rem.range(i, rem.D);
            int div = (int) temp.double_div(o);
            bignum mult = o * div;

            while (div > 0 && temp < mult) {
                mult = mult - o;
                div--;
            }

            while (div + 1 < BASE && !(temp < mult + o)) {
                mult = mult + o;
                div++;
            }

            rem = rem - (o * div << i);

            if (div > 0) {
                quot.digits[i] = div;
                quot.D = max(quot.D, i + 1);
            }
        }

        quot.trim();
        rem.trim();
        return make_pair(quot, rem);
    }

    inline bignum operator/(const bignum &o) const {
        return divmod(o).first;
    }

    inline bignum operator%(const bignum &o) const {
        return divmod(o).second;
    }

    inline bignum power(int exp) const {
        bignum p = 1, temp = *this;

        while (exp > 0) {
            if (exp & 1) p = p * temp;
            if (exp > 1) temp = temp * temp;
            exp >>= 1;
        }

        return p;
    }
};

inline bignum gcd(bignum a, bignum b) {
    bignum t;
    while (!(b == 0)) {
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}

/**
 * Multiplication using FFT
 * For good precision, use base <= 10^5
 */
inline bignum fastMul(const bignum &a, const bignum &b) {
    int sz = 1 << (32 - __builtin_clz(a.D + b.D));
    vector<pt> ain(sz), bin(sz);
    for (int i = 0; i < a.D; i++)
        ain[i] = i < a.D;
    for (int i = 0; i < b.D; i++)
        bin[i] = i < b.D;
    convolve(ain, bin);
    bignum ret = 0;
    ret.D = a.D + b.D;
    long long carry = 0;
    for (int i = 0; i < ret.D; i++) {
        long long x = (long long) floor(ain[i].real() + 0.5) + carry;
        ret.digits[i] = x % BASE;
        carry = x / BASE;
    }
    ret.trim();
    ret.sign = a.sign * b.sign;
    return ret;
}

int main() {
    int a, b;
    char op;
    bignum x, y;
    while (scanf("%d %c %d", &a, &op, &b) != EOF) {
        x = a, y = b;
        printf("%d %c %d = ", a, op, b);
        if (op == '+')
            printf("%s\n", (x+y).str());
        else if (op == '-')
            printf("%s\n", (x-y).str());
        else if (op == '*')
            printf("%s\n", (x*y).str());
        else if (op == '/')
            printf("%s\n", (x/y).str());
        else if (op == '%')
            printf("%s\n", (x%y).str());
        else if (op == '^')
            printf("%s\n", (x.power(b)).str());
    }
}

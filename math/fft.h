#ifndef _FFT_H_
#define _FFT_H_

#include <cmath>
#include <algorithm>
#include <complex>
#include <vector>
using namespace std;

typedef complex<long double> pt;

void fft_radix2(vector<pt> &in, bool inv) {
    int n = in.size();

    // bit reversal
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(in[i], in[j]);
    }

    // fft
    for (int len = 2, half = 1; len <= n; len <<= 1, half <<= 1) {
        long double p = (inv ? 1 : -1) * 2 * M_PI / len;
        pt wlen = pt(cosl(p), sinl(p));
        for (int i = 0; i < n; i += len) {
            pt w = 1;
            for (int j = 0; j < half; j++) {
                pt u = in[i+j], v = w * in[i+j+half];
                in[i+j] = u + v;
                in[i+j+half] = u - v;
                w *= wlen;
            }
        }
    }

    if (inv) {
        for (int i = 0; i < n; i++)
            in[i] /= n;
    }
}

void convolve(vector<pt> &a, vector<pt> &b) {
    int n = a.size();

    fft_radix2(a, 0);
    fft_radix2(b, 0);

    for (int i = 0; i < n; i++)
        a[i] *= b[i];

    fft_radix2(a, 1);
}

void fft_bluestein(vector<pt> &in, bool inv) {
    int n = in.size(), m = 1;
    while (m < (n<<1))
        m <<= 1;

    vector<pt> a(m), b(m), exptb(n);

    for (int i = 0; i < n; i++)
        exptb[i] = exp(pt(0, (inv ? 1 : -1) * M_PI * (i*i) / n));

    for (int i = 0; i < m; i++) {
        a[i] = i < n ? in[i] * exptb[i] : 0;
        b[i] = i < n || m-i < n ? conj(exptb[min(i, m-i)]) : 0;
    }

    convolve(a, b);

    for (int i = 0; i < n; i++)
        in[i] = a[i] * exptb[i];
}

void fft(vector<pt> &in, bool inv) {
    int n = in.size();
    if (n & (n-1))
        fft_bluestein(in, inv);
    else
        fft_radix2(in, inv);
}

#endif // _FFT_H_

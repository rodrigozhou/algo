/**
 * Manacher's Algorithm
 *
 * Compute the lengths of all palindromic substrings of a string
 *
 * Complexity: O(n)
 */

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 100005

char s[MAXN];
int p[2*MAXN]; // length of the palindrome centered at position (i-1)/2;

void manacher() {
    int m = 0;
    char t[2*MAXN];
    for (int i = 0; s[i]; i++) {
        t[m++] = '#';
        t[m++] = s[i];
        p[i] = 0;
    }
    t[m++] = '#';

    int c = 0, r = 0;
    for (int i = 0; i < m; i++) {
        p[i] = r > i ? min(r-i, p[2*c-i]) : i & 1;
        while (0 <= i-p[i]-1 && i+p[i]+1 < m && t[i-p[i]-1] == t[i+p[i]+1])
            p[i] += 2;
        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }
}

int main() {
    gets(s);
    manacher();
}

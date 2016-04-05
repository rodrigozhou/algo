/**
 * Z Algorithm
 * Complexity: O(n)
 *
 * Input  : string s
 * Output : z[i], longest common prefix of s with his suffix starting at i
 */

#include <cstdio>

void z_algorithm(char *s, int *z) {
    int l = 0, r = 0;
    for (int i = 0; s[i]; i++) {
        if (i > r) {
            l = r = i;
            for (; s[r] == s[r-l]; r++);
            z[i] = r-- - l;
        }
        else if (z[i-l] < r-i+1) {
            z[i] = z[i-l];
        }
        else {
            l = i;
            for (r++; s[r] == s[r-l]; r++);
            z[i] = r-- - l;
        }
    }
}

int main() {
}

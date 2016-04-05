#include <cstdio>
#include <cstring>
using namespace std;

#define MAXS 1000010

int pi[MAXS];

void kmp_table(char *pattern, int m) {
    pi[0] = -1;
    for (int i = 1, k = -1; i < m; i++) {
        while (k >= 0 && pattern[k+1] != pattern[i])
            k = pi[k];
        if (pattern[k+1] == pattern[i])
            k++;
        pi[i] = k;
    }
}

void kmp_search(char *text, char *pattern) {
    int n = strlen(text), m = strlen(pattern);
    kmp_table(pattern, m);
    for (int i = 0, k = -1; i < n; i++) {
        while (k >= 0 && pattern[k+1] != text[i])
            k = pi[k];
        if (pattern[k+1] == text[i])
            k++;
        if (k+1 == m) {
            printf("Match at %d\n", i-k);
            k = pi[k];
        }
    }
}

int main() {
    char s1[MAXS], s2[MAXS];
    gets(s1);
    gets(s2);
    kmp_search(s1, s2);
}

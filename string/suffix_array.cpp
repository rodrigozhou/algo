/**
 * Suffix Array
 * O(n log n)
 * "Suffix array: A new method for on-line string searches"
 * (Udi Manber and Gene Myers)
 *
 * Longest Common Prefix
 * O(n)
 * "Linear-Time Longest-Common-Prefix Computation in Suffix Arrays
 * and Its Applications"
 * (Toru Kasai, Gunho Lee, Hiroki Arimura, Setsuo Arikawa and Kunsoo Park)
 *
 * Code from TopCoder:
 * http://apps.topcoder.com/forums/?module=RevisionHistory&messageID=1171511
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 100005

//Output:
// pos  = The suffix array. Contains the n suffixes of str sorted in
//        lexicographical order. Each suffix is represented as a
//        single integer (the position of str where it starts).
// rank = The inverse of the suffix array.
//        rank[i] = the index of the suffix str[i..n) in the pos array.
//        (In other words, pos[i] = k <==> rank[k] = i)
//        With this array, you can compare two suffixes in O(1):
//        Suffix str[i..n) is smaller than str[j..n) iff rank[i] < rank[j]

int n;
char str[MAXN];
int rank[MAXN], pos[MAXN];
int cnt[MAXN], next[MAXN];
bool bh[MAXN], b2h[MAXN];

bool cmp(int a, int b) {
    return str[a] < str[b];
}

void suffix_array() {
    for (int i = 0; i < n; i++)
        pos[i] = i;
    sort(pos, pos+n, cmp);

    for (int i = 0; i < n; i++) {
        bh[i] = (i == 0 || str[pos[i]] != str[pos[i-1]]);
        b2h[i] = 0;
    }

    for (int h = 1; h < n; h <<= 1) {
        int buckets = 0;
        for (int i = 0, j; i < n; i = j) {
            j = i + 1;
            while (j < n && !bh[j])
                j++;
            next[i] = j;
            buckets++;
        }
        if (buckets == n)
            break;

        for (int i = 0; i < n; i = next[i]) {
            cnt[i] = 0;
            for (int j = i; j < next[i]; j++)
                rank[pos[j]] = i;
        }

        cnt[rank[n-h]]++;
        b2h[rank[n-h]] = 1;
        for (int i = 0; i < n; i = next[i]) {
            for (int j = i; j < next[i]; j++) {
                int s = pos[j] - h;
                if (s >= 0) {
                    int head = rank[s];
                    rank[s] = head + cnt[head]++;
                    b2h[rank[s]] = 1;
                }
            }
            for (int j = i; j < next[i]; j++) {
                int s = pos[j] - h;
                if (s >= 0 && b2h[rank[s]]) {
                    for (int k = rank[s] + 1; !bh[k] && b2h[k]; k++)
                        b2h[k] = 0;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            pos[rank[i]] = i;
            bh[i] |= b2h[i];
        }
    }
    for (int i = 0; i < n; i++)
        rank[pos[i]] = i;
}

int height[MAXN];

void getHeight() {
    height[0] = 0;
    for (int i = 0, h = 0; i < n; i++) {
        if (rank[i] > 0) {
            int j = pos[rank[i] - 1];
            while (i + h < n && j + h < n && str[i+h] == str[j+h])
                h++;
            height[rank[i]] = h;
            if (h > 0)
                h--;
        }
    }
}

int main() {
    scanf("%s", str);
    n = strlen(str);
    suffix_array();
    getHeight();
}

/**
 * Aho-Corasick String Matching Algorithm
 */

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define MAX 1000005

struct Node {
    int adj[26];
    int end, fail;

    void init() {
        memset(adj, -1, sizeof(adj));
        end = 0;
        fail = -1;
    }
};

int next_id;
Node trie[MAX];

void init() {
    trie[0].init();
    next_id = 1;
}

void add_word(const char *word) {
    int node = 0;
    for (int i = 0; word[i]; i++) {
        int &aux = trie[node].adj[word[i]-'a'];
        if (aux == -1) {
            trie[next_id].init();
            aux = next_id++;
        }
        node = aux;
    }
    trie[node].end = 1;
}

void build() {
    queue<int> q;
    trie[0].fail = -1;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int c = 0; c < 26; c++) {
            if (trie[u].adj[c] == -1) continue;
            int v = trie[u].adj[c];
            q.push(v);
            int f = trie[u].fail;
            while (f >= 0 && trie[f].adj[c] == -1)
                f = trie[f].fail;
            f = f >= 0 ? trie[f].adj[c] : 0;
            trie[v].fail = f;
        }
    }
}

void search(const char *text) {
    int node = 0;
    for (int i = 0; text[i]; i++) {
        while (node >= 0 && trie[node].adj[text[i]-'a'] == -1)
            node = trie[node].fail;
        node = node >= 0 ? trie[node].adj[text[i]-'a'] : 0;
        for (int f = node; f > 0; f = trie[f].fail) {
            if (trie[f].end) {
                // do something with a match ending at position i
            }
        }
    }
}

int main() {
    init();
    add_word("dictionary");
    build();
    search("text");
}

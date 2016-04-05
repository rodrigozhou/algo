/**
 * Aho-Corasick String Matching Algorithm
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
using namespace std;

#define mp make_pair
#define fi first
#define se second

typedef pair<int, int> pii;

#define MAX 1000005

struct Node {
    map<char, int> adj;
    int fail;
    pii match;
    int next;

    void init() {
        adj.clear();
        fail = -1;
        match = mp(-1, -1);
        next = -1;
    }

    int getChild(const char &c) {
        map<char, int>::iterator it = adj.find(c);
        if (it != adj.end())
            return it->second;
        return -1;
    }
};

int qntNodes, qntPatts;
Node trie[MAX];

void init() {
    trie[0].init();
    qntNodes = 1;
    qntPatts = 0;
}

void addWord(const char *word) {
    int node = 0, aux = -1;
    for (int i = 0; word[i]; i++) {
        aux = trie[node].getChild(word[i]);
        if (aux == -1) {
            trie[qntNodes].init();
            aux = qntNodes++;
            trie[node].adj[word[i]] = aux;
        }
        node = aux;
    }
    trie[node].match = mp(qntPatts++, strlen(word));
}

void build() {
    queue<int> q;
    map<char, int>::iterator it;

    trie[0].fail = -1;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (it = trie[u].adj.begin(); it != trie[u].adj.end(); it++) {
            int v = it->second;
            char c = it->first;
            q.push(v);

            int f = trie[u].fail;
            while (f >= 0 && trie[f].getChild(c) == -1)
                f = trie[f].fail;
            f = f >= 0 ? trie[f].getChild(c) : 0;
            trie[v].fail = f;
            trie[v].next = trie[f].match.fi >= 0 ? f : trie[f].next;
        }
    }
}

void search(const char *text) {
    int node = 0;
    for (int i = 0; text[i]; i++) {
        while (node >= 0 && trie[node].getChild(text[i]) == -1)
            node = trie[node].fail;
        node = node >= 0 ? trie[node].getChild(text[i]) : 0;

        int aux = node;
        while (aux >= 0) {
            if (trie[aux].match.fi >= 0) {
                // do something with the match
                printf("patt: %d, pos: %d\n",
                        trie[aux].match.fi,
                        i - trie[aux].match.se + 1);
            }
            aux = trie[aux].next;
        }
    }
}

int main() {
    init();
    addWord("take");
    addWord("fast");
    addWord("soft");
    addWord("ake");
    addWord("e");
    build();
    puts("takeso fasofast fassofatake sosso sofastake so");
    search("takeso fasofast fassofatake sosso sofastake so");
}

/**
 * Treap
 *
 * Problems: SPOJ/ORDERSET, CODECHEF/FURGRAPH
 */

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

#define MAX 200005

struct Node {
    int x, p, cnt;
    Node *l, *r;

    Node() {}
    Node(int x, int p, Node *l, Node *r) : x(x), p(p), l(l), r(r) {}
};

int next_id;
Node data[MAX];
Node *tree, *null;

void init() {
    data[0].cnt = 0;
    null = &data[0];
    tree = null;
    next_id = 1;
}

Node* new_node(int k) {
    data[next_id] = Node(k, rand(), null, null);
    data[next_id].cnt = 1;
    return &data[next_id++];
}

void refresh(Node *t) {
    if (t != null) {
        t->cnt = t->l->cnt + t->r->cnt + 1;
    }
}

// split treap 't' into treaps 'a' and 'b' such that
// 'a' contains all nodes with x < k
void split(Node* &t, int k, Node* &a, Node* &b) {
    if (t == null) {
        a = b = null;
    }
    else if (t->x < k) {
        Node *aux;
        split(t->r, k, aux, b);
        t->r = aux;
        refresh(t);
        a = t;
    }
    else {
        Node *aux;
        split(t->l, k, a, aux);
        t->l = aux;
        refresh(t);
        b = t;
    }
}

// merge treaps 'a' and 'b'
// keys of 'a' are smaller than keys of 'b'
Node* merge(Node* &a, Node* &b) {
    if (a == null)
        return b;
    if (b == null)
        return a;
    if (a->p < b->p) {
        Node* aux = merge(a->r, b);
        a->r = aux;
        refresh(a);
        return a;
    }
    else {
        Node* aux = merge(a, b->l);
        b->l = aux;
        refresh(b);
        return b;
    }
}

bool find(Node* t, int k) {
    if (t == null)
        return false;
    if (k < t->x)
        return find(t->l, k);
    if (k > t->x)
        return find(t->r, k);
    return true;
}

bool insert(Node* &t, int k) {
    if (find(t, k))
        return false;
    Node *a, *b, *c, *d;
    split(t, k, a, b);
    c = new_node(k);
    d = merge(a, c);
    t = merge(d, b);
    return true;
}

bool erase(Node* &t, int k) {
    if (!find(t, k))
        return false;
    Node *a, *b, *c, *d;
    split(t, k, a, b);
    split(b, k+1, c, d);
    t = merge(a, d);
    return true;
}

// return the kth smallest value in 't'
int kth_element(Node* t, int k) {
    if (k <= t->l->cnt)
        return kth_element(t->l, k);
    else if (k == t->l->cnt + 1)
        return t->x;
    else
        return kth_element(t->r, k - t->l->cnt - 1);
}

// return the number of elements in 't' smaller than 'k'
int count(Node* t, int k) {
    if (t == null)
        return 0;
    if (k <= t->x)
        return count(t->l, k);
    else
        return 1 + t->l->cnt + count(t->r, k);
}

int main() {
    srand(time(NULL));
    init();
    int q;
    scanf("%d", &q);
    while (q--) {
        char op;
        int x;
        scanf(" %c %d", &op, &x);
        if (op == 'I')
            insert(tree, x);
        else if (op == 'D')
            erase(tree, x);
        else if (op == 'C')
            printf("%d\n", count(tree, x));
        else {
            if (x > tree->cnt)
                puts("invalid");
            else
                printf("%d\n", kth_element(tree, x));
        }
    }
}

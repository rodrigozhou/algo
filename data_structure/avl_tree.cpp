/**
 * AVL Tree
 *
 * Problems: SPOJ/ORDERSET
 */

#include <cstdio>
#include <algorithm>
using namespace std;

struct Node {
    int x, h;
    Node *l, *r;
    int size;

    Node (int x = 0) : x(x), h(0), l(NULL), r(NULL), size(0) {}

    Node (int x, Node *l, Node *r) : x(x), l(l), r(r) {
        update();
    }

    void update() {
        h = max(l->h, r->h) + 1;
        size = l->size + r->size + 1;
    }
};

Node *nil = new Node();
Node *root;

void init() {
    nil->l = nil->r = nil;
    nil->h = nil->size = 0;
    root = nil;
}

Node* rot_r(Node *t) {
    Node *l = t->l;
    t->l = l->r;
    l->r = t;
    t->update();
    l->update();
    return l;
}

Node* rot_l(Node *t) {
    Node *r = t->r;
    t->r = r->l;
    r->l = t;
    t->update();
    r->update();
    return r;
}

Node* fix(Node *t) {
    if (t->l->h - t->r->h > 1) {
        if (t->l->l->h > t->l->r->h) {
            t = rot_r(t);
        }
        else {
            t->l = rot_l(t->l);
            t = rot_r(t);
        }
    }
    else if (t->l->h - t->r->h < -1) {
        if (t->r->r->h > t->r->l->h) {
            t = rot_l(t);
        }
        else {
            t->r = rot_r(t->r);
            t = rot_l(t);
        }
    }
    t->update();
    return t;
}

Node* insert(Node *t, int x) {
    if (t == nil)
        return new Node(x, nil, nil);
    if (x == t->x)
        return t;
    if (x < t->x)
        t->l = insert(t->l, x);
    else
        t->r = insert(t->r, x);
    t = fix(t);
    return t;
}

Node* erase(Node *t, int x) {
    if (t == nil)
        return t;
    if (x < t->x)
        t->l = erase(t->l, x);
    else if (x > t->x)
        t->r = erase(t->r, x);
    else {
        if (t->l == nil)
            return t->r;
        if (t->r == nil)
            return t->l;
        Node *a = t->r;
        while (a->l != nil) a = a->l;
        t->x = a->x;
        t->r = erase(t->r, a->x);
    }
    t = fix(t);
    return t;
}

// return the kth smallest value in 't'
int kth(Node *t, int k) {
    if (t->l->size + 1 == k)
        return t->x;
    if (k <= t->l->size)
        return kth(t->l, k);
    return kth(t->r, k - t->l->size - 1);
}

// return the number of elements int 't' smaller than 'x'
int count(Node *t, int x) {
    if (t == nil)
        return 0;
    if (x <= t->x)
        return count(t->l, x);
    return 1 + t->l->size + count(t->r, x);
}

int main() {
    init();
    int q, x;
    scanf("%d", &q);
    while (q--) {
        char op;
        scanf(" %c %d", &op, &x);
        if (op == 'I')
            root = insert(root, x);
        else if (op == 'D')
            root = erase(root, x);
        else if (op == 'C')
            printf("%d\n", count(root, x));
        else {
            if (x > root->size)
                puts("invalid");
            else
                printf("%d\n", kth(root, x));
        }
    }
}

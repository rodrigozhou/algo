/**
 * Treap
 *
 * Problems: SPOJ/ORDERSET
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
using namespace std;

#define INF 0x3f3f3f3f

struct TreapNode {
    int key, pri, cnt;
    TreapNode *left, *right, *parent;

    TreapNode(int key = 0, int pri = 0)
        : key(key), pri(pri), cnt(1), left(NULL), right(NULL), parent(NULL) {
    }
};

struct Treap {
    TreapNode *root;

    Treap() : root(NULL) {}

    void rot_right(TreapNode *u) {
        TreapNode *w = u->left, *p = u->parent;
        w->parent = p;
        if (p != NULL) {
            if (p->left == u) p->left = w;
            else p->right = w;
        }
        u->left = w->right;
        if (u->left)
            u->left->parent = u;
        u->parent = w;
        w->right = u;
        if (root == u)
            root = w;
        u->cnt = 1;
        if (u->left) u->cnt += u->left->cnt;
        if (u->right) u->cnt += u->right->cnt;
        w->cnt = 1;
        if (w->left) w->cnt += w->left->cnt;
        if (w->right) w->cnt += w->right->cnt;
    }

    void rot_left(TreapNode *u) {
        TreapNode *w = u->right, *p = u->parent;
        w->parent = p;
        if (p != NULL) {
            if (p->left == u) p->left = w;
            else p->right = w;
        }
        u->right = w->left;
        if (u->right)
            u->right->parent = u;
        u->parent = w;
        w->left = u;
        if (root == u)
            root = w;
        u->cnt = 1;
        if (u->left) u->cnt += u->left->cnt;
        if (u->right) u->cnt += u->right->cnt;
        w->cnt = 1;
        if (w->left) w->cnt += w->left->cnt;
        if (w->right) w->cnt += w->right->cnt;
    }

    void insert(int key) {
        TreapNode *u = new TreapNode(key, random());

        TreapNode *cur = root, *prev = NULL;
        while (cur && cur->key != key) {
            prev = cur;
            if (key < cur->key)
                cur = cur->left;
            else
                cur = cur->right;
        }
        if (cur) return;

        u->parent = prev;
        if (prev) {
            if (key < prev->key)
                prev->left = u;
            else
                prev->right = u;
            while (prev) {
                prev->cnt++;
                prev = prev->parent;
            }
        }
        else {
            root = u;
        }

        while (u->parent && u->parent->pri > u->pri) {
            if (u->parent->left == u)
                rot_right(u->parent);
            else
                rot_left(u->parent);
        }
    }

    void remove(int key) {
        TreapNode *u = root;
        while (u && u->key != key) {
            if (key < u->key)
                u = u->left;
            else
                u = u->right;
        }
        if (!u) return;

        while (u->left || u->right) {
            if (!u->left)
                rot_left(u);
            else if (!u->right)
                rot_right(u);
            else if (u->left->pri < u->right->pri)
                rot_right(u);
            else
                rot_left(u);
        }

        if (u->parent) {
            if (u->parent->left == u) u->parent->left = NULL;
            else u->parent->right = NULL;
            for (TreapNode *cur = u->parent; cur; cur = cur->parent)
                cur->cnt--;
        }
        else {
            root = NULL;
        }
        delete u;
    }

    int count_lt(int val) {
        int ret = 0;
        TreapNode *cur = root;
        while (cur) {
            if (cur->key == val) {
                if (cur->left)
                    ret += cur->left->cnt;
                break;
            }
            if (cur->key < val) {
                if (cur->left)
                    ret += cur->left->cnt;
                ret++;
                cur = cur->right;
            }
            else {
                cur = cur->left;
            }
        }
        return ret;
    }
};

int main() {
    srand(time(NULL));
    Treap tree;
    int q;
    scanf("%d", &q);
    while (q--) {
        char c;
        int x;
        scanf(" %c %d", &c, &x);
        if (c == 'I')
            tree.insert(x);
        else if (c == 'D')
            tree.remove(x);
        else if (c == 'C')
            printf("%d\n", tree.count_lt(x));
        else {
            int lo = -INF, hi = INF;
            while (lo < hi) {
                int mi = (lo + hi + 1) / 2;
                int cnt = tree.count_lt(mi);
                if (cnt < x)
                    lo = mi;
                else
                    hi = mi - 1;
            }
            if (-INF < lo && lo < INF)
                printf("%d\n", lo);
            else
                puts("invalid");
        }
    }
}

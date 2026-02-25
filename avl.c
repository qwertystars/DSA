#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int k;
    struct node *l, *r;
    int h;
} node;

int ht(node *n) { return n ? n->h : 0; }
int mx(int a, int b) { return a > b ? a : b; }

node *mk(int k) {
    node *n = malloc(sizeof(node));
    n->k = k;
    n->l = n->r = NULL;
    n->h = 1;
    return n;
}

int bal(node *n) { return n ? ht(n->l) - ht(n->r) : 0; }

node *rr(node *y) {
    node *x = y->l, *t = x->r;
    x->r = y;
    y->l = t;
    y->h = mx(ht(y->l), ht(y->r)) + 1;
    x->h = mx(ht(x->l), ht(x->r)) + 1;
    return x;
}

node *lr(node *x) {
    node *y = x->r, *t = y->l;
    y->l = x;
    x->r = t;
    x->h = mx(ht(x->l), ht(x->r)) + 1;
    y->h = mx(ht(y->l), ht(y->r)) + 1;
    return y;
}

node *ins(node *n, int k) {
    if (!n) return mk(k);

    if (k < n->k)      n->l = ins(n->l, k);
    else if (k > n->k)  n->r = ins(n->r, k);
    else                 return n;

    n->h = 1 + mx(ht(n->l), ht(n->r));
    int b = bal(n);

    if (b > 1 && k < n->l->k)       return rr(n);
    if (b < -1 && k > n->r->k)      return lr(n);
    if (b > 1 && k > n->l->k)       { n->l = lr(n->l); return rr(n); }
    if (b < -1 && k < n->r->k)      { n->r = rr(n->r); return lr(n); }

    return n;
}

node *minv(node *n) {
    while (n->l) n = n->l;
    return n;
}

node *del(node *r, int k) {
    if (!r) return r;

    if (k < r->k)       r->l = del(r->l, k);
    else if (k > r->k)  r->r = del(r->r, k);
    else {
        if (!r->l || !r->r) {
            node *t = r->l ? r->l : r->r;
            if (!t) { t = r; r = NULL; }
            else *r = *t;
            free(t);
        } else {
            node *t = minv(r->r);
            r->k = t->k;
            r->r = del(r->r, t->k);
        }
    }

    if (!r) return r;

    r->h = 1 + mx(ht(r->l), ht(r->r));
    int b = bal(r);

    if (b > 1 && bal(r->l) >= 0)    return rr(r);
    if (b > 1 && bal(r->l) < 0)     { r->l = lr(r->l); return rr(r); }
    if (b < -1 && bal(r->r) <= 0)   return lr(r);
    if (b < -1 && bal(r->r) > 0)    { r->r = rr(r->r); return lr(r); }

    return r;
}

void inord(node *r) {
    if (!r) return;
    inord(r->l);
    printf("%d ", r->k);
    inord(r->r);
}

void preord(node *r) {
    if (!r) return;
    printf("%d ", r->k);
    preord(r->l);
    preord(r->r);
}

int main() {
    node *r = NULL;

    r = ins(r, 2);
    r = ins(r, 1);
    r = ins(r, 7);
    r = ins(r, 4);
    r = ins(r, 5);
    r = ins(r, 3);
    r = ins(r, 8);

    printf("Inorder: ");
    inord(r);
    printf("\nPreorder: ");
    preord(r);
    printf("\n");

    r = del(r, 3);
    printf("After deleting 3: ");
    inord(r);
    printf("\n");

    return 0;
}

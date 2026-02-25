#include <stdio.h>
#include <stdlib.h>

typedef struct term {
    int c, e;
    struct term *next;
} term;

term *mk(int c, int e) {
    term *t = malloc(sizeof(term));
    t->c = c;
    t->e = e;
    t->next = NULL;
    return t;
}

term *addterm(term *p, int c, int e) {
    if (c == 0) return p;
    term *n = mk(c, e);
    if (!p || e > p->e) {
        n->next = p;
        return n;
    }
    term *cur = p;
    while (cur->next && cur->next->e > e)
        cur = cur->next;

    if (cur->next && cur->next->e == e) {
        cur->next->c += c;
        if (cur->next->c == 0) {
            term *tmp = cur->next;
            cur->next = tmp->next;
            free(tmp);
        }
        free(n);
    } else {
        n->next = cur->next;
        cur->next = n;
    }
    return p;
}

term *add(term *a, term *b) {
    term *res = NULL, *tail = NULL;

    while (a && b) {
        term *n;
        if (a->e > b->e) {
            n = mk(a->c, a->e);
            a = a->next;
        } else if (b->e > a->e) {
            n = mk(b->c, b->e);
            b = b->next;
        } else {
            int s = a->c + b->c;
            if (s == 0) { a = a->next; b = b->next; continue; }
            n = mk(s, a->e);
            a = a->next;
            b = b->next;
        }
        if (!res) res = tail = n;
        else { tail->next = n; tail = n; }
    }

    term *rem = a ? a : b;
    while (rem) {
        term *n = mk(rem->c, rem->e);
        if (!res) res = tail = n;
        else { tail->next = n; tail = n; }
        rem = rem->next;
    }
    return res;
}

term *sub(term *a, term *b) {
    term *res = NULL, *tail = NULL;

    while (a && b) {
        term *n;
        if (a->e > b->e) {
            n = mk(a->c, a->e);
            a = a->next;
        } else if (b->e > a->e) {
            n = mk(-b->c, b->e);
            b = b->next;
        } else {
            int d = a->c - b->c;
            if (d == 0) { a = a->next; b = b->next; continue; }
            n = mk(d, a->e);
            a = a->next;
            b = b->next;
        }
        if (!res) res = tail = n;
        else { tail->next = n; tail = n; }
    }

    while (a) {
        term *n = mk(a->c, a->e);
        if (!res) res = tail = n;
        else { tail->next = n; tail = n; }
        a = a->next;
    }
    while (b) {
        term *n = mk(-b->c, b->e);
        if (!res) res = tail = n;
        else { tail->next = n; tail = n; }
        b = b->next;
    }
    return res;
}

term *mul(term *a, term *b) {
    term *res = NULL;
    for (term *i = a; i; i = i->next)
        for (term *j = b; j; j = j->next)
            res = addterm(res, i->c * j->c, i->e + j->e);
    return res;
}

int eval(term *p, int x) {
    int res = 0;
    while (p) {
        int pw = 1;
        for (int i = 0; i < p->e; i++) pw *= x;
        res += p->c * pw;
        p = p->next;
    }
    return res;
}

void show(term *p) {
    if (!p) { printf("0\n"); return; }
    int first = 1;
    while (p) {
        if (!first && p->c > 0) printf(" + ");
        else if (!first && p->c < 0) printf(" - ");

        int c = first ? p->c : abs(p->c);

        if (p->e == 0)          printf("%d", c);
        else if (p->e == 1)     printf("%dx", c);
        else                    printf("%dx^%d", c, p->e);

        first = 0;
        p = p->next;
    }
    printf("\n");
}

void freep(term *p) {
    while (p) {
        term *t = p;
        p = p->next;
        free(t);
    }
}

int main() {
    term *p1 = NULL;
    p1 = addterm(p1, 3, 4);
    p1 = addterm(p1, 2, 3);
    p1 = addterm(p1, 5, 1);
    p1 = addterm(p1, 7, 0);

    term *p2 = NULL;
    p2 = addterm(p2, 1, 3);
    p2 = addterm(p2, 4, 2);
    p2 = addterm(p2, 3, 0);

    printf("P1 = "); show(p1);
    printf("P2 = "); show(p2);

    term *s = add(p1, p2);
    printf("P1 + P2 = "); show(s);

    term *d = sub(p1, p2);
    printf("P1 - P2 = "); show(d);

    term *m = mul(p1, p2);
    printf("P1 * P2 = "); show(m);

    printf("P1 at x=2: %d\n", eval(p1, 2));

    freep(p1); freep(p2);
    freep(s); freep(d); freep(m);

    return 0;
}

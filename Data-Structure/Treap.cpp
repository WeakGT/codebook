#include <bits/stdc++.h>
using namespace std;
mt19937 rng;
struct node {
  node *l, *r;
  int v, p, s; bool t; // val, pri, size, tag
  void pull();
  void push();
  node(int vv = 0): v(vv), p(rng()), s(1), t(0) {l = r = nullptr;}
};
int sz(node* o) {return o ? o->s : 0;}
void node::pull() {s = (l ? l->s : 0) + (r ? r->s : 0) + 1;}
void node::push() {
  if (t) {
    swap(l, r);
    if (l) l->t ^= 1;
    if (r) r->t ^= 1;
    t = 0;
  }
}
node* merge(node* a, node* b) {
  if (!a || !b) return a ? : b;
  if (a->p < b->p) return a->push(), a->r = merge(a->r, b), a->pull(), a;
  else return b->push(), b->l = merge(a, b->l), b->pull(), b;
}
void split(node* o, node*& a, node*& b, int k) { // a < k, b >= k
  if (!o) return a = b = nullptr, void();
  o->push();
  if (o->v < k) a = o, split(o->r, a->r, b, k);
  else b = o, split(o->l, a, b->l, k);
  o->pull();
}
void insert(node*& o, int k) {
  node *a, *b;
  split(o, a, b, k), o = merge(a, merge(new node(k), b));
}
void ssplit(node* o, node*& a, node*& b, int k) { // split first k things
  if (!o) return a = b = nullptr, void();
  if (sz(o->l) + 1 <= k) a = o, ssplit(o->r, a->r, b, k - sz(o->l) - 1);
  else b = o, ssplit(o->l, a, b->l, k);
  o->pull();
}
void reverse(node* o, int l, int r) {
  node *a, *b, *c;
  ssplit(o, a, b, l - 1), ssplit(b, b, c, r - l + 1);
  b->t ^= 1, o = merge(a, merge(b, c));
}
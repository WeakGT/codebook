const int inf = 1e9;
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
int N, M; // N : row max, M : col max
struct seg {
  vector<int> st;
  void pull(int);
  void merge(const seg&, const seg&, int, int, int);
  void build(int, int, int);
  void upd(int, int, int, int, int);
  int qry(int, int, int, int, int);
  seg(int size): st(size << 2 | 1) {}
};
void seg::pull(int id) {
  st[id] = max(st[lc(id)], st[rc(id)]);
}
void seg::merge(const seg& a, const seg& b, int id = 1, int l = 1, int r = M) {
  st[id] = max(a.st[id], b.st[id]);
  if (l == r) return;
  int m = (l + r) >> 1;
  merge(a, b, lc(id), l, m), merge(a, b, rc(id), m + 1, r);
}
void seg::build(int id = 1, int l = 1, int r = M) {
  if (l == r) {cin >> st[id]; return;}
  int m = (l + r) >> 1;
  build(lc(id), l, m), build(rc(id), m + 1, r);
  pull(id);
}
void seg::upd(int x, int v, int id = 1, int l = 1, int r = M) {
  if (l == r) {st[id] = v; return;}
  int m = (l + r) >> 1;
  if (x <= m) upd(x, v, lc(id), l, m);
  else upd(x, v, rc(id), m + 1, r);
  pull(id);
}
int seg::qry(int ql, int qr, int id = 1, int l = 1, int r = M) {
  if (ql <= l && r <= qr) return st[id];
  int m = (l + r) >> 1, ret = -inf;
  if (ql <= m) ret = max(ret, qry(ql, qr, lc(id), l, m));
  if (qr > m) ret = max(ret, qry(ql, qr, rc(id), m + 1, r));
  return ret;
}

struct segseg {
  vector<seg> st;
  void pull(int, int);
  void build(int, int, int);
  void upd(int, int, int, int, int, int);
  int qry(int, int, int, int, int, int, int);
  segseg(int n, int m): st(n << 2 | 1, seg(m)) {}
};
void segseg::pull(int id, int x) {
  st[id].upd(x, max(st[lc(id)].qry(x, x), st[rc(id)].qry(x, x)));
}
void segseg::build(int id = 1, int l = 1, int r = N) {
  if (l == r) {st[id].build(); return;}
  int m = (l + r) >> 1;
  build(lc(id), l, m), build(rc(id), m + 1, r);
  st[id].merge(st[lc(id)], st[rc(id)]);
}
void segseg::upd(int y, int x, int v, int id = 1, int l = 1, int r = N) {
  if (l == r) {st[id].upd(x, v); return;}
  int m = (l + r) >> 1;
  if (y <= m) upd(y, x, v, lc(id), l, m);
  else upd(y, x, v, rc(id), m + 1, r);
  pull(id, x);
}
int segseg::qry(int y1, int y2, int x1, int x2, int id = 1, int l = 1, int r = N) {
  if (y1 <= l && r <= y2) return st[id].qry(x1, x2);
  int m = (l + r) >> 1, ret = -inf;
  if (y1 <= m) ret = max(ret, qry(y1, y2, x1, x2, lc(id), l, m));
  if (y2 > m) ret = max(ret, qry(y1, y2, x1, x2, rc(id), m + 1, r));
  return ret;
}
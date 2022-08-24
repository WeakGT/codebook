#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
constexpr int N = 2e5 + 1;
int seg[N << 2];
void build(int id, int l,int r) { // [1, n]
	if (l == r) {
		cin >> seg[id];
		return;
	}
	int m = (l + r) >> 1;
	build(lc(id), l, m);
	build(rc(id), m + 1, r);
	seg[id] = max(seg[lc(id)], seg[rc(id)]);
}
void upd(int id, int l, int r, int x, int v) {
	if (l == r) {
		seg[id] = v;
		return;
	}
	int m = (l + r) >> 1;
	if (x <= m) upd(lc(id), l, m, x, v);
	else upd(rc(id), m + 1, r, x, v);
	seg[id] = max(seg[lc(id)], seg[rc(id)]);
}
int qry(int id, int l, int r, int ql, int qr) { // [ql, qr]
	if (ql <= l && r <= qr) return seg[id];
	if (ql > r || qr < l) return 0;
	int m = (l + r) >> 1;
	return max(qry(lc(id), l, m, ql, qr), qry(rc(id), m + 1, r, ql, qr));
}

#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
constexpr int N = 2e5 + 1;
int seg[N << 1], n;
void upd(int x, int v) {
	for (seg[x += n] = v; x > 1; x >>= 1)
		seg[x >> 1] = max(seg[x], seg[x ^ 1]);
}
int qry(int l, int r) { // [ql, qr)
	int ret = -1e9;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l & 1) ret = max(ret, seg[l++]);
		if (r & 1) ret = max(ret, seg[--r]);
	}
	return ret;
}
void build() { // [0, n)
	for (int i = 0; i < n; i++)
		cin >> seg[i + n];
	for (int i = n - 1; i; i--)
		seg[i] = max(seg[lc(i)], seg[rc(i)]);
}
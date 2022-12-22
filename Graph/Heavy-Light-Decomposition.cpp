#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef long long ll;
ll MOD = 10000007LL;

struct SegTree {
	vector<int> seg;
	void init(int _n) {
		seg.resize(_n * 4 + 1, 0);
	}
	void modify(int id, int l, int r, int i, int x) {
		if (l == r) return seg[id] = x, void();
		int mid = (l + r) >> 1;
		if (i <= mid) modify(id * 2, l, mid, i, x);
		else modify(id * 2 + 1, mid + 1, r, i, x);
		seg[id] = max(seg[id * 2], seg[id * 2 + 1]);
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return seg[id];
		if (r < ql || qr < l) return 0;
		int mid = (l + r) >> 1;
		return max(query(id * 2, l, mid, ql, qr), query(id * 2 + 1, mid + 1, r, ql, qr));
	}
} sgt[200009];


int n, q;
int w[200009];
vector<int> v[200009];
int sz[200009];
int p[20][200009];

void Dfs1(int u, int f) {
	p[0][u] = f;
	for (int i = 1; i <= 17; ++ i) p[i][u] = p[i - 1][p[i - 1][u]];
	for (int i = 0; i < (int)v[u].size(); ++ i) {
		if (v[u][i] == f) {
			swap(v[u].back(), v[u][i]);
			break;
		}
	}
	if (u != f) v[u].pop_back();

	sz[u] = 1;
	for (auto i : v[u]) {
		Dfs1(i, u);
		sz[u] += sz[i];
	}
}

int now;
int t[200009];
int top[200009];
int bot[200009];

void Dfs2(int u, int f, bool T) {
	if (T) top[u] = u;
	else top[u] = top[f];
	bot[top[u]] = u;
	t[u] = ++ now;

	if (!v[u].empty()) Dfs2(v[u].back(), u, false);
	for (auto i : v[u]) if (i != v[u].back()) {
			Dfs2(i, u, true);
		}
}

int _t;
int in[200009];
int out[200009];

void Dfs3(int u) {
	in[u] = ++ _t;
	for (auto i : v[u]) Dfs3(i);
	out[u] = ++ _t;
}

bool isfa(int a, int b) {
	return in[a] <= in[b] && out[b] <= out[a];
}

int lca(int a, int b) {
	for (int i = 17; i >= 0; -- i) {
		if (!isfa(p[i][a], b))
			a = p[i][a];
	}
	if (!isfa(a, b)) a = p[0][a];
	return a;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> q;
	for (int i = 1; i <= n; ++ i) cin >> w[i];
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}

	Dfs1(1, 1);
	for (int i = 1; i <= n; ++ i) {
		int p = 0;
		for (int j = 0; j < (int)v[i].size(); ++ j) {
			if (sz[v[i][p]] < sz[v[i][j]])
				p = j;
		}
		if (!v[i].empty()) swap(v[i].back(), v[i][p]);
	}

	Dfs2(1, 1, true);
	for (int i = 1; i <= n; ++ i) if (top[i] == i) {
			sgt[top[i]].init(t[bot[top[i]]] - t[top[i]] + 1);
		}
	for (int i = 1; i <= n; ++ i) sgt[top[i]].modify(1, t[top[i]], t[bot[top[i]]], t[i], w[i]);
	Dfs3(1);

	while ( q -- ) {
		int op; cin >> op;

		if (op == 1) {
			int s, x;
			cin >> s >> x;
			sgt[top[s]].modify(1, t[top[s]], t[bot[top[s]]], t[s], x);
		} else {
			int a, b;
			cin >> a >> b;
			int c = lca(a, b);

			int ans = 0;
			while (top[a] != top[c]) {
				ans = max(ans, sgt[top[a]].query(1, t[top[a]], t[bot[top[a]]], t[top[a]], t[a]));
				a = p[0][top[a]];
			}
			ans = max(ans, sgt[top[c]].query(1, t[top[a]], t[bot[top[a]]], t[c], t[a]));

			while (top[b] != top[c]) {
				ans = max(ans, sgt[top[b]].query(1, t[top[b]], t[bot[top[b]]], t[top[b]], t[b]));
				b = p[0][top[b]];
			}
			ans = max(ans, sgt[top[b]].query(1, t[top[b]], t[bot[top[b]]], t[c], t[b]));

			cout << ans << " ";
		}
	}
	cout << "\n";
}
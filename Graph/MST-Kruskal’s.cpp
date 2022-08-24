#define ALL(x) (x).begin(), (x).end()
using ll = long long;
constexpr int N = 1e5 + 1;

int p[N], s[N];

int find(int x) {
	return x == p[x] ? x : p[x] = find(p[x]);
}

void joint(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return;
	if (s[a] > s[b]) p[b] = a, s[a] += s[b];
	else p[a] = b, s[b] += s[a];
}

ll kruskal(int n, int m) { // n vertices, m edges
	for (int i = 0; i < n; i++) p[i] = i, s[i] = 1;
	vector<tuple<int, int, int>> v(m); // {w, a, b}
	for (auto& [w, a, b] : v) cin >> a >> b >> w;
	sort(ALL(v));
	ll res = 0; int cnt = 0;
	for (const auto& [w, a, b] : v)
		if (find(a) != find(b)) res += w, joint(a, b), cnt++;
	return cnt == n - 1 ? res : -1;
}

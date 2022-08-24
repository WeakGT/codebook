#define ep emplace
#define eb emplace_back

constexpr int N = 1e5 + 1;
vector<int> g[N], in(N), ans;

void topological_sort(int n, int m) {
	for (int i = 0, a, b; i < m; i++)
		cin >> a >> b, g[a].eb(b), in[b]++;
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (!in[i]) q.ep(i);
	if (q.empty()) {
		cout << "-1\n";
		return;
	}
	while (!q.empty()) {
		auto a = q.front(); q.pop(), ans.eb(a);
		for (const auto& i : g[a])
			if (!--in[i]) q.ep(i);
	}
	if (ans.size() == n)
		for (const auto& i : ans) cout << i << " \n"[&i == &ans.back()];
	else cout << "-1\n";
}

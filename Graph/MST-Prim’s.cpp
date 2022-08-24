#define f first
#define s second
#define ep emplace
using ll = long long;
using pii = pair<int, int>;
constexpr int N = 1e5 + 1, inf = 1e9;

vector<pii> g[N];
vector<bool> v;

ll prim(int n, int m) { // n vertices, m edges
	v.assign(n, 0);
	for (int i = 0; i < n; g[i].clear(), i++);
	for (int i = 0, a, b, c; i < m; i++)
		cin >> a >> b >> c, g[a].eb(b, c), g[b].eb(a, c);
	// pq : {first, second}->{edge cost, vertex id}
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.ep(0, 0);
	ll sum = 0; int cnt = 0;
	while (!pq.empty()) {
		auto a = pq.top(); pq.pop();
		if (v[a.s]) continue;
		v[a.s] = 1, cnt++, sum += a.f;
		for (const auto& i : g[a.s])
			if (!v[i.f]) pq.ep(i.s, i.f);
	}
	return (cnt == n ? sum : -1);
}

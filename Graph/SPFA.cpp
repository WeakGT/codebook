#define f first
#define s second
#define ep emplace
#define eb emplace_back
using ll = long long;
using pii = pair<int, int>;
constexpr int N = 1e5 + 1;
constexpr ll inf = 1e18;

vector<pii> g[N];
vector<ll> d(N, inf), cnt(N);
vector<bool> inq(N);

ll spfa(int n, int m, int s, int t) { // n vertices, m edges, source, target
	for (int i = 0; i < n; i++) g[i].clear();
	for (int i = 0, a, b, c; i < m; i++)
		cin >> a >> b >> c, g[a].eb(b, c), g[b].eb(a, c);
	queue<int> q;
	q.ep(s), d[s] = 0, inq[s] = 1;
	while (!q.empty()) {
		auto a = q.front(); q.pop(), inq[a] = 0;
		if (++cnt[a] > n) return -1; //  detect negative cycle
		for (const auto& i : g[a])
			if (d[a] + i.s < d[i.f]) {
				d[i.f] = d[a] + i.s;
				if (!inq[i.f]) q.ep(i.f), inq[i.f] = 1;
			}
	}
	return d[t];
}

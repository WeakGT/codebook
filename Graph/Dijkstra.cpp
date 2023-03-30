#define f first
#define s second
#define ep emplace
using ll = long long;
using pii = pair<int, int>;
const int N = 2e5 + 5;
const ll inf = 1e18;

vector<pii> g[N];
vector<ll> d(N, inf);

ll dijkstra(int n, int m, int s, int t) { // n vertices, m edges, source, target
  for (int i = 0; i < n; g[i].clear(), i++);
  for (int i = 0, a, b, c; i < m; i++)
    cin >> a >> b >> c, g[a].eb(b, c), g[b].eb(a, c);
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.ep(d[s] = 0, s); // {edge, vertex}
  while (!pq.empty()) {
    auto a = pq.top(); pq.pop();
    if (d[a.s] != a.f) continue;
    for (const auto& i : g[a.s])
      if (d[a.s] + i.s < d[i.f])
        pq.ep(d[i.f] = d[a.s] + i.s, i.f);
  }
  return d[t];
}
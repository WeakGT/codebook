const ll inf = 1e18;

ll bellman_ford(int n, int m, int s, int t) { // n vertices, m edges, source, target
  vector<tuple<int, int, int>> v(m);
  for (auto& [a, b, c] : v) cin >> a >> b >> c;
  vector<ll> d(n, inf);
  d[s] = 0;
  for (int i = 0; i < n - 1; i++)
    for (const auto& [a, b, c] : v)
      if (d[a] + c < d[b]) d[b] = d[a] + c;
  for (const auto& [a, b, c] : v) // detect negative cycle
    if (d[a] + c < d[b]) return -1;
  return d[t];
}
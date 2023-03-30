#define eb emplace_back
const int N = 2e5 + 5, logN = __lg(N) + 1, inf = 1e9;
int n, q, logn;
int dep[N], fa[N][logN];
vector<int> g[N];

void dfs(int x, int p) {
  dep[x] = ~p ? dep[p] + 1 : 0;
  fa[x][0] = p;
  for (int i = 1; (1 << i) <= dep[x]; i++)
    fa[x][i] = fa[fa[x][i - 1]][i - 1];
  for (const auto& u : g[x])
    if (u != p) dfs(u, x);
}

int LCA(int u, int v) {
  if (dep[u] > dep[v]) swap(u, v);
  for (int i = 0; i < logn; i++)
    if ((dep[v] - dep[u]) >> i & 1) v = fa[v][i];
  if (u == v) return u;
  for (int i = logn - 1; i >= 0; i--)
    if (fa[u][i] != fa[v][i])
      u = fa[u][i], v = fa[v][i];
  return fa[u][0];
}
// g[a].eb(b)
// dfs(root, -1)
// query -> LCA(u, v)
// distance of (u, v) = dep[u] + dep[v] - 2 * dep[LCA(u, v)]

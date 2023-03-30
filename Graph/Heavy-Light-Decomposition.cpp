#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
#define eb emplace_back
int t, n, q, seg[N << 1]; // t := time-stamp
int sz[N], fa[N], dep[N], to[N], fr[N], dfn[N], arr[N];
// size, father, depth, to-heavy-child, from-head, dfs-order, a_i value
vector<int> g[N];
void upd(int x, int v) {
  for (seg[x += n] = v; x > 1; x >>= 1)
    seg[x >> 1] = max(seg[x], seg[x ^ 1]);
}
int qry(int l, int r) { // [l, r]
  int ret = -1e9; // -max
  for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ret = max(ret, seg[l++]);
    if (r & 1) ret = max(ret, seg[--r]);
  }
  return ret;
}
void dfs(int x, int p) {
  sz[x] = 1, fa[x] = p, to[x] = -1, dep[x] = ~p ? dep[p] + 1 : 0;
  for (auto i : g[x])
    if (i != p) {
      dfs(i, x);
      if (to[x] == -1 || sz[i] > sz[to[x]]) to[x] = i;
      sz[x] += sz[i];
    }
}
void dfs2(int x, int f) {
  fr[x] = f, dfn[x] = ++t, upd(dfn[x], arr[x]);
  if (to[x] != -1) dfs2(to[x], f);
  for (auto i : g[x])
    if (i != fa[x] && i != to[x]) dfs2(i, i);
}
int qry2(int u, int v) { // query on tree
  int fu = fr[u], fv = fr[v], ret = -1e9;
  while (fu != fv) {
    if (dep[fu] < dep[fv]) swap(fu, fv), swap(u, v);
    ret = max(ret, qry(dfn[fu], dfn[u])); // interval: [dfn[fu], dfn[u]]
    u = fa[fu], fu = fr[u];
  }
  if (dep[u] > dep[v]) swap(u, v);
  // u is the LCA
  ret = max(ret, qry(dfn[u], dfn[v]));
  return ret;
}
int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> arr[i];
  for (int i = 1, a, b; i < n; i++)
    cin >> a >> b, g[a].eb(b), g[b].eb(a);
  dfs(1, -1), dfs2(1, 1);
  while (q--) {
    int op; cin >> op;
    if (op == 1) {
      int x, v; cin >> x >> v, arr[x] = v, upd(dfn[x], v);
    }
    else {
      int a, b; cin >> a >> b;
      cout << qry2(a, b) << '\n';
    }
  }
}
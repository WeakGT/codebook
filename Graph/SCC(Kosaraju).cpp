#define eb emplace_back
const int N = 2e5 + 5;
vector<int> g[N], rg[N], ord;
int scc[N];
bool v[N];
void rdfs(int x) {
  v[x] = 1;
  for (const auto& i : rg[x])
    if (!v[i]) rdfs(i);
  ord.eb(x);
}
void dfs(int x, int nscc) {
  scc[x] = nscc;
  for (const auto& i : g[x])
    if (scc[i] == -1) dfs(i, nscc);
}
void kosaraju(int n) {
  memset(v, 0, sizeof(v));
  memset(scc, -1, sizeof(scc));
  for (int i = 0; i < n; i++)
    if (!v[i]) rdfs(i);
  int nscc = 0;
  for (int i = n - 1; i >= 0; i--) {
    int x = ord[i];
    if (scc[x] == -1)
      dfs(x, nscc++);
  }
}

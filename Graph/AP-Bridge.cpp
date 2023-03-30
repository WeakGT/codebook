#define eb emplace_back
using pii = pair<int, int>;
const int N = 2e5 + 5;

int d[N], low[N];
vector<int> g[N];
vector<int> ap;
vector<pii> bridge;

void dfs(int x, int p) {
  d[x] = ~p ? d[p] + 1 : 1, low[x] = d[x];
  int cnt = 0;
  bool isap = 0;
  for (const auto& i : g[x]) {
    if (i == p) continue;
    if (!d[i]) {
      dfs(i, x), cnt++;
      if (d[x] <= low[i]) isap = 1;
      if (d[x] < low[i]) bridge.eb(x, i);
      low[x] = min(low[x], low[i]);
    }
    low[x] = min(low[x], d[i]);
  }
  if (p == -1 && cnt < 2) isap = 0;
  if (isap) ap.eb(x);
}

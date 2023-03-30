#define ep emplace
constexpr int N = 2e5 + 1;

int d[N], low[N], bcc[N], nbcc;
vector<int> g[N];
stack<int> st;

void dfs(int x, int p) {
  d[x] = ~p ? d[p] + 1 : 1, low[x] = d[x];
  st.ep(x);
  for (const auto& i : g[x]) {
    if (i == p) continue;
    if (!d[i]) {
      dfs(i, x);
      low[x] = min(low[x], low[i]);
    }
    low[x] = min(low[x], d[i]);
  }
  if (low[x] == d[x]) {
    nbcc++;
    int tmp;
    do tmp = st.top(), st.pop(), bcc[tmp] = nbcc; while (tmp != x);
  }
}

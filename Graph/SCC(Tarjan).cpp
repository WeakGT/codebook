#define ep emplace
const int N = 2e5 + 5;
int d[N], low[N], scc[N], ins[N], nscc;
vector<int> g[N];
stack<int> st;
void dfs(int x, int p) {
  d[x] = ~p ? d[p] + 1 : 1, low[x] = d[x];
  st.ep(x), ins[x] = 1;
  for (const auto& i : g[x]) {
    if (!d[i]) dfs(i, x), low[x] = min(low[x], low[i]);
    else if (ins[i]) low[x] = min(low[x], d[i]);
  }
  if (d[x] == low[x]) {
    nscc++;
    int tmp;
    do tmp = st.top(), st.pop(), scc[tmp] = nscc, ins[tmp] = 0; while (tmp != x);
  }
}

#define ep emplace
#define eb emplace_back
constexpr int N = 2e5 + 1;

int d[N], low[N], id;
vector<int> g[N];
vector<vector<int>> bcc;
stack<int> st;

void dfs(int x, int p) {
	d[x] = ~p ? d[p] + 1 : 1, low[x] = d[x];
	st.ep(x);
	for (const auto& i : g[x]) {
		if (i == p) continue;
		if (!d[i]) {
			dfs(i, x);
			low[x] = min(low[x], low[i]);
			if (d[x] <= low[i]) {
				int tmp;
				bcc.eb();
				do tmp = st.top(), st.pop(), bcc.back().eb(tmp); while (tmp != x);
				st.ep(x);
			}
		}
		low[x] = min(low[x], d[i]);
	}
}

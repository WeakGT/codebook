constexpr int N = 500 + 1;
constexpr ll inf = 1e18;
vector<vector<ll>> d(N, vector<ll>(N, inf));
for (int i = 1; i <= n; i++) d[i][i] = 0;
for (int k = 1; k <= n; k++)
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

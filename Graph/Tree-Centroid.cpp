const int N = 2e5 + 5, inf = 1e9;

vector<int> g[N];
int n, sz[N], center, csize; // set csize = inf

void dfs(int x, int p) {
  int mxsub = 0;
  sz[x] = 1;
  for (const auto& i : g[x])
    if (i != p) dfs(i, x), sz[x] += sz[i], mxsub = max(mxsub, sz[i]);
  mxsub = max(mxsub, n - sz[x]);
  if (mxsub < csize) center = x, csize = mxsub;
}

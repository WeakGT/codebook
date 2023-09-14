using ll = long long;
const int N = 1000 + 5;
ll bit[N][N];
int n, m, a[N][N];
void build() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      bit[i][j] = a[i][j];
  for (int b = 1; b << 1 <= max(n, m); b <<= 1) {
    for (int i = b; i + b <= n; i += b << 1)
      for (int j = 1; j <= m; j++)
        bit[i + b][j] += bit[i][j];
    for (int i = 1; i <= n; i++)
      for (int j = b; j + b <= m; j += b << 1)
        bit[i][j + b] += bit[i][j];
  }
}
void upd(int x, int y, int v) {
  for (int i = x; i <= n; i += i & -i)
    for (int j = y; j <= m; j += j & -j)
      bit[i][j] += v;
}
ll qry(int x, int y) {
  ll ret = 0;
  for (int i = x; i; i -= i & -i)
    for (int j = y; j; j -= j & -j)
      ret += bit[i][j];
  return ret;
}
ll qry(int x1, int y1, int x2, int y2) { // closed-interval
  return qry(x2, y2) - qry(x1 - 1, y2) - qry(x2, y1 - 1) + qry(x1 - 1, y1 - 1);
}
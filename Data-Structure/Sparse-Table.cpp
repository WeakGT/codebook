const int N = 5e5 + 5, logN = __lg(N) + 1;
int st[logN][N], a[N];
void build(int n) { // 0-based
  copy(a, a + n, st[0]);
  for (int i = 1; (1 << i) <= n; i++)
    for (int j = 0; j + (1 << i) - 1 <= n; j++)
      st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}
int qry(int l, int r) {
  int k = __lg(r - l + 1);
  return max(st[k][l], st[k][r - (1 << k) + 1]);
}
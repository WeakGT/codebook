template <typename T> using vec = vector<T>;
template <typename T> using matrix = vec<vec<T>>;
constexpr int mod = 1e9 + 7;
template <typename T>
matrix<T> operator*(const matrix<T>& a, const matrix<T>& b) {
  int n = a.size(), r = b.size(), m = b.front().size();
  matrix<T> ret(n, vec<T>(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      for (int k = 0; k < r; k++)
        ret[i][j] += 1LL * a[i][k] * b[k][j] % mod, ret[i][j] %= mod;
  return ret;
}

const int G = 3, P = 998244353;
const int sval = 100, split = log10(sval);
int fpow(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1, x = 1LL * x * x % P)
    if (y & 1) ret = 1LL * ret * x % P;
  return ret;
}
void ntt(vector<int>& x, int lim, int opt) {
  for (int i = 1, j = 0; i < lim; i++) {
    for (int k = lim >> 1; !((j ^= k) & k); k >>= 1);
    if (i < j) swap(x[i], x[j]);
  }
  for (int m = 2; m <= lim; m <<= 1) {
    int k = m >> 1;
    int gn = fpow(G, (P - 1) / m);
    for (int i = 0; i < lim; i += m) {
      int g = 1;
      for (int j = 0; j < k; ++j, g = 1LL * g * gn % P) {
        int tmp = 1LL * x[i + j + k] * g % P;
        x[i + j + k] = (x[i + j] - tmp + P) % P;
        x[i + j] = (x[i + j] + tmp) % P;
      }
    }
  }
  if (opt == -1) {
    reverse(x.begin() + 1, x.begin() + lim);
    int inv = fpow(lim, P - 2);
    for (int i = 0; i < lim; ++i)
      x[i] = 1LL * x[i] * inv % P;
  }
}
vector<int> mul(vector<int> a, vector<int> b) {
  int lim = 1, n = a.size(), m = b.size();
  while (lim < (n + m - 1)) lim <<= 1;
  a.resize(lim + 1), b.resize(lim + 1);
  ntt(a, lim, 1), ntt(b, lim, 1);
  for (int i = 0; i < lim; ++i)
    a[i] = 1LL * a[i] * b[i] % P;
  ntt(a, lim, -1);
  int len = 0;
  for (int i = 0; i < lim; ++i) {
    if (a[i] >= sval) len = i + 1, a[i + 1] += a[i] / sval, a[i] %= sval;
    if (a[i]) len = max(len, i);
  }
  while (a[len] >= sval) a[len + 1] += a[len] / sval, a[len] %= sval, len++;
  return a.resize(len + 1), a;
}
void print(const vector<int>& v) {
  if (!v.size()) return;
  cout << v.back();
  for (int i = v.size() - 2; ~i; --i)
    cout << setfill('0') << setw(split) << v[i];
  cout << '\n';
}
int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  string stra, strb;
  while (cin >> stra >> strb) {
    vector<int> a((stra.size() + split - 1) / split);
    vector<int> b((strb.size() + split - 1) / split);
    int tmp = stra.size();
    for (auto& i : a)
      tmp -= split, i = atoi(stra.substr(max(0, tmp), min(split, split + tmp)).data());
    tmp = strb.size();
    for (auto& i : b)
      tmp -= split, i = atoi(strb.substr(max(0, tmp), min(split, split + tmp)).data());
    print(mul(a, b));
  }
  return 0;
}

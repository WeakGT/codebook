vector<bool> isp;
vector<int> p;
void sieve(int n) {
  p.clear(), isp.assign(n + 1, 1);
  isp[0] = isp[1] = 0;
  for (int i = 2; i <= n; i++) {
    if (isp[i]) p.eb(i);
    for (const auto& x : p) {
      if (1LL * i * x > n) break;
      isp[i * x] = 0;
      if (i % x == 0) break;
    }
  }
}
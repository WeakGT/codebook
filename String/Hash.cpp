struct Hash {
  vector<ll> h;
  vector<ll> f;
  Hash(string s, int p = 127) {
    h.assign((int)s.size() + 1, 0);
    f.assign((int)s.size() + 1, 0);
    f[0] = 1;
    for (int i = 1; i <= (int)s.size(); ++ i) f[i] = f[i - 1] * p % MOD;
    for (int i = 1; i <= (int)s.size(); ++ i)
      h[i] = (h[i - 1] * p + s[i - 1]) % MOD;
  }
  int query(int l, int r) { // 0-based [l, r]
    if (r < l) return 0;
    return ((h[r + 1] - h[l] * f[r - l + 1]) % MOD + MOD) % MOD;
  }
};
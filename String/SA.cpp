const int N = 2e5 + 5;

string s;
int sa[N], tmp[2][N], c[N], rk[N], h[N];
// lcp(sa[i], sa[j]) = min{h[k]} where i <= k <= j

void suffix_array() {
  int *x = tmp[0], *y = tmp[1], m = 256, n = s.size();
  fill(c, c + m, 0);
  for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
  partial_sum(c, c + m, c);
  for (int i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
  for (int k = 1; k < n; k <<= 1) {
    fill(c, c + m, 0);
    for (int i = 0; i < n; i++) c[x[i]]++;
    partial_sum(c, c + m, c);
    int p = 0;
    for (int i = n - k; i < n; i++) y[p++] = i;
    for (int i = 0; i < n; i++)
      if (sa[i] >= k) y[p++] = sa[i] - k;
    for (int i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
    y[sa[0]] = p = 0;
    for (int i = 1; i < n; i++) {
      int a = sa[i], b = sa[i - 1];
      if (x[a] != x[b] || a + k >= n || b + k >= n || x[a + k] != x[b + k]) p++;
      y[sa[i]] = p;
    }
    if (n == p + 1) break;
    swap(x, y), m = p + 1;
  }
}

void LCP() {
  int n = s.size(), val = 0;
  for (int i = 0; i < n; i++) rk[sa[i]] = i;
  for (int i = 0; i < n; i++) {
    if (rk[i] == 0) h[rk[i]] = 0;
    else {
      if (val) val--;
      int p = sa[rk[i] - 1];
      while (val + i < n && val + p < n && s[val + i] == s[val + p]) val++;
      h[rk[i]] = val;
    }
  }
}
// cin >> s, suffix_array(), LCP();
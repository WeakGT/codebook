#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5, sqN = sqrt(N) + 5;
int a[N], ans[N], n, q, sz; // maybe need blk[sqN];

struct Query {
  int ql, qr, id;
  bool operator<(const Query& b) const {
    int aa = ql / sz, bb = b.ql / sz;
    if (aa != bb) return aa < bb;
    else return qr < b.qr;
  }
} Q[N];

void add(int x) {}
void sub(int x) {}
int qry(int k) {}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> q, sz = sqrt(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0, ql, qr; i < q; i++)
    cin >> ql >> qr, Q[i] = {ql - 1, qr - 1, i};
  // Mo's algorithm
  sort(Q, Q + q); /* remember initialize arrays */
  int l = 0, r = -1;
  for (int i = 0; i < q; i++) {
    auto [ql, qr, k, id] = Q[i];
    while (r < qr) add(a[++r]);
    while (r > qr) sub(a[r--]);
    while (l < ql) sub(a[l++]);
    while (l > ql) add(a[--l]);
    ans[id] = qry(k);
  }
  for (int i = 0; i < q; i++) cout << ans[i] << '\n';
}
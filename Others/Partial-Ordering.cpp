// O(n log^2 n)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5, M = 2e5 + 5;
int n, K, cnt, ans[N];
struct node {
  int x, y, z, v, ans, tag, id;
  node() { ans = tag = v = x = y = z = 0; }
  friend bool operator==(const node &a, const node &b) {
    return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
  }
} a[N], t[N];
bool cmp1(const node &a, const node &b) {
  if (a.x != b.x) return a.x < b.x;
  if (a.y != b.y) return a.y < b.y;
  return a.z < b.z;
}
bool cmp2(const node &a, const node &b) {
  if (a.y != b.y) return a.y < b.y;
  if (a.tag != b.tag) return a.tag < b.tag;
  return a.id < b.id;
}
#define lowbit(x) (x & -x)
int bit[M];
void add(int p, int x) {
  for (; p <= K; p += lowbit(p)) bit[p] += x;
}
int query(int p) {
  int ret = 0;
  for (; p; p -= lowbit(p)) ret += bit[p];
  return ret;
}
void CDQ(int l, int r) {
  if (l == r) return;
  int mid = (l + r) >> 1;
  CDQ(l, mid); CDQ(mid + 1, r);
  for (int i = l; i <= r; ++i) a[i].id = i;
  for (int i = l; i <= mid; ++i) a[i].tag = 0;
  for (int i = mid + 1; i <= r; ++i) a[i].tag = 1;
  sort(a + l, a + r + 1, cmp2);
  for (int i = l; i <= r; ++i) {
    if (!a[i].tag) add(a[i].z, a[i].v);
    else a[i].ans += query(a[i].z);
  }
  for (int i = l; i <= r; ++i)
    if (!a[i].tag) add(a[i].z, -a[i].v);
}
int main() {
  cin >> n >> K;
  for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y >> a[i].z, a[i].v = 1;
  sort(a + 1, a + n + 1, cmp1);
  cnt = 1;
  for (int i = 2; i <= n; ++i) {
    if (a[i] == a[cnt]) ++a[cnt].v;
    else a[++cnt] = a[i];
  }
  CDQ(1, cnt);
  // let ans[i] denote that the number of (aj<=ai && bj<=bi && cj<=ci) for i != j
  for (int i = 1; i <= cnt; ++i) ans[a[i].ans + a[i].v - 1] += a[i].v;
  for (int i = 0; i < n; ++i) cout << ans[i] << '\n';
  return 0;
}
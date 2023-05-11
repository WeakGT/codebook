#define f first
#define s second
#define ALL(x) (x).begin(), (x).end()
template <typename T>
pair<T, T> operator-(const pair<T, T>& a, const pair<T, T>& b) {
  return {a.f - b.f, a.s - b.s};
}
template <typename T>
int cross(const pair<T, T>& o, const pair<T, T>& a, const pair<T, T>& b) {
  auto p = a - o, q = b - o;
  return p.f * q.s - q.f * p.s;
}
template <typename T>
vector<pair<T, T>> convex_hull(vector<pair<T, T>> hull) {
  if (hull.size() <= 2) return hull;
  sort(ALL(hull));
  vector<pair<T, T>> stk;
  int n = hull.size();
  for (int i = 0; i < n; i++) {
    while (stk.size() >= 2 && cross(stk.end()[-2], stk.end()[-1], hull[i]) <= 0)
      stk.pop_back();
    stk.push_back(hull[i]);
  }
  for (int i = n - 2, t = stk.size() + 1; i >= 0; i--) {
    while ((int)stk.size() >= t && cross(stk.end()[-2], stk.end()[-1], hull[i]) <= 0)
      stk.pop_back();
    stk.push_back(hull[i]);
  }
  return stk.pop_back(), stk;
}

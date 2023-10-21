// Courtesy of Jinkela
const double PI = atan2(0.0, -1.0);
template<typename T>
struct point {
  T x, y;
  point() {}
  point(const T&x, const T&y): x(x), y(y) {}
  point operator+(const point &b)const {
    return point(x + b.x, y + b.y);
  }
  point operator-(const point &b)const {
    return point(x - b.x, y - b.y);
  }
  point operator*(const T &b)const {
    return point(x * b, y * b);
  }
  point operator/(const T &b)const {
    return point(x / b, y / b);
  }
  bool operator==(const point &b)const {
    return x == b.x && y == b.y;
  }
  T dot(const point &b)const { return x * b.x + y * b.y; }
  T cross(const point &b)const { return x * b.y - y * b.x; }
  point normal()const { //求法向量
    return point(-y, x);
  }
  T abs2()const { return dot(*this); }
  T rad(const point &b)const { //兩向量的弧度
    return fabs(atan2(fabs(cross(b)), dot(b)));
  }
  T getA()const { //對x軸的弧度
    T A = atan2(y, x); //超過180度會變負的
    if (A <= -PI / 2)A += PI * 2;
    return A;
  }
};
template<typename T>
struct line {
  line() {}
  point<T> p1, p2;
  T a, b, c; //ax+by+c=0
  line(const point<T>&x, const point<T>&y): p1(x), p2(y) {}
  void pton() { //轉成一般式
    a = p1.y - p2.y; b = p2.x - p1.x; c = -a * p1.x - b * p1.y;
  }
  T ori(const point<T> &p)const { //點和有向直線的關係，>0左邊、=0在線上<0右邊
    return (p2 - p1).cross(p - p1);
  }
  T btw(const point<T> &p)const { //點投影落在線段上<=0
    return (p1 - p).dot(p2 - p);
  }
  bool point_on_segment(const point<T>&p)const {
    return ori(p) == 0 && btw(p) <= 0;
  }
  T dis2(const point<T> &p, bool is_segment = 0)const { //點跟直線/線段的距離平方
    point<T> v = p2 - p1, v1 = p - p1;
    if (is_segment) {
      point<T> v2 = p - p2;
      if (v.dot(v1) <= 0)return v1.abs2();
      if (v.dot(v2) >= 0)return v2.abs2();
    }
    T tmp = v.cross(v1); return tmp * tmp / v.abs2();
  }
  T seg_dis2(const line<T> &l)const { //兩線段距離平方
    return min({dis2(l.p1, 1), dis2(l.p2, 1), l.dis2(p1, 1), l.dis2(p2, 1)});
  }
  point<T> projection(const point<T> &p)const { //點對直線的投影
    point<T> n = (p2 - p1).normal();
    return p - n * (p - p1).dot(n) / n.abs2();
  }
  point<T> mirror(const point<T> &p)const {
    //點對直線的鏡射，要先呼叫pton轉成一般式
    point<T> R; T d = a * a + b * b;
    R.x = (b * b * p.x - a * a * p.x - 2 * a * b * p.y - 2 * a * c) / d;
    R.y = (a * a * p.y - b * b * p.y - 2 * a * b * p.x - 2 * b * c) / d;
    return R;
  }
  bool parallel(const line &l)const {
    return (p1 - p2).cross(l.p1 - l.p2) == 0;
  }
};
template<typename T>
struct polygon {
  polygon() {}
  vector<point<T> > p;//逆時針順序
  T double_signed_area()const {
    T ans = 0;
    for (int i = p.size() - 1, j = 0; j < (int)p.size(); i = j++)
      ans += p[i].cross(p[j]);
    return ans;
  }
  point<T> center_of_mass()const {
    T cx = 0, cy = 0, w = 0;
    for (int i = p.size() - 1, j = 0; j < (int)p.size(); i = j++) {
      T a = p[i].cross(p[j]);
      cx += (p[i].x + p[j].x) * a; cy += (p[i].y + p[j].y) * a;
      w += a;
    } return point<T>(cx / 3 / w, cy / 3 / w);
  }
  int ahas(const point<T>& t)const { //點是否在簡單多邊形內，是的話回傳1、在邊上回傳-1、否則回傳0
    int c = 0; //Works for clockwise input as well
    for (int i = 0, j = p.size() - 1; i < p.size(); j = i++) {
      if (line<T>(p[i], p[j]).point_on_segment(t))return -1;
      if ((p[i].y > t.y) != (p[j].y > t.y)) {
        T L = (t.x - p[i].x) * (p[j].y - p[i].y);
        T R = (p[j].x - p[i].x) * (t.y - p[i].y);
        if (p[j].y < p[i].y) {L = -L; R = -R;}
        if (L < R)c = !c;
      }
    } return c;
  }
  int point_in_convex(const point<T>&x)const {
    int l = 1, r = (int)p.size() - 2;
    while (l <= r) { //點是否在凸多邊形內，是的話回傳1、在邊上回傳-1、否則回傳0
      int mid = (l + r) / 2;
      T a1 = (p[mid] - p[0]).cross(x - p[0]);
      T a2 = (p[mid + 1] - p[0]).cross(x - p[0]);
      if (a1 >= 0 && a2 <= 0) {
        T res = (p[mid + 1] - p[mid]).cross(x - p[mid]);
        return res > 0 ? 1 : (res >= 0 ? -1 : 0);
      }
      if (a1 < 0)r = mid - 1; else l = mid + 1;
    } return 0;
  }
  vector<T> getA()const { //凸包邊對x軸的夾角
    vector<T>res;//一定是遞增的
    for (size_t i = 0; i < p.size(); ++i)
      res.push_back((p[(i + 1) % p.size()] - p[i]).getA());
    return res;
  }
  bool line_intersect(const vector<T>&A, const line<T> &l)const { //O(logN)
    int f1 = upper_bound(A.begin(), A.end(), (l.p1 - l.p2).getA()) - A.begin();
    int f2 = upper_bound(A.begin(), A.end(), (l.p2 - l.p1).getA()) - A.begin();
    return l.cross_seg(line<T>(p[f1], p[f2]));
  }
  T diam() {
    int n = p.size(), t = 1;
    T ans = 0; p.push_back(p[0]);
    for (int i = 0; i < n; i++) {
      point<T> now = p[i + 1] - p[i];
      while (now.cross(p[t + 1] - p[i]) > now.cross(p[t] - p[i]))t = (t + 1) % n;
      ans = max(ans, (p[i] - p[t]).abs2());
    } return p.pop_back(), ans;
  }
  T min_cover_rectangle() {
    int n = p.size(), t = 1, r = 1, l;
    if (n < 3)return 0; //也可以做最小周長矩形
    T ans = 1e99; p.push_back(p[0]);
    for (int i = 0; i < n; i++) {
      point<T> now = p[i + 1] - p[i];
      while (now.cross(p[t + 1] - p[i]) > now.cross(p[t] - p[i]))t = (t + 1) % n;
      while (now.dot(p[r + 1] - p[i]) > now.dot(p[r] - p[i]))r = (r + 1) % n;
      if (!i)l = r;
      while (now.dot(p[l + 1] - p[i]) <= now.dot(p[l] - p[i]))l = (l + 1) % n;
      T d = now.abs2();
      T tmp = now.cross(p[t] - p[i]) * (now.dot(p[r] - p[i]) - now.dot(p[l] - p[i])) / d;
      ans = min(ans, tmp);
    } return p.pop_back(), ans;
  }
  T dis2(polygon &pl) { //凸包最近距離平方
    vector<point<T> > &P = p, &Q = pl.p;
    int n = P.size(), m = Q.size(), l = 0, r = 0;
    for (int i = 0; i < n; ++i)if (P[i].y < P[l].y)l = i;
    for (int i = 0; i < m; ++i)if (Q[i].y < Q[r].y)r = i;
    P.push_back(P[0]), Q.push_back(Q[0]);
    T ans = 1e99;
    for (int i = 0; i < n; ++i) {
      while ((P[l] - P[l + 1]).cross(Q[r + 1] - Q[r]) < 0)r = (r + 1) % m;
      ans = min(ans, line<T>(P[l], P[l + 1]).seg_dis2(line<T>(Q[r], Q[r + 1])));
      l = (l + 1) % n;
    } return P.pop_back(), Q.pop_back(), ans;
  }
  static int sign(const point<T>&t) {
    return (t.y ? t.y : t.x) < 0;
  }
  static bool angle_cmp(const line<T>& A, const line<T>& B) {
    point<T> a = A.p2 - A.p1, b = B.p2 - B.p1;
    return sign(a) < sign(b) || (sign(a) == sign(b) && a.cross(b) > 0);
  }
  int halfplane_intersection(vector<line<T> > &s) {
    sort(s.begin(), s.end(), angle_cmp); //線段左側為該線段半平面
    int L, R, n = s.size();
    vector<point<T> > px(n);
    vector<line<T> > q(n);
    q[L = R = 0] = s[0];
    for (int i = 1; i < n; ++i) {
      while (L < R && s[i].ori(px[R - 1]) <= 0)--R;
      while (L < R && s[i].ori(px[L]) <= 0)++L;
      q[++R] = s[i];
      if (q[R].parallel(q[R - 1]) && q[--R].ori(s[i].p1) > 0)q[R] = s[i];
      if (L < R)px[R - 1] = q[R - 1].line_intersection(q[R]);
    }
    while (L < R && q[L].ori(px[R - 1]) <= 0)--R;
    p.clear();
    if (R - L <= 1)return 0;
    px[R] = q[R].line_intersection(q[L]);
    for (int i = L; i <= R; ++i)p.push_back(px[i]);
    return R - L + 1;
  }
};

const int N = 2e5 + 5;
int p[N], s[N];
void init(int n) {
	for (int i = 0; i <= n; i++) p[i] = i, r[i] = 1;
}
int find(int x) {
	return p[x] == x ? x : p[x] = find(p[x]);
}
void joint(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) return;
	if (s[x] > s[y]) s[x] += s[y], p[y] = x;
	else s[y] += s[x], p[x] = y;
}

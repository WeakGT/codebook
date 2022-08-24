using ll = long long;

void karatsuba(const vector<ll>& f, const vector<ll>& g, vector<ll>& c, int n) {
	if (n <= 32) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				c[i + j] += f[i] * g[j];
		return;
	}
	vector<ll> f1(n / 2), f2(n / 2), g1(n / 2), g2(n / 2);
	copy(f.begin(), f.begin() + n / 2, f1.begin()), copy(f.begin() + n / 2, f.end(), f2.begin());
	copy(g.begin(), g.begin() + n / 2, g1.begin()), copy(g.begin() + n / 2, g.end(), g2.begin());
	vector<ll> t1(n), t2(n), t3(n);
	karatsuba(f1, g1, t1, n / 2), karatsuba(f2, g2, t2, n / 2);
	for (int i = 0; i < n / 2; i++) f1[i] += f2[i];
	for (int i = 0; i < n / 2; i++) g1[i] += g2[i];
	karatsuba(f1, g1, t3, n / 2);
	for (int i = 0; i < n; i++) t3[i] -= t1[i] + t2[i];
	for (int i = 0; i < n; i++)
		c[i] += t1[i], c[i + n] += t2[i], c[i + n / 2] += t3[i];
}

void mul(const vector<ll>& a, const vector<ll>& b, vector<ll>& c) {
	int n = a.size(), m = b.size(), t = max(n, m), p = 1;
	while (p < t) p <<= 1;
	vector<ll> aa(p), bb(p);
	copy(a.begin(), a.end(), aa.begin()), copy(b.begin(), b.end(), bb.begin());
	c.assign(p << 1, 0), karatsuba(aa, bb, c, p), c.resize(n + m - 1);
}

#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

int n, m, k;
vector<pair<int, ll>> v[100009], r[100009];
int cnt[100009];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m >> k;
	for (int i = 1; i <= m; ++ i) {
		int a, b; ll c;
		cin >> a >> b >> c;
		v[a].push_back({b, c});
		r[b].push_back({a, c});
	}

	vector<ll> d(n + 1, MOD * MOD);
	d[n] = 0;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	pq.push({d[n], n});

	while (!pq.empty()) {
		auto [t, p] = pq.top();
		pq.pop();
		if (d[p] != t) continue;
		for (auto [i, c] : r[p]) if (d[p] + c < d[i]) {
				d[i] = d[p] + c;
				pq.push({d[i], i});
			}
	}

	priority_queue<tuple<ll, ll, int>, vector<tuple<ll, ll, int>>, greater<tuple<ll, ll, int>>> pq2;
	pq2.push({d[1], 0, 1});
	vector<ll> ans;

	while (!pq2.empty() && (int)ans.size() < k) {
		auto [t, f, p] = pq2.top();
		pq2.pop();
		if (cnt[p] == k) continue;
		cnt[p] += 1;

		if (p == n) ans.push_back(t);
		for (auto [i, c] : v[p]) {
			pq2.push({f + c + d[i], f + c, i});
		}
	}

	for (auto i : ans) cout << i << " ";
	cout << "\n";
}
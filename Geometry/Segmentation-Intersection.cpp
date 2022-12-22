int sign(ll x) {
    return (x > 0 ? 1 : (x < 0 ? -1 : 0));
}

ll cross(pair<ll, ll> o, pair<ll, ll> a, pair<ll, ll> b) {
    return (a.first - o.first) * (b.second - o.second) - (a.second - o.second) * (b.first - o.first);
}

bool intersect1D(ll a, ll b, ll c, ll d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d);
}

bool intersect2D(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c, pair<ll, ll> d) {
    return intersect1D(a.first, b.first, c.first, d.first)
           && intersect1D(a.second, b.second, c.second, d.second)
           && sign(cross(a, b, c)) * sign(cross(a, b, d)) <= 0
           && sign(cross(c, d, a)) * sign(cross(c, d, b)) <= 0;
}
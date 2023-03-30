pair<ll, ll> extgcd(ll a, ll b) {
  if (b == 0) return {1, 0};
  auto [xp, yp] = extgcd(b, a % b);
  return {yp, xp - a / b * yp};
}
#include <bits/stdc++.h>
using namespace std;
#define ll long long

pair<ll, ll> extgcd(ll a, ll b) {
  if (b == 0) return {1, 0};
  pair<ll, ll> q = extgcd(b, a % b);
  return {q.second, q.first - q.second * (a / b)};
}

int main() {

}
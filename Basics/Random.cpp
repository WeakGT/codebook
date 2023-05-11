#include <random>
#include <chrono>
#include <algorithm>
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
int randint(int lb, int ub) {
  return uniform_int_distribution<int>(lb, ub)(rng);
}
// shuffle(v.begin(), v.end(), rng);

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// #include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using rbtree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// less<T> :  increasing, greater<T> : decreasing
// rb_tree_tag, splay_tree_tag, ov_tree_tag

int main() {
  int x;
  rbtree<int> t, rhs, rhs2;
  t.insert(x);
  t.erase(x); // return 1 or 0
  cout << t.order_of_key(x) << '\n'; // rank
  cout << *t.find_by_order(x) << '\n'; // x-th
  cout << *t.lower_bound(x) << '\n'; // iterator >= x
  cout << *t.upper_bound(x) << '\n'; // iterator > x
  t.join(rhs); // merge // same type, no duplicate elements
  t.split(x, rhs2); // tree : elements <= x, rhs : elements > x
}
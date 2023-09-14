#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cstring>
using namespace std;
int l, w;
vector<pair<int, short>> tree[100000];
bitset<100000> removed;
int current_centroid, BIT[100000];
// Return subtree size internally
// and place the discovered centroid in current_centroid
int find_centroid(const int n, const int u, const int p = -1) {
  if (n == 1) { current_centroid = u; return 0; }
  int subtree_sum = 0;
  for (const auto &[v, w] : tree[u]) if (v != p && !removed[v]) {
      subtree_sum += find_centroid(n, v, u);
      if (current_centroid > -1) return 0;
      if (subtree_sum >= n >> 1) { current_centroid = u; return 0; }
    }
  return subtree_sum + 1;
}
void DFS(const int u, const int p, const int length, const int weight, vector<pair<int, int>> &record) {
  record.emplace_back(weight, length);
  for (const auto &[v, w] : tree[u]) if (v != p && !removed[v])
      DFS(v, u, length + 1, weight + w, record);
}
bool greater_size(const vector<pair<int, int>> &v, const vector<pair<int, int>> &w) {
  return v.size() > w.size();
}
long long centroid_decomposition(const int n, int u) {
  long long ans = 0;
  // Step 1: find the centroid
  current_centroid = -1; find_centroid(n, u);
  removed[u = current_centroid] = true;
  // Step 2: DFS from the centroid (again)
  // and continue the centroid decomposition
  vector<vector<pair<int, int>>> root2subtree_paths;
  for (const auto &[v, w] : tree[u]) if (!removed[v]) {
      root2subtree_paths.emplace_back();
      DFS(v, u, 1, w, root2subtree_paths.back());
      // Sort mainly according to weight
      ranges::sort(root2subtree_paths.back());
      ans += centroid_decomposition(root2subtree_paths.back().size(), v);
    }
  for (const auto &v : root2subtree_paths)
    for (const auto &[weight, length] : v)
      if (length <= l && weight <= w) ++ans;
  // Step 3: optimal merging
  ranges::make_heap(root2subtree_paths, greater_size);
  while (root2subtree_paths.size() > 1) {
    ranges::pop_heap(root2subtree_paths, greater_size);
    // Merge front() (with maybe larger size) and back()
    // Count cross-centroid paths
    memset(BIT, 0, root2subtree_paths.back().size() * sizeof(int));
    auto p = root2subtree_paths.front().crbegin();
    for (auto q = root2subtree_paths.back().cbegin(); q != root2subtree_paths.back().cend(); ++q) {
      int L;
      while (p != root2subtree_paths.front().crend()
             && p->first + q->first > w) {
        L = min(l - p->second,
                static_cast<int>(root2subtree_paths.back().size()));
        while (L > 0) { ans += BIT[L - 1]; L -= L & -L; }
        ++p;
      }
      L = q->second;
      while (L <= static_cast<int>(root2subtree_paths.back().size()))
      {
        ++BIT[L - 1]; L += L & -L;
      }
    }
    while (p != root2subtree_paths.front().crend()) {
      int L = min(l - p++->second, static_cast<int>(root2subtree_paths.back().size()));
      while (L > 0) { ans += BIT[L - 1]; L -= L & -L; }
    }
    // Actually merge the lists
    vector<pair<int, int>> buffer;
    buffer.reserve(root2subtree_paths.front().size() + root2subtree_paths.back().size());
    ranges::merge(root2subtree_paths.front(), root2subtree_paths.back(), back_inserter(buffer));

    root2subtree_paths.pop_back();
    ranges::pop_heap(root2subtree_paths, greater_size);
    root2subtree_paths.back() = move(buffer);
    ranges::push_heap(root2subtree_paths, greater_size);
  }
  return ans;
}
int main() {
  ios_base::sync_with_stdio(false);
  int n; cin >> n >> l >> w;
  for (int i = 1; i < n; ++i) {
    int p; short w; cin >> p >> w;
    tree[--p].emplace_back(i, w);
    tree[i].emplace_back(p, w);
  }
  cout << centroid_decomposition(n, 0) << endl;
}
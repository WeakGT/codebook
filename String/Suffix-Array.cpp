void counting_sort(vector<int> &dest, const vector<int> &src, int bucket_count, function<int(const int&)> f) {
  int *bucket_begin = new int[bucket_count], *buf = new int[src.size()];
  fill(bucket_begin, bucket_begin + bucket_count, 0);
  for (int i = 0; i < src.size(); ++i)
    if ((buf[i] = f(src[i])) + 1 < bucket_count)
      ++bucket_begin[buf[i] + 1];
  partial_sum(bucket_begin, bucket_begin + bucket_count, bucket_begin);
  dest.resize(src.size());
  for (int i = 0; i < src.size(); ++i)
    dest[bucket_begin[buf[i]]++] = src[i];
  delete[] bucket_begin; delete[] buf;
}
#define a 'a'  // The smallest character in the alphabet
#define sz 26  // The size of the alphabet. The alphabet is [a, a + sz)
vector<int> suffix_array(const string &s) {
  vector<int> SA, sa(s.size());
  SA.reserve(s.size()); iota(sa.begin(), sa.end(), 0);
  counting_sort(SA, sa, sz, [&](const int &i) { return s[i] - a; });
  int *R = new int[SA.size()], *r = new int[SA.size()];
  R[SA[0]] = 1;  // R = 0 is reserved for the empty string
  for (int i = 1; i < SA.size(); ++i)
    R[SA[i]] = s[SA[i]] == s[SA[i - 1]] ? R[SA[i - 1]] : i + 1;
  int L = 1;
  while (L < s.size()) {
    auto R2 = [&](const int &i) {
      if (i + L < SA.size()) return R[i + L];
      return 0;  // so that when L = 1, "a" is ordered before "aa"
    };
    counting_sort(sa, SA, SA.size() + 1, R2);
    counting_sort(SA, sa, SA.size(), [&](const int &i) { return R[i] - 1; });
    r[SA[0]] = 1;
    for (int i = 1; i < SA.size(); ++i)
      if (R[SA[i]] == R[SA[i - 1]] && R2(SA[i]) == R2(SA[i - 1]))
        r[SA[i]] = r[SA[i - 1]];
      else r[SA[i]] = i + 1;
    swap(R, r); L <<= 1;
  }
  delete[] R; delete[] r; return SA;
}
#undef a
#undef sz
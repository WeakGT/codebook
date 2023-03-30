// P[2i] := max 2j+1: s[i-j, i+j] is palindromic
// P[2i-1] := max 2j: s[i-j, i+j) is palindromic
// maximal palindrome: s.substr((1 + i - P[i]) >> 1, P[i])
vector<unsigned> Manacher(const string &s) {
  unsigned L = 0, R = 1;
  vector<unsigned> P; P.reserve((s.size() << 1) - 1);
  P.push_back(1);
  for (unsigned i = 1; i < s.size(); ++i)
    for (int j = 0; j < 2; ++j) {
      if (i < R) {
        const int k = ((L + R - i) << 1) - j - 1;
        if (P[k] >> 1 < R - i - j) { P.push_back(P[k]); continue; }
        L = (i << 1) - R + j;
      }
      else R = (L = i) + j;
      while (L > 0 && R < s.size() && s[L - 1] == s[R]) {--L; ++R;}
      P.push_back(R - L);
    }
  return P;
}
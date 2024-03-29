#define pb push_back
const int N = 1e6 + 5;
int F[N];
vector<int> match(string A, string B) {
  vector<int> ans;
  F[0] = -1, F[1] = 0;
  for (int i = 1, j = 0; i < (int)B.size(); F[++i] = ++j) {
    if (B[i] == B[j]) F[i] = F[j]; // optimize
    while (j != -1 && B[i] != B[j]) j = F[j];
  }
  for (int i = 0, j = 0; i < (int)A.size(); ++i) {
    while (j != -1 && A[i] != B[j]) j = F[j];
    if (++j == (int)B.size()) ans.pb(i + 1 - j), j = F[j];
  }
  return ans;
}
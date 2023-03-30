bool rit(auto& x) {
  x = 0; char c = cin.rdbuf()->sbumpc(); bool neg = 0;
  while (!isdigit(c)) {
    if (c == EOF) return 0;
    if (c == '-') neg = 1;
    c = cin.rdbuf()->sbumpc();
  }
  while (isdigit(c))
    x = x * 10 + c - '0', c = cin.rdbuf()->sbumpc();
  return x = neg ? -x : x, 1;
}
void wit(auto x) {
  if (x < 0) cout.rdbuf()->sputc('-'), x = -x;
  char s[20], len = 0;
  do s[len++] = x % 10 + '0'; while (x /= 10);
  while (len) cout.rdbuf()->sputc(s[--len]);
}
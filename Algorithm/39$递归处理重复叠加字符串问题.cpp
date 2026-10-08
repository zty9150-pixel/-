#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;

string s;
int q;

void dfs(ll len, ll k, bool istran)
{
  ll half = len / 2;
  if (len == s.length())
  {
    if (istran)
      cout << char(isupper(s[k - 1]) ? tolower(s[k - 1]) : toupper(s[k - 1])) << ' ';
    else
      cout << s[k - 1] << ' ';
    return;
  }
  if (k > half)
    dfs(half, k - half, !istran);
  else
    dfs(half, k, istran);
}

void solution()
{
  cin >> s >> q;
  while (q--)
  {
    ll k;
    cin >> k;
    ll len = s.length();
    while (len < k)
      len *= 2;
    dfs(len, k, false);
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();
  return 0;
}
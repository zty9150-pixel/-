#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool check(const string &s, int k)
{
  int n = s.size();
  vector<int> used(n, 0);
  for (int i = n - 1; i >= 0; --i)
  {
    if (k > 0 && s[i] == '1')
    {
      used[i] = 1;
      --k;
    }
  }
  int cur = 0;

  for (int i = 0; i < n; ++i)
  {
    if (used[i])
    {
      --cur;
      if (cur < 0)
        return false;
    }
    else
    {
      ++cur;
    }
  }

  return true;
}

void solve()
{
  int n;
  cin >> n;

  string s;
  cin >> s;
  if (n == 1)
  {
    cout << 1 << '\n';
    return;
  }
  int cnt1 = 0;
  for (char c : s)
  {
    if (c == '1')
      ++cnt1;
  }
  int l = 1;
  int r = cnt1 + 1;
  while (r - l > 1)
  {
    int mid = (l + r) / 2;

    if (check(s, mid))
      l = mid;
    else
      r = mid;
  }
  ll ans = 0;
  for (int i = n - 1; i >= 0; --i)
  {
    if (s[i] == '1' && l > 0)
    {
      --l;
    }
    else
    {
      ans += i + 1;
    }
  }

  cout << ans << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  while (T--)
  {
    solve();
  }

  return 0;
}
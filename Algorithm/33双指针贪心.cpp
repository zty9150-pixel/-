#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
// const ll inf = 1e9;
// 长度为k的01串a称为good，当且仅当a[i≠ak-i+1]，i=1,2,..k。
// 给定长度为n的字符串s，问是否能经过不超过300次如下操作使得s变为good:在s的任意位置插入“01”。

string s;

void solution()
{
  int n;
  cin >> n >> s;
  if (s.length() % 2)
  {
    cout << -1 << '\n';
    return;
  }
  int one = 0, zer = 0;
  for (auto &i : s)
  {
    if (i == '1')
      one++;
    if (i == '0')
      zer++;
  }
  if (one != zer)
  {
    cout << -1 << '\n';
    return;
  }
  int l = 0, r = s.length() - 1;
  int ans = 0;
  while (l < r)
  {
    if (s[l] != s[r])
    {
      l++;
      r--;
    }
    else
    {
      if (s[l] == '0')
      {
        s.insert(r + 1, "01");
        ans++;
        l++;
        r++;
      }
      else if (s[l] == '1')
      {
        s.insert(l, "01");
        ans++;
        l++;
        r++;
      }
    }
  }
  cout << ans << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
  {
    solution();
  }

  return 0;
}
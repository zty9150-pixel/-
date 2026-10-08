#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;

int n, m, x, y;

void solve()
{
  cin >> n >> m >> x >> y;
  vector<vector<ll>> a(n + 1, vector<ll>(m + 1, 0));
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= m; ++j)
    {
      int x;
      cin >> x;
      a[i][j] = x + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    }
  }
  ll ans = 0;
  for (int i = x; i <= n; ++i)
  {
    for (int j = y; j <= m; ++j)
    {
      ll sum = a[i][j] - a[i - x][j] - a[i][j - y] + a[i - x][j - y];
      ans = max(ans, sum);
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
    solve();
  }

  return 0;
}

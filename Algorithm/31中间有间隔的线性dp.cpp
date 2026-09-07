#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
// const ll inf = 1e9;

ll n, m, q;
ll t[N], k[N], s[N], pre[N];
ll dp[N];

void solution()
{
  cin >> n >> m >> q;
  for (int i = 1; i <= q; ++i)
  {
    cin >> t[i];
    pre[t[i]]++;
  }
  for (int i = 1; i <= n; ++i)
    pre[i] += pre[i - 1];
  for (int i = 1; i <= m; ++i)
    cin >> k[i] >> s[i];
  for (int i = 1; i <= n; ++i)
  {
    dp[i] = dp[i - 1];
    for (int j = 1; j <= m; ++j)
    {
      ll len = 1ll << k[j];
      if (i < len)
        continue;
      if (pre[i] - pre[i - len] > 0)
        continue;
      dp[i] = max(dp[i], dp[i - len] + s[j]);
    }
  }
  cout << dp[n];
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();

  return 0;
}
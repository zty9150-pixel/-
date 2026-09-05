#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 1001;
const int mod = 1e6 + 7;

int n, m, k;
int dp[N]; // dp表示当前占用j时间时最大利润是多少
int t[110], p[110];

void solution()
{
  cin >> m >> n;
  for (int i = 1; i <= n; ++i)
  {
    cin >> t[i] >> p[i];
  }
  cin >> k;
  for (int i = 1; i <= n; ++i)
  {

    for (int j = t[i]; j <= m; ++j)
    {
      dp[j] = max(dp[j], p[i]);
      if (j - t[i] - k >= 0)
      {
        dp[j] = max(dp[j - t[i] - k] + p[i], dp[j]);
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= m; ++i)
  {
    ans = max(ans, dp[i]);
  }
  cout << ans;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();

  return 0;
}
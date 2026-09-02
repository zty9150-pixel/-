#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int mod = 1e6 + 7;

int n, m;
int a[N];
int dp[N][N];
int pre[N][N];

void solution()
{
  cin >> n >> m;

  for (int i = 1; i <= n; ++i)
    cin >> a[i];

  // 只考虑第1种花
  for (int j = 0; j <= m; ++j)
  {
    if (j <= a[1])
      dp[1][j] = 1;
  }

  // 第1行前缀和
  pre[1][0] = dp[1][0];

  for (int j = 1; j <= m; ++j)
  {
    pre[1][j] = (pre[1][j - 1] + dp[1][j]) % mod;
  }

  // 考虑第2 ~ n种花
  for (int i = 2; i <= n; ++i)
  {
    for (int j = 0; j <= m; ++j)
    {
      int l = j - a[i];

      if (l <= 0)
        dp[i][j] = pre[i - 1][j];
      else
        dp[i][j] = (pre[i - 1][j] - pre[i - 1][l - 1] + mod) % mod;
    }

    pre[i][0] = dp[i][0];

    for (int j = 1; j <= m; ++j)
    {
      pre[i][j] = (pre[i][j - 1] + dp[i][j]) % mod;
    }
  }

  cout << dp[n][m] << '\n';
}
void solution2() // 不做前缀和，直接再加一重循环
{
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  dp[0][0] = 1;
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 0; j <= m; ++j)
    {
      for (int k = 0; k <= j && k <= a[i]; ++k)
      {
        dp[i][j] = (dp[i][j] + dp[i - 1][j - k] + mod) % mod;
      }
    }
  }
  cout << dp[n][m] << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();

  return 0;
}
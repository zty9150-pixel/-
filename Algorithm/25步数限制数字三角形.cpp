#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int mod = 1e6 + 7;

int n, m;
int a[N][N];
int dp[N][N][N];
int pre[N][N];

void solution()
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= i; ++j)
    {
      cin >> a[i][j];
    }
  }
  for (int i = n; i >= 1; --i)
  {
    for (int j = 1; j <= i; ++j)
    {
      for (int k = 0; k <= n - i; ++k)
      {
        if (k > 0)
          dp[i][j][k] = max(dp[i + 1][j][k] + a[i][j], dp[i + 1][j + 1][k - 1] + a[i][j]);
        else
          dp[i][j][k] = dp[i + 1][j][k] + a[i][j];
      }
    }
  }
  if (n % 2)
  {
    cout << dp[1][1][(n - 1) / 2];
  }
  else
  {
    cout << max(dp[1][1][(n - 1) / 2], dp[1][1][(n - 1) / 2 + 1]);
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();

  return 0;
}
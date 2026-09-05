#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 110;
const int mod = 1e6 + 7;

int n, m, k;
int dp[N][N][N]; // dp表示当前占用j时间时最大利润是多少

void solution()
{
  cin >> n >> m;
  dp[0][0][2] = 1;
  for (int i = 0; i <= n; ++i) // 店
  {
    for (int j = 0; j <= m; ++j) // 花
    {
      for (int k = 0; k <= 100; ++k)
      {
        if (k % 2 == 0 && i)
        {
          dp[i][j][k] += dp[i - 1][j][k / 2];
        }
        if (j)
          dp[i][j][k] += dp[i][j - 1][k + 1];
      }
    }
  }
  cout << dp[n][m - 1][1];
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();

  return 0;
}
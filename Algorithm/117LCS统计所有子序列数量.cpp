/*
题目：Two

题目描述：
给定两个序列 A、B，分别从中选取任意子序列 A'、B'（不要求连续）。
求有多少对 (A', B') 满足两个子序列完全相同。
注意：不同位置选出的相同数值序列，仍然算不同的方案。
答案对 1e9+7 取模。

思路：二维 DP + 容斥

1. 状态定义：
   dp[i][j] 表示：
   A 的前 i 个元素与 B 的前 j 个元素中，
   能组成多少对相同的非空子序列。

2. 初始化：
   dp[0][j] = dp[i][0] = 0
   任意一个序列为空，都无法组成相同的非空子序列。

3. 状态转移：

   情况一：a[i] == b[j]

   两个末尾元素相同，可以同时选取，也可以不选取。

   dp[i][j] = dp[i-1][j] + dp[i][j-1] + 1

   这里 +1 表示新增一对：
   分别只选取 a[i] 和 b[j]，组成相同的单元素序列。

   情况二：a[i] != b[j]

   不可能同时选取两个末尾元素，因为它们不相等。

   使用容斥原理：
   dp[i-1][j]：不选 a[i]
   dp[i][j-1]：不选 b[j]
   dp[i-1][j-1]：两边末尾都不选，被重复计算一次。

   dp[i][j] = dp[i-1][j] + dp[i][j-1]
              - dp[i-1][j-1]

4. 答案：
   dp[n][m]

复杂度：
时间复杂度：O(n*m)
空间复杂度：O(n*m)

注意：
每次状态转移都需要对 1e9+7 取模，
容斥时注意处理负数。
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;

int n, m;
void solve()
{
  vector<int> a(n + 1);
  vector<int> b(m + 1);
  vector<vector<int>> dp(n + 1, vector<int>(m + 1));

  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= m; ++i)
    cin >> b[i];

  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= m; ++j)
    {
      if (a[i] == b[j])
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1] + 1;
      else
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1] + 1 - dp[i - 1][j - 1];
    }
  }
  cout << dp[n][m] << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // int t;
  // cin >> t;
  // while (t--)
  {
    while (cin >> n >> m)
      solve();
  }

  return 0;
}

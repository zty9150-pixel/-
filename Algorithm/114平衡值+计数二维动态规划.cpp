/*
题目：
    有 C 个挂钩，位置为 c[i]，可能在天平中心左侧或右侧。
    有 G 个砝码，重量为 w[i]。

    每个砝码必须选择一个挂钩放置，同一个挂钩可以放多个砝码。
    要求所有砝码产生的力矩之和为 0。

    求满足天平平衡的放置方案总数。

思路：二维 DP（计数型 DP）

    1. 状态设计：

       dp[i][j] 表示前 i 个砝码全部放置完毕，
       总力矩为 j 的方案数。

       由于力矩可能为负数，需要 OFFSET 偏移量。

    2. 力矩计算：

       一个砝码放在位置 c[k] 上，产生的力矩为：

       w[i] * c[k]

       正数表示右侧，负数表示左侧。

    3. 状态转移：

       枚举当前砝码 i，
       枚举之前产生的总力矩 j，
       再枚举当前砝码可以放置的挂钩 k。

       dp[i][j + w[i] * c[k]] += dp[i-1][j];

       即：
       当前方案数累加上前 i-1 个砝码产生的方案数。

    4. 初始状态：

       dp[0][OFFSET] = 1;

       一个砝码都不放时，力矩为 0，
       存在一种空方案。

    5. 最终答案：

       dp[G][OFFSET]

       即所有砝码放置完毕，力矩恰好为 0 的方案数。

数值范围：

    G <= 20
    w[i] <= 25
    |c[i]| <= 15

    总力矩绝对值最大不超过：

    20 * 25 * 15 = 7500

    因此 OFFSET = 7500，
    数组长度至少为 15001。

复杂度：

    时间 O(G * C * 15001)
    空间 O(G * 15001)

注意：

    这是计数型 DP，不是最优化 DP。
    因此转移使用 +=，而不是 min/max。

    每个砝码必须使用一次，所以每一层只能
    从上一层 dp[i-1] 转移，不能在同一层重复使用砝码。

    同一个挂钩可以放置多个砝码。
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int OFFSET = 7500;
const int N = 15001;

void solve()
{
  int C, G;
  cin >> C >> G;

  vector<int> c(C), w(G);

  for (int &x : c)
    cin >> x;

  for (int &x : w)
    cin >> x;

  vector<vector<ll>> dp(G + 1, vector<ll>(N, 0));

  dp[0][OFFSET] = 1;

  for (int i = 1; i <= G; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      if (dp[i - 1][j] == 0)
        continue;

      for (int k = 0; k < C; ++k)
      {
        int nj = j + w[i - 1] * c[k];

        if (nj >= 0 && nj < N)
          dp[i][nj] += dp[i - 1][j];
      }
    }
  }

  cout << dp[G][OFFSET] << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();
  return 0;
}
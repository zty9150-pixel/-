/*
题目：
有 n 个任务，每个任务有两个属性：
ci：完成任务获得的分数系数。
pi：完成任务后体力下降的百分比。

初始体力 S = 1。

按照 1 到 n 的顺序处理任务，每个任务可以选择：
1. 放弃：不发生任何变化。
2. 完成：获得 S * ci 分数，体力变为 S * (1-pi/100)。

求最大总得分。

思路：倒序 DP + 线性性质

原始想法：
dp[S] = 当前体力为 S 时能够获得的最大分数。

问题：
体力是浮点数，每次完成任务后都会发生变化，
无法像普通背包一样枚举体力状态。

优化关键：
后续任务的得分与当前体力 S 成正比。

因此：
如果初始体力为 1 时，后续任务最多获得 dp[i+1] 分，
那么初始体力为 S 时，最多获得 S * dp[i+1] 分。

状态定义：
dp[i] = 从第 i 个任务开始，
        初始体力为 1 时能够获得的最大分数。

初始化：
dp[n+1] = 0

状态转移：

选择一：放弃当前任务
dp[i] = dp[i+1]

选择二：完成当前任务
立即获得 ci 分。
完成后体力变为 1-pi/100。

后续最多获得：
(1-pi/100) * dp[i+1]

因此：
dp[i] = max(
    dp[i+1],
    ci + (1-pi/100) * dp[i+1]
)

最终答案：
dp[1]

空间优化：
每次只依赖 dp[i+1]，
因此只需要一个 double 变量倒序更新。

注意：
1. 必须倒序处理，因为依赖后面的任务。
2. 使用 double 保存浮点数。
3. 输出时使用 fixed 和 setprecision(10)。

复杂度：
时间：O(n)
空间：O(n) 保存任务，DP 本身 O(1)。

核心技巧：
利用后续收益与当前体力成正比的线性性质，
消除原本需要枚举的浮点体力状态。
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;

void solve()
{
  int n;
  cin >> n;

  vector<int> c(n + 1);
  vector<int> p(n + 1);
  vector<double> dp(n + 1);

  for (int i = 1; i <= n; ++i)
    cin >> c[i] >> p[i];

  dp[n] = c[n];

  for (int i = n - 1; i >= 1; --i)
  {
    dp[i] = max(dp[i + 1], c[i] + (1.0 - p[i] / 100.0) * dp[i + 1]);
  }

  cout << fixed << setprecision(10) << dp[1] << '\n';
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
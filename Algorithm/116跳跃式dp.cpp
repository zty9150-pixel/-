/*
题目：CF - Mushroom Toxicity（蘑菇毒性）

题目描述：
给定 n 个蘑菇，每个蘑菇毒性为 a[i]，角色最大承受毒性为 x。
选择一个连续区间 [l,r]，从左到右依次吃蘑菇。

每吃一个蘑菇，当前毒性 g += a[i]：
- 如果 g <= x，继续吃。
- 如果 g > x，毒性清零，继续吃。

求有多少个区间 [l,r]，吃完后最终毒性不为 0。

思路：
1. 定义 dp[i]：以 i 为左端点，最终毒性不为 0 的区间数量。
2. 找到从 i 开始，第一个使毒性超过 x 的位置 p。
3. 由于 a[i] 均为正数，可以用前缀和 + 二分查找 p。

状态转移：
- [i,p-1] 内的所有区间均合法，共 p-i 个。
- 吃到 p 时毒性清零，该区间不合法。
- 从 p+1 开始，之前的毒性影响已经消失，
  后续方案可以直接复用 dp[p+1]。

因此：
dp[i] = p-i + dp[p+1]

如果不存在 p：
dp[i] = n-i+1

倒序计算 dp，最后累加所有 dp[i]。

题解：
1. 前缀和 sum[i] = sum[i-1] + a[i]。
2. 第一个超过毒性上限的位置满足：
   sum[p] > sum[i-1] + x
3. 使用 upper_bound 查找 p。
4. 倒序 DP，统计答案。

代码：
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve()
{
  int n;
  ll x;
  cin >> n >> x;

  vector<ll> sum(n + 1), dp(n + 2);

  for (int i = 1; i <= n; ++i)
  {
    ll a;
    cin >> a;
    sum[i] = sum[i - 1] + a;
  }

  ll ans = 0;

  for (int i = n; i >= 1; --i)
  {
    int p = upper_bound(sum.begin(), sum.end(),
                        sum[i - 1] + x) -
            sum.begin();

    if (p == n + 1)
      dp[i] = n - i + 1;
    else
      dp[i] = p - i + dp[p + 1];

    ans += dp[i];
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
    solve();

  return 0;
}

/*
复杂度：
时间：O(n log n)
空间：O(n)

知识点：
1. 前缀和 + 二分查找。
2. 倒序 DP。
3. 利用毒性清零的性质跳过中间状态，复用后续 DP。
4. 毒性值最大 1e9，不适合直接作为二维 DP 的下标。

核心：
状态重置后，之前的历史不再影响后续结果，
可以直接跳转到重置位置之后的 DP 状态。
*/
/*
题目：
给定一个长度为 n 的整数数组 a。
如果区间 [l,r] 的元素和为 0，则称其为美丽区间。
求最多能选出多少个互不重叠的美丽区间。

思路一：前缀和 + 贪心

1. sum 表示当前前缀和。
2. 使用 set 记录当前尚未选取区间内出现过的前缀和。
3. 初始化 st[0] = true。
4. 从左向右遍历：
   - sum += a[i]
   - 如果 sum 已经出现过，说明存在一个区间和为 0。
   - ans++，选择当前结束的区间。
   - 清空 set，sum = 0，重新开始统计。
   - 否则将 sum 加入 set。

贪心正确性：
每次选择最早结束的零和区间。
这样可以给后续区间留下尽可能多的空间。
属于最早结束时间优先的区间调度贪心。

思路二：DP + 前缀和 + 哈希表

定义：
dp[i] = 前 i 个元素中最多能选出的不重叠零和区间数量。

设 sum[i] 为前缀和。

如果 sum[i] == sum[j]：
说明区间 [j+1,i] 的和为 0。

状态转移：
dp[i] = max(dp[i-1], dp[j]+1)

使用 map 维护：
mp[x] = 前缀和为 x 的位置中最大的 dp 值。

转移：
dp[i] = max(dp[i-1], mp[sum]+1)
mp[sum] = max(mp[sum], dp[i])

注意：
1. 初始 mp[0] = 0。
2. 前缀和使用 long long。
3. unordered_map 最坏可能退化，map 可以保证 O(log n)。

复杂度：
贪心 + set：O(n log n)
DP + map：O(n log n)
空间复杂度：O(n)
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;

void solve()
{
  int n;
  cin >> n;

  vector<int> a(n + 1);
  map<ll, int> mp;
  vector<int> dp(n + 1, 0);

  for (int i = 1; i <= n; ++i)
    cin >> a[i];

  mp[0] = 0;
  ll sum = 0;

  for (int i = 1; i <= n; ++i)
  {
    sum += a[i];
    dp[i] = dp[i - 1];
    if (mp.count(sum))
      dp[i] = max(dp[i], mp[sum] + 1);

    mp[sum] = dp[i];
  }

  cout << dp[n] << '\n';
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
/*
E - Orray（前缀 OR 字典序最大化）

【题意】
给定 n 个非负整数，重新排列数组，使得前缀 OR 数组字典序最大。
bi = a1 | a2 | ... | ai

【贪心思路】
维护当前前缀 OR：cur。

每次遍历所有未使用的元素，计算：
tmp = cur | a[i]

选择使 tmp 最大的元素放到下一个位置，更新 cur。

【正确性】
字典序比较优先看第一个不同的位置，因此每次都应该使当前前缀 OR 最大。
选择使 cur | a[i] 最大的元素，即可保证当前位最优。

【关键优化】
OR 运算具有单调性：
1. 只能将二进制位从 0 变成 1。
2. 已经为 1 的位不会变回 0。
3. 每次选择都必须让 cur 严格增大。

由于 ai <= 1e9 < 2^30，最多只有 30 个有效二进制位。
因此 cur 最多严格增大 30 次。

当不存在能够使 cur 增大的元素时，说明剩余元素无论如何排列，都不会改变后续前缀 OR，可以直接输出。

【复杂度】
时间复杂度：O(30n) = O(n)
空间复杂度：O(n)
*/

#include <bits/stdc++.h>
using namespace std;

void solve()
{
  int n;
  cin >> n;

  vector<int> a(n);
  for (auto &x : a)
    cin >> x;

  int cur = 0;
  vector<int> ans;
  vector<bool> vis(n, false);

  for (int k = 0; k < 30; ++k)
  {
    int pos = -1;
    int mx = cur;

    for (int i = 0; i < n; ++i)
    {
      if (!vis[i] && (cur | a[i]) > mx)
      {
        mx = cur | a[i];
        pos = i;
      }
    }

    if (pos == -1)
      break;

    ans.push_back(a[pos]);
    vis[pos] = true;
    cur = mx;
  }

  // 剩余元素不会改变前缀 OR，直接输出
  for (int i = 0; i < n; ++i)
  {
    if (!vis[i])
      ans.push_back(a[i]);
  }

  for (auto x : ans)
    cout << x << ' ';
  cout << '\n';
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
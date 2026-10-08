/*
题目：
给定长度N的整数序列A，求**非空连续子数组**，子数组总和等于0的数量。
只要起始/终止下标不同就算不同方案，哪怕子数组里数字一样。

约束：
1 ≤ N ≤ 2e5
-1e9 ≤ A[i] ≤ 1e9

输入：
N A1 A2 ... AN

输出：
和为0的非空连续子数组总数

样例1
输入：6 1 3 -4 2 2 -2
输出：3
满足的子数组：[1,3,-4], [-4,2,2], [2,-2]

样例2
输入：7 1 -1 1 -1 1 -1 1
输出：12

样例3
输入：5 1 -2 3 -4 5
输出：0

核心思路：前缀和 + 哈希表计数
设 s[0]=0，s[i]=A1+A2+...+Ai
区间[l,r]和为0 ⇔ s[r] == s[l-1]
哈希表记录前缀和s出现过多少次，每次累加之前出现的次数。
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  unordered_map<ll, ll> cnt;
  cnt[0] = 1;

  ll sum = 0, ans = 0;

  for (int i = 0; i < n; ++i)
  {
    ll x;
    cin >> x;

    sum += x;
    ans += cnt[sum];
    cnt[sum]++; // 或者用pre[l - 1] == pre[r] 出现多少次二维遍历数组 但是是O（n^2）会超时
                // 也可以算出所有前缀和排序， 0 1 0 1 0 -> 0 0 0 1 1,0可以组成3个重复对数，1可以组成1对重复对数
  }

  cout << ans << '\n';
  return 0;
}

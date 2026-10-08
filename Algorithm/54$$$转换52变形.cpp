/*
题型：前缀和 + 哈希表统计子数组数量 O(n)
题意：
数组a元素是0~9，求【好子数组】个数。
好子数组定义：子数组和 = 子数组长度
∑a[l..r] = r-l+1
输入：t组用例；n；一串数字字符串，每个字符代表a[i]
sum n ≤ 1e5

*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;

int n;
string s;

void solve()
{
  cin >> n;
  cin >> s;
  unordered_map<int, int> um;
  um[0] = 1;
  ll sum = 0;
  ll ans = 0;
  for (auto &c : s)
  {
    int x = c - '0' - 1; //   ∑a[l..r] = r-l+1    =>    ∑a[l..r] - (r-l+1) = 0    =>    ∑a[l..r] - ∑1    =>    ∑(a_i - 1)
    sum += x;            // 实际推导 ： 要求每个数都是1才能拿到好数组，那就是求∑a_i是否可以为n，即∑(a_i - 1)是否可以为0
    ans += um[sum];
    um[sum]++;
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
  {
    solve();
  }

  return 0;
}

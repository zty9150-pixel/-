
#include <bits/stdc++.h>
using namespace std;

/*
题目：
N个盒子排成一行，从左到右编号1~N。
每个盒子可以选择放球/不放球。

定义合法方案(good)：
对每个 i (1<=i<=N)：所有编号是 i 的倍数的盒子中，球的总数 mod 2 == a[i]
a[i]只能是0或1

问：是否存在合法放球方案？存在则输出任意一组；不存在输出-1。

输入：
N  a1 a2 ... aN

输出：
M  b1 b2 ... bM
M是放球的盒子数量，b数组是放球盒子的编号，顺序任意

限制：
1 ≤ N ≤ 2e5
a_i ∈ {0,1}

样例1
输入：3 1 0 0
输出：1 1
解释：只在1号盒子放球
i=1：倍数1,2,3，总球数1 mod2=1 == a1
i=2：倍数2，总球数0 == a2
i=3：倍数3，总球数0 == a3

样例2
输入：5 0 0 0 0 0
输出：0
全部不放球，满足条件
*/

//    0/1的模2加法 == 异或   （1%2）+ （1%2）+（0%2）= 1^1^0

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n + 1), b(n + 1);

  for (int i = 1; i <= n; ++i)
    cin >> a[i];

  for (int i = n; i >= 1; --i)
  {
    b[i] = a[i];

    for (int j = i * 2; j <= n; j += i) // 求n个数的倍数之和时间复杂度只有nlogn
      b[i] ^= b[j];
  }

  vector<int> ans;
  for (int i = 1; i <= n; ++i)
  {
    if (b[i])
      ans.push_back(i);
  }

  cout << ans.size();
  for (int x : ans)
    cout << ' ' << x;
  cout << '\n';

  return 0;
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
题目：I - Factorials and Powers of Two

一、题意

给定正整数 n，将 n 表示为若干个互不相同的 powerful numbers 之和，
求最少需要多少个数。

powerful number 满足：
1. 是 2 的幂：1, 2, 4, 8, ...
2. 或者是阶乘：0!, 1!, 2!, 3!, ...

二、核心思路：二进制枚举 + popcount

1. 不超过 1e12 的阶乘中，只需要考虑 3! 到 14!。

   0! = 1，1! = 1，2! = 2。
   这些数已经是 2 的幂，因此不需要重复考虑。

2. 阶乘只有 12 个，可以用二进制枚举所有选择方案：
   mask 的第 i 位为 1，表示选择 fac[i]。

3. 计算选择的阶乘之和 sum。
   如果 sum > n，该方案不合法。

4. 剩余部分 rem = n - sum。
   rem 可以表示成若干个互不相同的 2 的幂之和。

5. rem 的二进制中有多少个 1，就需要多少个 2 的幂。

   最少使用数量：
   popcount(mask) + popcount(rem)

6. 枚举所有阶乘选择方案，取最小值。

三、为什么 popcount(rem) 是最少数量？

任意整数的标准二进制表示中，每个为 1 的位对应一个 2 的幂。

例如：
13 = 8 + 4 + 1 = (1101)₂

所以 13 需要 3 个不同的 2 的幂。

由于不同的 2 的幂各使用一次时不会进位，
其二进制表示是唯一的，因此所需数量就是 popcount(rem)。

四、正确性证明

1. 完备性：
   所有可能选择的阶乘子集都被二进制枚举覆盖。

2. 剩余部分最优：
   固定阶乘子集后，剩余值唯一确定为 n - sum。
   用 popcount 可以得到表示该剩余值所需的最少 2 的幂数量。

3. 全局最优：
   枚举所有阶乘子集，计算每种方案的最少总数并取最小值，
   因此得到全局最优解。

五、复杂度

阶乘数量为 12。

时间复杂度：O(2^12 * 12)
空间复杂度：O(12)

六、易错点

1. n 必须使用 long long，因为 n <= 1e12。
2. 阶乘数组必须使用 long long，13! 已超过 int 范围。
3. 使用 __builtin_popcountll(rem)，不能使用 popcount(int) 统计长整数。
4. mask = 0 也必须枚举，表示不选择任何阶乘。
5. 不需要判断无解，因为任何正整数都可以用不同的 2 的幂表示。
*/

void solve()
{
  ll n;
  cin >> n;

  vector<ll> fac;
  ll x = 1;

  // 生成 3! 到 14!
  for (int i = 1; i <= 14; ++i)
  {
    x *= i;
    if (i >= 3)
      fac.push_back(x);
  }

  int ans = INT_MAX;

  // 枚举 12 个阶乘的所有选择方案
  for (int mask = 0; mask < (1 << 12); ++mask)
  {
    ll sum = 0;

    for (int j = 0; j < 12; ++j)
    {
      if ((mask >> j) & 1)
        sum += fac[j];
    }

    if (sum > n)
      continue;

    ll rem = n - sum;

    int cnt = __builtin_popcount(mask) + __builtin_popcountll(rem);

    ans = min(ans, cnt);
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

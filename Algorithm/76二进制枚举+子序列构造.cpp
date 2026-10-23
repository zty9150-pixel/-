
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
题目：H - Make a Square

一、核心思路：二进制枚举 + 子序列构造

1. 每次操作可以删除 n 中任意一位数字，最终保留的数字必须是正整数，
   且不能有前导零。
2. n <= 2e9，最多只有 10 位，因此可以枚举每一位保留或删除的所有方案。
3. 使用二进制状态 mask 表示选择方案：
   - 第 j 位为 1：保留原数字的第 j 位。
   - 第 j 位为 0：删除原数字的第 j 位。
4. 枚举所有非空状态，按照原数字从左到右的顺序构造新数字 x。
5. 判断 x 是否为完全平方数，取删除次数的最小值。

二、为什么使用字符串构造？

使用字符串 s 保存原数字，方便按照原顺序提取每一位，
避免使用 pow(10, j) 计算位数。

三、注意事项

1. mask 必须非空，不能把一位都不保留的情况当成答案。
2. 不能保留以 0 开头的子序列。
   因为转换成整数时，"04" 会变成 4，无法识别前导零。
3. 题目要求正整数，所以 0 不能作为答案。
4. 判断完全平方数时，使用整数平方根并验证 root * root == x，
   不要只依赖浮点数开方结果。
5. 删除次数 = 原数字位数 - 保留位数
             = len - __builtin_popcount(mask)。

四、正确性证明

1. 完备性：
   每一位只有保留和删除两种选择，二进制枚举覆盖所有非空选择方案。
2. 合法性：
   排除前导零和 0，并且只接受完全平方数，因此留下的结果符合题意。
3. 最优性：
   对每个合法平方数计算删除次数，并取最小值，
   所以得到的就是最少操作次数。
4. 如果不存在合法平方数，输出 -1。

五、复杂度分析

设数字长度为 L，L <= 10。

时间复杂度：O(2^L * L)
空间复杂度：O(L)

数据范围很小，可以直接枚举。
*/

void solve()
{
  string s;
  cin >> s;

  int len = s.size();
  int ans = INT_MAX;

  // 枚举所有非空的保留状态
  for (int mask = 1; mask < (1 << len); ++mask)
  {
    ll x = 0;
    bool valid = true;

    // 按原数字从左到右构造子序列
    for (int j = 0; j < len; ++j)
    {
      if ((mask >> j) & 1)
      {
        int digit = s[j] - '0';

        // 第一个保留的数字不能为 0
        if (x == 0 && digit == 0)
        {
          valid = false;
          break;
        }

        x = x * 10 + digit;
      }
    }

    // 排除前导零以及不合法的构造
    if (!valid || x == 0)
      continue;

    // 判断 x 是否为完全平方数
    ll root = sqrtl(x);
    if (root * root == x)
    {
      // 删除次数 = 原长度 - 保留位数
      int del = len - __builtin_popcount(mask);
      ans = min(ans, del);
    }
  }

  cout << (ans == INT_MAX ? -1 : ans) << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();
  return 0;
}

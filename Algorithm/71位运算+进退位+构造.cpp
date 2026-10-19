/*
题目：Bitwise Balancing
类型：位运算 / 逐位贪心 / 二进制构造 / 进位与借位

一、题目大意

给定 B、C、D，寻找非负整数 a，使得：

    (a | B) - (a & C) = D

如果不存在合法的 a，输出 -1。

二、核心思路：从 a = 0 开始，逐位构造

当 a = 0 时：

    (0 | B) - (0 & C) = B

所以初始令：

    sum = B

之后考虑将 a 的第 i 位从 0 变成 1，
观察整个表达式会发生什么变化。

设：

    w = 2^i
    b = B 的第 i 位
    c = C 的第 i 位

三、推导每一位的变化量 del

当 a 的第 i 位从 0 变成 1 时：

    OR 部分的变化：
        (1 | b) - (0 | b)

    AND 部分的变化：
        (1 & c) - (0 & c)

由于原表达式是 OR - AND，所以：

    del = [(1 | b) - (0 | b)
          - (1 & c) + (0 & c)] * 2^i

分类讨论：

1. b = 0，c = 0

   OR 增加 2^i，AND 不变。

       del = +2^i

2. b = 1，c = 1

   OR 不变，AND 增加 2^i。

       del = -2^i

3. b != c

   OR 和 AND 的变化相互抵消，
   整个表达式不变。

       del = 0

因此：

    del 只能是 +2^i、-2^i 或 0。

四、为什么从低位向高位构造？

第 i 位的变化量是：

    del ∈ {-2^i, 0, +2^i}

它是 2^i 的整数倍。

因此，修改第 i 位及更高位，
不会影响结果模 2^i 的余数。

换句话说：

    更高位的选择不会破坏已经确定的低位。

所以按照：

    第 0 位 -> 第 1 位 -> ... -> 第 60 位

依次构造。

五、逐位贪心

初始：

    sum = B
    a = 0

处理第 i 位时：

1. 如果 sum 的第 i 位与 D 的第 i 位相同：

       不需要修改，令 a_i = 0。

2. 如果 sum 的第 i 位与 D 的第 i 位不同：

       必须尝试翻转当前位。

   如果 del != 0：

       令 a_i = 1
       sum += del

   如果 del == 0：

       当前位无法改变，而更高位也无法修正这一位，
       因此无解，输出 -1。

六、为什么加上 del 可以翻转当前位？

假设当前位不同。

如果 del = +2^i：

    sum 加上 2^i，当前位翻转，
    可能产生进位，但只影响更高位。

如果 del = -2^i：

    sum 减去 2^i，当前位翻转，
    可能产生借位，但只影响更高位。

因此两种情况都能修正当前位，
而不破坏已经确定的低位。

七、正确性证明

维护不变量：

处理完第 i 位后，sum 与 D 的低 i+1 位完全相同。

初始处理第 0 位之前，不变量自然成立。

处理第 i 位时：

1. 如果当前位已经相同，则保持 a_i = 0。
2. 如果当前位不同且 del != 0，则选择 a_i = 1，
   使当前位翻转。
3. 如果当前位不同但 del = 0，
   则当前位无法修正。

由于更高位的变化都是 2^(i+1) 的倍数，
无法改变低 i+1 位。

所以，如果某一位无法修正，就一定无解；
否则逐位构造完成后，sum = D。

八、C++ 实现要点

    long long B, C, D;
    long long sum = B;
    long long ans = 0;

    for (int i = 0; i <= 60; ++i)
    {
        long long w = 1LL << i;
        int b = (B >> i) & 1;
        int c = (C >> i) & 1;

        long long del = 0;

        if (b == 0 && c == 0)
            del = w;
        else if (b == 1 && c == 1)
            del = -w;

        if (((sum >> i) & 1) != ((D >> i) & 1))
        {
            if (del == 0)
            {
                cout << -1 << '\\n';
                return;
            }

            ans |= w;
            sum += del;
        }
    }

    cout << (sum == D ? ans : -1) << '\\n';

九、复杂度

时间复杂度：O(61)，即 O(1)。
空间复杂度：O(1)。

十、易错点

1. B、C、D、sum、ans 必须使用 long long。
2. 使用 1LL << i，不要使用 pow(2, i)。
3. del 可能为负数，不是只有增加。
4. 必须从低位向高位构造。
5. 只有当前位不同时，才需要考虑选择 a_i = 1。
6. 当前位不同且 del == 0 时，一定无解。
7. 最后检查 sum == D，确保整个表达式满足要求。

十一、核心总结

初始结果为 B。

每设置 a 的一位，就让结果增加、减少或不变。

从低位向高位：
    当前位相同 -> 不修改；
    当前位不同 -> 尝试用 del 翻转；
    无法翻转 -> 无解。

关键思想：
逐位贪心 + 二进制权值 + 低位不变量。
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll B, C, D;

void solve()
{
  cin >> B >> C >> D;
  ll ans = 0, sum = B;

  for (int i = 0; i < 61; ++i)
  {
    ll b = (B >> i) & 1;
    ll c = (C >> i) & 1;
    ll m = 1LL << i;
    ll del = ((1 | b) - (0 | b) - (1 & c) + (0 & c)) * m;

    if (((sum >> i) & 1) != ((D >> i) & 1))
    {
      sum += del;
      ans |= m;
    }
  }
  if (sum != D || ans > (1LL << 61))
  {
    cout << -1 << '\n';
    return;
  }
  else
  {
    cout << ans << '\n';
  }
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

/*
题目：Maximize XOR, Minimize Operations
考点：位运算、贪心、二进制构造

一、操作性质
每次操作：x -= 1, y += 1
因此 x + y = S 始终不变。

设操作后两个数为 a, b：
a + b = S
a = x - k
b = y + k

操作次数：
k = x - a

二、利用异或公式转化目标
a ^ b = (a + b) - 2 * (a & b)
      = S - 2 * (a & b)

因为 S 固定，所以 a & b 越小，异或越大。
当 a & b = 0 时，异或最大，最大值为 S。

三、a & b = 0 的二进制性质
a、b 的每一位不能同时为 1。
因此 a + b 不会产生进位，即：
S = a | b

所以 a 中所有为 1 的位，都必须是 S 中为 1 的位。
也就是：
(a & S) == a

四、转化为寻找最大的 a
需要满足：
1. a <= x，因为 x 只能减少。
2. (a & S) == a，即 a 是 S 的子掩码。

因为操作次数 k = x - a，
所以 a 越大，操作次数越少。

最终问题：
寻找不超过 x 的最大 S 的子掩码。

五、贪心构造
从高位到低位枚举二进制位 i：

1. 如果 S 的第 i 位是 0：
   a 的这一位只能为 0。

2. 如果 S 的第 i 位是 1：
   尝试将 2^i 加入 a。

3. 如果 a + 2^i <= x：
   就保留这一位，即 a += 2^i。
   否则不选这一位。

为什么从高位开始？
高位的权值更大。优先选择能加入且不超过 x 的高位，
可以保证最终得到最大的合法 a。

六、正确性证明
1. 任意合法的最终状态都满足 a <= x。
2. 为了使 a & b = 0，a 只能选择 S 中为 1 的位。
3. 贪心从高位到低位，优先选择可行的最高位；
   如果选择该位会使 a > x，那么任何保留该位的方案
   都不可能合法。因此贪心构造出最大的合法 a。
4. 因为操作次数 k = x - a，最大的 a 对应最少操作次数。
5. 此时 a & b = 0，因此最大异或值为 S。

七、输出
最大异或值：S = x + y
最少操作次数：x - a

时间复杂度：O(log S)
空间复杂度：O(1)
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve()
{
    ll x, y;
    cin >> x >> y;

    ll s = x + y;
    ll a = 0;

    for (int i = 29; i >= 0; --i)
    {
        ll bit = 1LL << i;

        if ((s & bit) && a + bit <= x)
            a += bit;
    }

    cout << s << ' ' << x - a << '\n';
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

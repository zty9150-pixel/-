
/*
题目：E - 分数博弈
考点：博弈论、数学转换、差值构造

一、题目说明
    给定两个整数 p、q，Alice 和 Bob 轮流操作，Alice 先手。

    每次可以选择：
    1. p--（p > 0）
    2. q--（q > 1）

    当 p = 0 且 q = 1 时，游戏结束。

    如果游戏过程中任意时刻 p/q = 2/3，则 Bob 获胜；
    否则 Alice 获胜。

    双方均采用最优策略，判断获胜者。

二、差值转换
    Bob 的获胜条件：
        p/q = 2/3
        => 3p = 2q
        => 3p - 2q = 0

    定义 d = 3p - 2q，Bob 的目标就是让 d = 0。

    两种操作对 d 的影响：
    1. p--：d' = 3(p-1)-2q = d-3
    2. q--：d' = 3p-2(q-1) = d+2

三、Bob 必胜区间：2/3 < p/q < 1

    由 p/q > 2/3：
        3p > 2q => d > 0

    由 p/q < 1：
        p < q
        => 3p-2q < p
        => d < p

    因此：
        0 < d < p < q

    Bob 采用与 Alice 相反的操作：
    - Alice 减 p，Bob 减 q
    - Alice 减 q，Bob 减 p

    每轮双方各操作一次：
        (p,q) -> (p-1,q-1)

    差值变化：
        d' = 3(p-1)-2(q-1)
           = 3p-2q-1
           = d-1

    因此每轮 d 减少 1，经过 d 轮必然变为 0。

    又因为初始 d < p < q，
    所以在 d 变为 0 前，操作始终合法。

    因此 Bob 必胜。

四、其他情况
    1. p/q < 2/3：
       Alice 优先减 p，使 d 保持负数，避免 d = 0。

    2. p/q >= 1：
       Alice 优先减 q，使 d 保持正数，避免 d = 0。

    3. p/q = 2/3：
       已满足 Bob 的获胜条件。

五、最终结论
    Bob 必胜当且仅当：
        2q <= 3p < 3q

    否则 Alice 获胜。

复杂度：
    时间 O(1)
    空间 O(1)
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve()
{
    ll p, q;
    cin >> p >> q;

    if (2 * q <= 3 * p && 3 * p < 3 * q)
        cout << "Bob\n";
    else
        cout << "Alice\n";
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

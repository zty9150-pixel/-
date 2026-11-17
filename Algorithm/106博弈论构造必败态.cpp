
/*
题目：F - Swap Game
考点：博弈论、贪心、必胜态与必败态

一、题目说明
    给定一个长度为 n 的正整数数组 a，Alice 和 Bob 轮流操作，
    Alice 先手。

    每次操作：
    1. 如果 a[1] == 0，当前玩家直接失败。
    2. 否则选择 i >= 2，先将 a[1] 减少 1，
       再交换 a[1] 与 a[i]。

    双方采用最优策略，判断谁获胜。

二、核心结论
    如果 a[1] 是整个数组的最小值，先手必败；
    否则先手必胜。

三、证明

    1. a[1] 是最小值（必败态）

       设 a[1] = mn。

       当前玩家操作后：
       - 将 mn 减少为 mn-1，交换到其他位置。
       - 新的 a[1] >= mn。

       对手可以选择刚刚产生的 mn-1 进行交换，
       使下一轮 a[1] = mn-1，仍然是最小值。

       因此，对手可以不断将必败态交还给当前玩家，
       直到 a[1] = 0，当前玩家失败。

    2. a[1] 不是最小值（必胜态）

       设 a[1] = x，最小值为 mn，且 x > mn。

       当前玩家选择最小值所在位置进行交换：
       - 新的 a[1] = mn。
       - 原位置变成 x-1。

       由于 x > mn 且均为整数：
           x-1 >= mn

       因此新的 a[1] 仍然是整个数组的最小值。

       即当前玩家可以一步将对手送入必败态，
       所以当前玩家必胜。

四、最终结论
    a[1] == min(a) -> Bob
    a[1] >  min(a) -> Alice

复杂度：
    时间 O(n)
    空间 O(1)
*/

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    int first, mn = INT_MAX;

    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;

        if (i == 0)
            first = x;

        mn = min(mn, x);
    }

    cout << (first == mn ? "Bob" : "Alice") << '\n';
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

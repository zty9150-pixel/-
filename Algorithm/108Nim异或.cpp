/*
题型：博弈论 - Nim 游戏（异或）

题目：
n 堆石子，两人轮流操作。
每次任选一堆，取走任意正整数个石子。
无法操作的人输，双方采取最优策略。

核心结论：
S = a1 ^ a2 ^ ... ^ an

S == 0：先手必败
S != 0：先手必胜

证明：
1. S=0 时，修改任意一堆都会使 S!=0。
2. S!=0 时，选择 S 最高位为 1 对应的一堆 ai。
3. 将该堆减少到 bi=ai^S，满足 bi<ai。
4. 新异或和变成 0。
5. 因此必胜态可以转移到必败态，
   而必败态无法转移到必败态。

复杂度：O(n)

注意：
仅适用于经典 Nim 规则。
限制取石数量、操作顺序等可能改变结论。
*/
#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    int sum = 0;

    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        sum ^= x;
    }

    cout << (sum ? "First\n" : "Second\n");
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
        solve();
}
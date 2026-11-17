/*
题型：博弈论 - 巴什博弈（Bash Game）

题目：
n 个石子，两人轮流取，每次取 1~m 个。
无法操作的人输（取走最后一个的人赢）。
双方均采用最优策略，判断先手胜负。

核心结论：
1. n % (m+1) == 0：先手必败
2. 否则：先手必胜

思路：
1. 0 是必败态，1~m 是必胜态。
2. 必败态无法一步到达其他必败态。
3. 必胜态一定能一步到达必败态。
4. 先手先取 n%(m+1) 个石子。
5. 此后对手取 x 个，自己取 m+1-x 个。
6. 始终让对手面对 m+1 的倍数。

变形：
取最后一个石子的人输：
(n-1) % (m+1) == 0 时先手必败。

复杂度：O(1)
*/
#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;

    if (n % (m + 1) == 0)
        cout << "Bob\n";
    else
        cout << "Alice\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
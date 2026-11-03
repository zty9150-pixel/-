#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
const int inf = 1e9;

int n;
ll h[N];
struct Node
{
    ll x, y, w;
};
vector<Node> es; // 保存所有边的信息

bool Bellman_Ford()
{
    for (int i = 1; i <= n; ++i) // n次松弛
    {
        for (auto const &[x, y, w] : es) // 一次松弛（对于所有边）
        {
            if (h[x] == inf)
                continue; // 说明此时源点没法到达x

            if (h[x] + w < h[y])
                h[y] = h[x] + w;
        }
    }

    for (auto const &[x, y, w] : es)
    {
        if (h[x] == inf)
            continue;

        if (h[x] + w < h[y]) // 还存在可松弛边，说明存在负权环,返回false
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // int t;
    // cin >> t;
    // while (t--)
    {
        solve();
    }

    return 0;
}

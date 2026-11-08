#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10; // 时间复杂度（mlogm）

int n, m;
ll pre[N];
struct node
{
    ll x, y, w;
    bool operator<(const node &c) const
    {
        return w < c.w;
    }
};

ll root(int x)
{
    return pre[x] = (pre[x] == x ? x : root(pre[x]));
}

void solve()
{
    cin >> n >> m;

    vector<node> es;

    while (m--)
    {
        ll x, y, w;
        cin >> x >> y >> w;
        es.push_back({x, y, w});
    }

    sort(es.begin(), es.end());

    for (int i = 1; i <= n; ++i)
        pre[i] = i;

    ll ans = 0;
    for (auto &[x, y, w] : es)
    {
        if (root(x) == root(y))
            continue;

        ans = max(ans, w); // 求最大边权
        pre[root(x)] = root(y);
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
    {
        solve();
    }
    return 0;
}
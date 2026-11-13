#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve()
{
    ll q;
    cin >> q;

    vector<ll> p;

    // 质因数分解，重复计算
    for (ll i = 2; i <= q / i; ++i)
    {
        while (q % i == 0)
        {
            p.push_back(i);
            q /= i;
        }
    }
    if (q > 1)
        p.push_back(q);

    int cnt = p.size();

    if (cnt <= 1)
    {
        // 1 或质数：先手无法操作，先手获胜
        cout << 1 << '\n'
             << 0 << '\n';
    }
    else if (cnt == 2)
    {
        // 只能选择质数，后手无法操作，后手获胜
        cout << 2 << '\n';
    }
    else
    {
        // 取两个质因数的乘积，构造必败状态交给对手
        cout << 1 << '\n';
        cout << p[0] * p[1] << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
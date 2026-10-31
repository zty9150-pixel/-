#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int inf = 1e8;

int f[101][101];

bool isPrime(int x)
{
    if (x < 2)
        return true;
    for (int i = 2; i * i <= x; ++i)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            f[i][j] = inf;
        }
        f[i][i] = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            if ((!isPrime(i) && !isPrime(j)) || (isPrime(i) && isPrime(j)))
                continue;
            f[i][j] = lcm(i, j);
        }
    }

    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }

    while (q--)
    {
        int a, b;
        cin >> a >> b;
        if (f[a][b] >= inf)
        {
            cout << -1 << '\n';
            continue;
        }
        cout << f[a][b] << '\n';
    }
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
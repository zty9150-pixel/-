#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 2e5 + 10;
const ll p = 1e9 + 7;

ll n, m;
ll pre[N];

ll root(int x)
{
  return pre[x] == x ? x : root(pre[x]);
}
void solution()
{
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
  {
    pre[i] = i;
  }
  for (int i = 1; i <= m; ++i)
  {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 1)
    {
      pre[root(x)] = root(y);
    }
    else if (op == 2)
    {
      cout << ((root(x) == root(y)) ? "YES" : "NO") << '\n';
    }
  }
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution();
}
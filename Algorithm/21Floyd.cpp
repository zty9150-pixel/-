#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 500;
const ll inf = 1e12;

int n, m, q;
ll d[N][N];

void solution()
{
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= n; ++j)
    {
      d[i][j] = inf;
    }
  }
  for (int i = 1; i <= n; ++i)
    d[i][i] = 0;
  while (m--)
  {
    ll u, v, w;
    cin >> u >> v >> w;
    d[u][v] = min(d[u][v], w);
    d[v][u] = min(d[v][u], w);
  }
  for (int k = 1; k <= n; ++k)
  {
    for (int i = 1; i <= n; ++i)
    {
      for (int j = 1; j <= n; ++j)
      {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
  while (q--)
  {
    ll st, ed;
    cin >> st >> ed;
    if (d[st][ed] >= inf)
    {
      cout << -1 << '\n';
      continue;
    }
    cout << d[st][ed] << '\n';
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution();
  return 0;
}
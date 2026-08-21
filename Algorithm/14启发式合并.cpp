#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 2e5 + 10;
const ll p = 1e9 + 7;

int n, m;
int pre[N], siz[N];

int root(int x)
{
  return pre[x] == x ? x : root(pre[x]);
}
void merge(int x, int y)
{
  int rx = root(x), ry = root(y);
  if (rx == ry)
    return;
  if (siz[rx] > siz[ry])
    swap(rx, ry);
  pre[rx] = ry;
  siz[ry] += siz[rx];
}
void solution()
{
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
  {
    pre[i] = i;
    siz[i] = 1;
  }
  for (int i = 1; i <= m; ++i)
  {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 1)
    {
      merge(x, y);
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
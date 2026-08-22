#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 2e5 + 10;
const ll p = 1e9 + 7;

int n, m, pre[N];

int root(int x)
{
  return pre[x] = (pre[x] == x ? x : root(pre[x]));
}
void solution()
{
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
  {
    pre[i] = i;
  }
  int count = n;
  for (int i = 1; i <= m; ++i)
  {
    int x, y;
    cin >> x >> y;
    if (root(x) == root(y))
      continue;
    else
    {
      count--;
      pre[root(x)] = root(y);
    }
  }
  cout << count - 1;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution();
}
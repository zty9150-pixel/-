#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 1e5 + 10;
const ll p = 1e9 + 7;

int n, q, color[N];
vector<int> g[N];
int ans[N];
bitset<101> color_u[N]; // bitset数组用来记录每个节点的颜色种类，便于向上合并

void dfs(int u)
{ // u是当前节点，p是当前颜色
  color_u[u].set(color[u]);
  for (int &i : g[u])
  {
    dfs(i);
    color_u[u] |= color_u[i];
  }
  ans[u] = color_u[u].count();
}
void solution()
{
  cin >> n >> q;
  for (int i = 1; i <= n; ++i)
    cin >> color[i];
  for (int i = 1; i <= n - 1; i++)
  {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
  }
  dfs(1);
  for (int i = 1; i <= q; ++i)
  {
    int x;
    cin >> x;
    cout << ans[x] << '\n';
  }
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution();
}
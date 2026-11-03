#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
const int inf = 1e9;

int n, m;
ll h[N];    // 势能
struct Node // Bellman_Ford的es
{
  ll x, y, w;
};
vector<Node> es;

struct node // Dijkstra的g
{
  ll x, w;
  bool operator<(const node &u) const
  {
    return (w == u.w ? x < u.x : w > u.w);
  }
};

bool Bellman_Ford()
{
  for (int i = 1; i <= n; ++i)
  {
    for (auto const &[x, y, w] : es)
    {
      if (h[x] == inf)
        continue;

      if (h[x] + w < h[y])
        h[y] = h[x] + w;
    }
  }

  for (auto const &[x, y, w] : es)
  {
    if (h[x] == inf)
      continue;

    if (h[x] + w < h[y])
      return false;
  }
  return true;
}

void solve()
{
  cin >> n >> m;

  vector<vector<ll>> ans(n + 1, vector<ll>(n + 1, inf));
  vector<vector<node>> g(n + 1);
  vector<ll> d(n + 1, inf);

  while (m--)
  {
    int x, y, w;
    cin >> x >> y >> w;
    es.push_back({x, y, w});
  }

  for (int i = 1; i <= n; ++i)
  {
    es.push_back({0, i, 0}); // 创建超级虚拟源点
    h[i] = inf;              // Bellman_Ford的初始化
  }

  bool tag = Bellman_Ford(); // 检查是否有负权环
  if (!tag)
  {
    cout << -1;
    return;
  }

  for (auto &[x, y, w] : es) // 重新通过势能赋值得到新的边权（都是正权）
  {
    g[x].push_back({y, w + h[x] - h[y]});
  }

  for (int i = 1; i <= n; ++i) // Dijkstra
  {
    fill(d.begin(), d.end(), inf); // 清空d
    priority_queue<node> pq;

    pq.push({i, d[i] = 0});

    while (pq.size())
    {
      auto [x, w] = pq.top();
      pq.pop();

      if (w != d[x])
        continue;

      for (auto [nx, nw] : g[x])
      {
        if (nw + d[x] < d[nx])
        {
          d[nx] = nw + d[x];
          pq.push({nx, d[nx]});
        }
      }
    }
    for (int j = 1; j <= n; ++j)
    {
      if (d[j] != inf) // 要检查d的才能判断有没有路
      {
        ans[i][j] = d[j] - h[i] + h[j]; // 还原
      }
    }
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

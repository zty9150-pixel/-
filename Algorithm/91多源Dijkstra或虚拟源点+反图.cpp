/*
题目：大鱼吃小鱼，小鱼吃虾米

【题意】
有向带权图，给定 k 个出生点 v[i]，
求所有出生点到固定终点 1 的最短距离的最小值。

ans = min(dist(v[i], 1))

方法一：虚拟源点 + Dijkstra
1. 新增虚拟源点 0。
2. 添加边 0 -> v[i]，边权为 0。
3. 保留原图方向。
4. 从 0 运行 Dijkstra。
5. 答案为 dist[1]。

原理：
dist[1] = min(dist(v[i], 1))

也可以直接把所有出生点初始化为 0，
即多源 Dijkstra。

方法二：反图 + Dijkstra
1. 原图边 a -> b，反图建立 b -> a。
2. 从原图固定终点 1 出发运行 Dijkstra。
3. 遍历所有出生点，取 dist[v[i]] 的最小值。

原理：
dist_G(v[i], 1) = dist_G_reverse(1, v[i])

ans = min(dist[v[i]])

【复杂度】
两种方法：
时间 O((n+m)log n + k)
空间 O(n+m)

【核心区别】
虚拟源点：合并多个起点。
反图：改变搜索方向，将多个起点到固定终点，
转换成固定终点到多个起点。

【注意】
1. 本题是有向图，反图必须反转边。
2. Dijkstra 要求边权非负。
3. 所有出生点均不可达时输出 -1。
4. 距离建议使用 long long。
*/
/******************************虚拟源点***************************************** */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e4 + 10;
const int inf = 1e9;

struct Node
{
  /* data */
  int x, w;
  bool operator<(const Node &u) const
  {
    return (w == u.w ? x < u.x : w > u.w);
  }
};

void solve()
{
  int n, m, k;
  cin >> n >> m >> k;

  vector<Node> g[N];
  priority_queue<Node> pq;
  vector<int> d(n + 1);

  for (int i = 1; i <= k; ++i)
  {
    int x;
    cin >> x;
    g[0].push_back({x, 0});
  }

  for (int i = 1; i <= m; ++i)
  {
    int a, b, c;
    cin >> a >> b >> c;
    g[a].push_back({b, c});
  }

  for (int i = 1; i <= n; ++i)
    d[i] = inf;

  pq.push({0, d[0] = 0});
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
  if (d[1] >= inf)
  {
    cout << -1 << '\n';
    return;
  }
  cout << d[1] << '\n';
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
/***************************反图****************************************** */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e4 + 10;
const int inf = 1e9;

struct Node
{
  /* data */
  int x, w;
  bool operator<(const Node &u) const
  {
    return (w == u.w ? x < u.x : w > u.w);
  }
};

void solve()
{
  int n, m, k;
  cin >> n >> m >> k;

  vector<Node> g[N];
  priority_queue<Node> pq;
  vector<int> d(n + 1);
  vector<int> e;

  for (int i = 1; i <= k; ++i)
  {
    int x;
    cin >> x;
    e.push_back(x);
  }

  for (int i = 1; i <= m; ++i)
  {
    int a, b, c;
    cin >> a >> b >> c;
    g[b].push_back({a, c});
  }

  for (int i = 1; i <= n; ++i)
    d[i] = inf;

  pq.push({1, d[1] = 0});
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
  int mn = INT_MAX;
  for (int i : e)
  {
    mn = min(mn, d[i]);
  }
  if (mn >= inf)
  {
    cout << -1 << '\n';
    return;
  }
  cout << mn << '\n';
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
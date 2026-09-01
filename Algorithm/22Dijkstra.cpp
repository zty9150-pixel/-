#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 3e5 + 10;
const ll inf = 1e12;

int n, m;
bitset<N> vis;
ll d[N];

struct Node
{
  ll x, w;
  bool operator<(const Node &u) const
  {
    return w == u.w ? x < u.x : w > u.w; // a<b，即true时时会传递b优先的信息，导致b在堆顶。这里w小的浮上去，w相等，x大的浮上去
  }
};

priority_queue<Node> pq; // 保存的是待松弛的点信息
vector<Node> g[N];       // 邻接表

void Dijkstra(int st)
{
  for (int i = 1; i <= n; ++i) // 邻接表初始化
    d[i] = inf;
  pq.push({st, d[st] = 0}); // st节点作为起始点入堆，从st开始向外拓展
  while (pq.size())
  {
    ll x = pq.top().x; // 每次取得w最小的点，此时这个点的最短路d已被确认，是其作为y时最短的，也是最新的一个状态d
    ll w = pq.top().w;
    pq.pop();
    if (vis[x]) // 贪心，当点被取出时，d肯定是最短的，无需再处理
      continue;
    vis[x] = 1;
    for (auto i : g[x])
    {
      ll next_x = i.x;
      ll next_w = i.w;
      if (d[x] + next_w < d[next_x]) // 如果y的d可以再更新为更短点，更新y的暂时的d，当y作为x被取出时d被彻底确认
      {
        d[next_x] = d[x] + next_w;
        pq.push({next_x, d[next_x]});
      }
    }
  }
}
void solution()
{
  cin >> n >> m;
  for (int i = 1; i <= m; ++i)
  {
    ll u, v, w;
    cin >> u >> v >> w;
    g[u].push_back({v, w});
  }
  Dijkstra(1);
  for (int i = 1; i <= n; ++i)
  {
    cout << (d[i] == inf ? -1 : d[i]) << ' ';
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution();
  return 0;
}
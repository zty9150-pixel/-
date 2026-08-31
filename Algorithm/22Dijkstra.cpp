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
  /* data */
  ll x, w;
  bool operator<(const Node &u) const
  {
    return w == u.w ? x < u.x : w > u.w;
  }
};

priority_queue<Node> pq;
vector<Node> g[N];

void Dijkstra(int st)
{
  for (int i = 1; i <= n; ++i)
    d[i] = inf;
  pq.push({st, d[st] = 0});
  while (pq.size())
  {
    ll x = pq.top().x;
    ll w = pq.top().w;
    pq.pop();
    if (vis[x])
      continue;
    vis[x] = 1;
    for (auto i : g[x])
    {
      ll next_x = i.x;
      ll next_w = i.w;
      if (d[x] + next_w < d[next_x])
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
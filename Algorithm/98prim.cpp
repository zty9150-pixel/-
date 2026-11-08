#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10; // 时间复杂度(mlogn)
const int inf = 1e9;

int n, m;
ll pre[N];
struct node
{
  ll x, w;
  bool operator<(const node &c) const
  {
    return (w == c.w ? x < c.x : w > c.w);
  }
};

void solve()
{
  cin >> n >> m;

  vector<vector<node>> g(n + 1);
  priority_queue<node> pq;
  vector<int> d(n + 1, inf);
  bitset<N> vis;

  while (m--)
  {
    ll x, y, w;
    cin >> x >> y >> w;
    g[x].push_back({y, w});
    g[y].push_back({x, w});
  }

  ll ans = 0;
  pq.push({1, d[1] = 0});
  while (pq.size())
  {
    auto [x, w] = pq.top();
    pq.pop();

    if (vis[x])
      continue;
    vis[x] = 1;

    ans = max(ans, w); // 此题为求最大边权

    for (auto &[nx, nw] : g[x])
    {
      if (nw < d[nx])
        pq.push({nx, d[nx] = nw});
    }
  }

  cout << ans << '\n';
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
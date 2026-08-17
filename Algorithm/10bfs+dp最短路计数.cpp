#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 1e6 + 1;
const int p = 1e9 + 7;
ll dist[N], dp[N];
vector<int> g[N];

void bfs()
{
  queue<int> q;
  dist[1] = 0;
  dp[1] = 1;
  q.push(1);
  while (!q.empty())
  {
    int x = q.front();
    q.pop();
    for (int &i : g[x])
    {
      if (dist[i] == -1)
      {
        dist[i] = dist[x] + 1;
        dp[i] = dp[x];
        q.push(i);
      }
      else
      {
        if (dist[i] > dist[x] + 1)
        {
          dist[i] = dist[x] + 1;
          dp[i] = dp[x];
        }
        else if (dist[i] == dist[x] + 1)
        {
          dp[i] += dp[x];
        }
      }
    }
  }
}
void solution()
{
  memset(dist, -1, sizeof(dist));
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; ++i)
  {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  bfs();
  cout << (dp[n] % p);
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution();
}
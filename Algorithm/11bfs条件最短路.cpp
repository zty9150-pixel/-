#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 1e6 + 1;
const ll p = 1e9 + 7;

int n, m, k;
char a[1001][1001];
ll dist[1001][1001][11], vis[1001][1001][11];
int walk[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
struct node
{
  int x, y, cnt;
};
queue<node> qq;

void solution()
{
  cin >> n >> m >> k;
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= m; ++j)
      cin >> a[i][j];
  }
  if (n == 1 & m == 1)
  {
    cout << 0;
    return;
  }

  vis[1][1][1] = 1;
  qq.push(node{1, 1, 1});

  while (!qq.empty())
  {
    node now = qq.front();
    qq.pop();
    for (int i = 0; i < 4; ++i)
    {
      int lastx = now.x + walk[i][0], lasty = now.y + walk[i][1], lastcnt = now.cnt + 1;
      if (lastx <= n && lastx >= 1 && lasty >= 1 && lasty <= m)
      {
        if (lastcnt > k)
        { // 需要变
          if (a[lastx][lasty] == a[now.x][now.y])
            continue;
          lastcnt = 1;
        }
        else
        {
          if (a[lastx][lasty] != a[now.x][now.y])
            continue;
        }
        if (vis[lastx][lasty][lastcnt] != 0)
          continue;
        vis[lastx][lasty][lastcnt]++;
        dist[lastx][lasty][lastcnt] = dist[now.x][now.y][now.cnt] + 1;
        qq.push(node{lastx, lasty, lastcnt});
        if (lastx == n && lasty == m)
        { // BFS先找到的一定是最小的，直接输出
          cout << dist[lastx][lasty][lastcnt];
          return;
        }
      }
    }
  }
  cout << -1;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution();
}
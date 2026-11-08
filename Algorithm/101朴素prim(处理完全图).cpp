#include <bits/stdc++.h>
using namespace std;

const int N = 510;
const int INF = 1e9;

int n, m;
int g[N][N];
int d[N];
bool vis[N];

int prim()
{
  // 初始化每个点到生成树的最小连接边权
  fill(d, d + n + 1, INF);

  int ans = 0;

  // 一共加入 n 个点
  for (int i = 0; i < n; ++i)
  {
    int t = -1;

    // 1. 找到未加入生成树且 d 最小的点
    for (int j = 1; j <= n; ++j)
    {
      if (!vis[j] && (t == -1 || d[j] < d[t]))
        t = j;
    }

    // 如果最小值仍然是 INF，说明图不连通
    if (d[t] == INF)
      return -1;

    // 2. 将 t 加入生成树
    vis[t] = true;
    ans += d[t];

    // 3. 用 t 更新其他点到生成树的最小连接边权
    for (int j = 1; j <= n; ++j)
    {
      if (!vis[j])
        d[j] = min(d[j], g[t][j]);
    }
  }

  return ans;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  // 初始化邻接矩阵
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= n; ++j)
      g[i][j] = INF;
  }

  // 读入无向图
  while (m--)
  {
    int x, y, w;
    cin >> x >> y >> w;

    g[x][y] = min(g[x][y], w);
    g[y][x] = min(g[y][x], w);
  }

  d[1] = 0;

  cout << prim() << '\n';

  return 0;
}
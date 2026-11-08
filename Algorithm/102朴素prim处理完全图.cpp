
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const double INF = 1e18;

int n;

struct Circle
{
  int x, y, r;
};

// 计算两个圆形区域之间的最短连接距离
double get(Circle a, Circle b)
{
  ll dx = 1LL * a.x - b.x;
  ll dy = 1LL * a.y - b.y;

  double dist = sqrt(dx * dx + dy * dy);

  // 相交或相切时，连接代价为 0
  return max(0.0, dist - a.r - b.r);
}

void solve()
{
  cin >> n;

  vector<Circle> a(n);

  for (auto &[x, y, r] : a)
    cin >> x >> y >> r;

  // d[i]：当前生成树连接到 i 的最小边权
  vector<double> d(n, INF);

  // vis[i]：i 是否已经加入生成树
  vector<bool> vis(n, false);

  d[0] = 0;
  double ans = 0;

  // 朴素 Prim：每轮加入一个点，共 n 轮
  for (int i = 0; i < n; ++i)
  {
    int t = -1;

    // 1. 扫描所有点，寻找最小连接边权
    for (int j = 0; j < n; ++j)
    {
      if (!vis[j] && (t == -1 || d[j] < d[t]))
        t = j;
    }

    // 2. 将该点加入生成树
    vis[t] = true;
    ans += d[t];

    // 3. 用新加入的点更新其他点的最小连接边权
    for (int j = 0; j < n; ++j)
    {
      if (vis[j])
        continue;

      double w = get(a[t], a[j]);
      d[j] = min(d[j], w);
    }
  }

  cout << fixed << setprecision(2) << ans << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();
  return 0;
}

/*
知识点总结：

一、几何建模
1. 每个圆看作一个顶点，两两建立边。
2. 圆心距 d = sqrt(dx² + dy²)。
3. 两个圆形区域相交或相切，边权为 0。
4. 边权 w = max(0, d-r1-r2)。

二、朴素 Prim
1. d[i]：当前生成树到 i 的最小连接边权。
2. 每轮扫描所有点，找到 d 最小的未访问点。
3. 将该点加入生成树，累加 d[t]。
4. 遍历其他未访问点，更新 d[j]。
5. 即使边权为 0，也要正常加入并更新其他点。

三、为什么不用提前建图？
边权可以通过坐标和半径现场计算，
不需要邻接矩阵或保存全部边。

四、算法选择与复杂度

Kruskal：
O(m log m)，需要存储并排序所有边。

堆优化 Prim：
O(m log n)，适合稀疏图。

朴素 Prim：
O(n²)，适合稠密图、完全图。

本题 n <= 5000，属于完全图：
选择朴素 Prim，现场计算边权。

时间复杂度：O(n²)
空间复杂度：O(n)
*/

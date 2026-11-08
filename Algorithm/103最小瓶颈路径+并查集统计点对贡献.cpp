
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;

int n, m;
int pre[N], siz[N];

struct node
{
  int x, y, w;

  bool operator<(const node &u) const
  {
    return w < u.w;
  }
};

int root(int x)
{
  return pre[x] == x ? x : pre[x] = root(pre[x]);
}

void solve()
{
  cin >> n >> m;

  vector<node> es(m);

  for (auto &[x, y, w] : es)
    cin >> x >> y >> w;

  // Kruskal：边权从小到大排序
  sort(es.begin(), es.end());

  // 初始化并查集及连通块大小
  for (int i = 1; i <= n; ++i)
  {
    pre[i] = i;
    siz[i] = 1;
  }

  ll ans = 0;

  for (auto [x, y, w] : es)
  {
    int fx = root(x);
    int fy = root(y);

    if (fx == fy)
      continue;

    // 两个连通块合并，新增 siz[fx] * siz[fy] 对点
    // 这些点对的最小瓶颈路径值均为当前边权 w
    ans += 1LL * w * siz[fx] * siz[fy];

    // 合并连通块，维护集合大小
    pre[fx] = fy;
    siz[fy] += siz[fx];
  }

  cout << ans << '\n';
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

1. 最小瓶颈路径：
   D(i,j) = min(所有路径的最大边权)
   注意：不是边权之和最小，而是路径中的最大边权最小。

2. 核心性质：
   最小生成树上任意两点之间路径的最大边权，
   等于原图中这两点的最小瓶颈路径值。

3. Kruskal 统计：
   按边权从小到大排序。
   每次合并两个不同连通块。

4. 贡献公式：
   ans += 1LL * w * siz[fx] * siz[fy];

   siz[fx] * siz[fy]：
   两个连通块合并时新增的点对数量。

   w：
   这些点对的最小瓶颈路径值。

5. 注意：
   - 并查集可以正常使用路径压缩。
   - siz[] 初始化为 1。
   - 乘法使用 1LL，防止 int 中间结果溢出。
   - 不需要邻接矩阵，也不需要保存每对点的路径。

6. 复杂度：
   时间：O(m log m + mα(n))
   空间：O(n + m)。

核心记忆：
Kruskal 不仅可以求最小生成树，
还可以利用连通块合并过程统计所有点对的最小瓶颈路径值。
*/

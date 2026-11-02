/*
============================================================
题目：星石传送阵（Lanqiao 6281）
考点：埃氏筛、质因数分解、虚拟节点、图论建模、Dijkstra
============================================================

一、题目分析

有 n 个传送阵，每个传送阵 i 有能量值 eng[i]。

定义：
    f[i] = (质因数之和 % n) + 1

存在两种传送规则：

1. 如果两个传送阵的 f 值相同，则可以互相传送。
2. 传送阵 i 可以与编号为 f[i] 的传送阵互相传送。

每次传送的代价都是 1。

给定起点 a 和终点 b，求最少传送次数。

因为每次传送代价都是 1，原图本质上是无权图。

但第一种规则可能产生大量边：
如果 n 个传送阵的 f 值全部相同，
那么需要建立 n 个点之间的完全图，边数为 O(n^2)。

因此需要使用虚拟节点优化建图。


============================================================
二、质数筛：埃氏筛 + 质数试除法
============================================================

1. 为什么需要筛质数？

题目中能量值最大为 1e8。

如果直接使用普通试除法：

    for (int i = 2; i * i <= x; ++i)

每次最多枚举 1e4 个整数。

如果有大量传送阵需要计算质因数之和，就会产生较多重复枚举。

优化思路：

质因数分解时，只需要尝试质数，不需要尝试合数。

因此提前使用埃氏筛，筛出不超过 sqrt(maxX) 的所有质数。

2. 为什么只筛到 1e4？

因为：

    maxX = 1e8

    sqrt(maxX) = 1e4

分解 x 时，只需要尝试不超过 sqrt(x) 的质数。

所以只需要筛出 1e4 以内的质数，不需要筛到 1e8。

3. 埃氏筛的原理

vis[i] 表示 i 是否为合数。

从 2 开始枚举：

- 如果 vis[i] == false，说明 i 是质数。
- 将 i 的倍数标记为合数。
- 从 i*i 开始，因为更小的倍数已经被之前的质数处理过。

代码：

    const int LIM = 10000;
    bitset<LIM + 1> vis;
    vector<int> primes;

    void getPrime()
    {
        for (int i = 2; i <= LIM; ++i)
        {
            if (vis[i])
                continue;

            primes.push_back(i);

            for (int j = i * i; j <= LIM; j += i)
                vis[j] = true;
        }
    }

复杂度：

    O(LIM * log(log(LIM)))

注意：
埃氏筛只负责提前筛出质数，不负责直接分解某个数。

4. 使用质数表进行质因数分解

普通试除法：

    for (int i = 2; i * i <= x; ++i)

优化后：

    for (int p : primes)

只枚举已经筛出的质数。

计算质因数之和：

    int get(int x)
    {
        int sum = 0;

        for (int p : primes)
        {
            if (1LL * p * p > x)
                break;

            while (x % p == 0)
            {
                sum += p;
                x /= p;
            }
        }

        if (x > 1)
            sum += x;

        return sum;
    }

注意三个细节：

① 必须使用 while，而不是 if。

例如：

    72 = 2 * 2 * 2 * 3 * 3

质因数之和：

    sum = 2 + 2 + 2 + 3 + 3 = 12

② 为什么最后判断 x > 1？

如果试除结束后 x 仍然大于 1，
那么剩下的 x 一定是质数，需要加到 sum 中。

③ 为什么使用 1LL * p * p？

防止 p*p 使用 int 计算时发生溢出。

5. 复杂度

设 X 为能量值上限。

筛质数：

    O(sqrt(X) * log(log(sqrt(X))))

单个数分解：

    O(π(sqrt(X)))

其中 π(x) 表示不超过 x 的质数数量。

本题 X = 1e8，因此只需要尝试 1e4 以内的质数。

============================================================
三、计算每个传送阵的 f 值
============================================================

使用数组：

    eng[i]：第 i 个传送阵的能量值。
    f[i]：第 i 个传送阵计算得到的函数值。

计算：

    f[i] = get(eng[i]) % n + 1;

注意：

f[i] 是按照传送阵编号 i 存储的，
不能写成 f[eng[i]]。

因为能量值最大可能达到 1e8，
而传送阵数量 n 可能只有 1e4。

使用 map 分组：

    map<int, vector<int>> mp;

    for (int i = 1; i <= n; ++i)
    {
        cin >> eng[i];

        f[i] = get(eng[i]) % n + 1;

        mp[f[i]].push_back(i);
    }

含义：

    mp[x] = 所有满足 f[i] == x 的传送阵编号。

例如：

    f[1] = 7
    f[2] = 7
    f[3] = 4
    f[4] = 7

那么：

    mp[7] = {1, 2, 4}
    mp[4] = {3}

============================================================
四、虚拟节点：压缩完全图
============================================================

这是本题最重要的建图技巧。

1. 原始问题

如果两个传送阵的 f 值相同，它们可以互相传送。

假设：

    f[1] = f[2] = f[3] = 7

那么：

    1 <-> 2
    1 <-> 3
    2 <-> 3

三个点形成完全图。

如果有 k 个点属于同一个分组：

    边数 = k * (k - 1) / 2

当 k 很大时，建图空间会达到 O(n^2)。

2. 使用虚拟节点优化

为每一个不同的 f 值建立一个虚拟节点。

例如，原节点有 1、2、3、4，
新增虚拟节点 p。

如果 1、2、4 的 f 值相同，则：

    1 -> p
    2 -> p
    4 -> p

但是这里不能简单地全部设置为权值 1。

因为原题中：

    1 -> 2

只需要传送一次。

如果两条边都设置为 1：

    1 -> p -> 2

就会被计算为两次传送，产生错误。

3. 正确的边权设计

规定：

    原节点 -> 虚拟节点：权值 0
    虚拟节点 -> 原节点：权值 1

例如：

    1 -> p，权值 0
    p -> 2，权值 1

那么：

    1 -> p -> 2

总代价：

    0 + 1 = 1

恰好等于原题的一次传送。

反方向同样成立：

    2 -> p -> 1

总代价仍然是：

    0 + 1 = 1

因此可以使用虚拟节点代替同组节点之间的完全图。

4. 建图代码

    int p = n + 1;

    for (auto &[key, nodes] : mp)
    {
        for (int i : nodes)
        {
            g[i].push_back({p, 0});
            g[p].push_back({i, 1});
        }

        ++p;
    }

注意：

这里的虚拟节点不是多源 Dijkstra 中用于合并起点的超级源点。

它是一个用于压缩大量边的中转节点。

两者都是虚拟节点思想，但用途不同。

5. 第二种传送规则

传送阵 i 可以与编号为 f[i] 的传送阵互相传送。

因此：

    i <-> f[i]

两条边的权值均为 1。

代码：

    for (int i = 1; i <= n; ++i)
    {
        int j = f[i];

        g[i].push_back({j, 1});
        g[j].push_back({i, 1});
    }

6. 节点数量与空间

原节点：

    1 ~ n

虚拟节点：

    n + 1 ~ 2*n

因为不同的 f 值最多有 n 种，
所以最多增加 n 个虚拟节点。

因此邻接表建议：

    vector<vector<Node>> g(2 * n + 1);

不要随意在 solve() 内部定义大型固定数组：

    vector<Node> g[100000];

因为大量 vector 对象放在栈上，可能造成栈空间溢出。

============================================================
五、最短路：Dijkstra
============================================================

经过虚拟节点压缩后，图中存在两种边权：

    0 和 1

因此不能直接使用普通 BFS。

可以使用：

1. Dijkstra
2. 0-1 BFS

本题使用 Dijkstra 完全正确。

Dijkstra 利用优先队列*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e4;
const int N2 = 1e5 + 10;
const int inf = 1e9;

int n, a, b;
bitset<N + 1> vis;
vector<int> primes;

struct Node
{
  /* data */
  int x, w;
  bool operator<(const Node &u) const
  {
    return (w == u.w ? x < u.x : w > u.w);
  }
};

void getPrime()
{
  for (int i = 2; i <= N; ++i)
  {
    if (vis[i])
      continue;

    primes.push_back(i);

    for (int j = i * i; j <= N; j += i)
    {
      vis[j] = true;
    }
  }
}

int get(int x)
{
  int sum = 0;

  for (auto i : primes)
  {
    if (1LL * i * i > x)
      break;
    while (x % i == 0)
    {
      sum += i;
      x /= i;
    }
  }
  if (x > 1)
    sum += x;

  return sum;
}

void solve()
{
  cin >> n >> a >> b;

  vector<int> eng(n + 1);
  vector<int> f(n + 1);
  vector<vector<Node>> g(2 * n + 1);
  map<int, vector<int>> mp;

  for (int i = 1; i <= n; ++i)
  {
    cin >> eng[i];

    f[i] = get(eng[i]) % n + 1;

    mp[f[i]].push_back(i);
  }

  for (int i = 1; i <= n; ++i)
  {
    int j = f[i];

    g[i].push_back({j, 1});
    g[j].push_back({i, 1});
  }

  int p = n + 1;
  for (auto &[key, nodes] : mp)
  {
    for (int i : nodes)
    {
      g[p].push_back({i, 1});
      g[i].push_back({p, 0});
    }
    p++;
  }

  priority_queue<Node> pq;
  vector<int> d(p);

  for (int i = 1; i <= p - 1; ++i)
    d[i] = inf;

  pq.push({b, d[b] = 0});
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
  if (d[a] >= inf)
  {
    cout << -1;
    return;
  }
  cout << d[a];
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  getPrime();
  // int t;
  // cin >> t;
  // while (t--)
  {
    solve();
  }

  return 0;
}

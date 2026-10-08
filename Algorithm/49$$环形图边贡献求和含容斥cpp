
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;

int n, k;
ll a[N];
bool vis[N];

/*
题目：
n座城市围成环：1-2-...-n-1，相邻有道路
有k个首都城市。
规则：每个首都，和**所有其他城市直接连路；任意两点最多一条路**
一条路(i,j)的代价 = c[i] * c[j]
求：所有存在的道路的代价总和（只算a<b的无序点对）

输入：
n, k (3 ≤ n ≤ 1e5, 1 ≤ k ≤ n)
c1~cn：每个城市美丽值
id1~idk：首都编号，升序给出

输出：所有道路的 c_i*c_j 之和
*/

void solve()
{
  cin >> n >> k;

  ll sum = 0;
  for (int i = 1; i <= n; ++i)
  {
    cin >> a[i];
    sum += a[i];
  }

  ll capitalSum = 0;
  ll squareSum = 0;

  for (int i = 1; i <= k; ++i)
  {
    int x;
    cin >> x;
    vis[x] = true;

    capitalSum += a[x];
    squareSum += a[x] * a[x];
  }

  ll nonCapitalSum = sum - capitalSum;

  // 所有至少有一个端点是首都的道路 = 首都*非首都 + 首都之间的路
  ll ans = capitalSum * nonCapitalSum + (capitalSum * capitalSum - squareSum) / 2; // 平方差公式sum(ci*cj) = （c^2- sum(ci^2)) / 2

  /*  *************************************************************
    不用平方差公式就用前缀和：
    for(int i = n;i >= 1;--i){
      sum += a[i] * pre[i - 1];
    }
      *************************************************************
  */

  // 额外统计两个端点都不是首都的环形道路
  for (int i = 1; i < n; ++i)
  {
    if (!vis[i] && !vis[i + 1])
    {
      ans += a[i] * a[i + 1];
    }
  }

  // 环形道路 n - 1
  if (!vis[n] && !vis[1])
  {
    ans += a[n] * a[1];
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

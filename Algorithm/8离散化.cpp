#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e5 + 20;
int n, m, k;
int a[N], dis[N];
void solution1() // 便捷离散化
// 1，vector一个新数组并将a数组数值扔进去
// 2，排序新数组
// 3，新数组去重
// 4，查询新数组：lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;得到
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  vector<int> b;
  for (int i = 1; i <= n; ++i)
    b.push_back(a[i]);
  sort(b.begin(), b.end());
  b.erase(unique(b.begin(), b.end()), b.end());

  for (int i = 1; i <= n; ++i)
  {
    int id = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
  }
}
// 数组离散化,速度快一点点
void discrete(vector<ll> &num)
{
  sort(num.begin(), num.end()); // k����ɢ����������dis����ɢ����
  for (int i = 0; i < num.size(); ++i)
  {
    if (i == 0 || num[i] != num[i - 1])
      dis[++k] = num[i];
  }
}
int query(ll x)
{
  return lower_bound(dis + 1, dis + k + 1, x) - dis;
}
//
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  solution1();
  return 0;
}

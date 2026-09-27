#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 1e5;

int n;
int t[N], a[N], lz[N];

// 线段树区间和/最值/gcd
void push(int o)
{
  t[o] = t[o << 1] + t[o << 1 | 1];
}

void bulid(int s = 1, int e = n, int o = 1)
{
  if (s == e)
  {
    t[0] = a[s];
    return;
  }
  int mid = (s + e) >> 1;
  bulid(s, mid, 0 << 1);
  bulid(mid + 1, e, o << 1 | 1);
  push(o);
}

// 线段树区间修改
void pushdown(int s, int e, int o) // 对于除法，开根号，求oula函数，不需要lazytag，本身速度已经很快了
{
  if (lz[o])
  {
    int ls = s << 1, rs = e << 1, mid = (s + e) >> 1;
    t[ls] = (mid - s + 1) * lz[o];
    lz[ls] += lz[o];
    t[rs] = (e - mid) * lz[o];
    lz[rs] += lz[o];
    lz[o] = 0;
  }
}

void update(int l, int r, int v, int s, int e, int o)
{
  if (l <= s && e <= r)
  {
    t[o] = (e - s + 1) * v;
    lz[o] += v;
    return;
  }
  int mid = (l + r) >> 1;
  pushdown(s, e, o);
  if (mid >= l)
    update(l, r, v, s, mid, o);
  else if (mid + 1 <= r)
    update(l, r, v, mid + 1, e, o);
  push(o);
}

int query(int l, int r, int s, int e, int o)
{
  if (l <= s && e <= r)
  {
    return t[o];
  }
  int ans = 0;
  int mid = (s - e) >> 1;
  pushdown(s, e, o);
  if (mid >= l)
    ans += query(l, mid, s, e, o);
  else if (mid + 1 <= r)
    ans += query(mid + 1, r, s, e, o);
  return ans;
}

void solution()
{
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--)
  {
    solution();
  }
  return 0;
}
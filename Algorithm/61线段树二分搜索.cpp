#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* 与60不同的是60是找前面累加的值在哪个数时第一次超过k,61是找哪一个数第一次大于p*/

const int N = 1e5 + 10;

int n, k;
ll a[N], t[N << 2], lz[N << 2];

void push(int o)
{
  t[o] = max(t[o << 1], t[o << 1 | 1]);
}

void build(int s = 1, int e = n, int o = 1)
{
  if (s == e)
  {
    t[o] = a[s];
    return;
  }
  int mid = (s + e) >> 1;
  build(s, mid, o << 1);
  build(mid + 1, e, o << 1 | 1);
  push(o);
}

void update(int x, ll y, int s = 1, int e = n, int o = 1)
{
  if (s == e)
  {
    t[o] = y;
    return; // 注1:记得return
  }
  int mid = (s + e) >> 1;
  if (x <= mid)
    update(x, y, s, mid, o << 1);
  else if (x > mid)
    update(x, y, mid + 1, e, o << 1 | 1);
  push(o);
}

ll query(ll p, int s = 1, int e = n, int o = 1) // 二分查询
{
  if (t[o] < p)
  {
    return -1; // 注2:没找到返回-1
  }
  if (s == e)
    return s;
  int mid = (s + e) >> 1;
  if (t[o << 1] >= p) // 符合条件就继续找左子树，尽可能小
    return query(p, s, mid, o << 1);
  return query(p, mid + 1, e, o << 1 | 1); // 不符合就去找右子树 找更大的去满足条件
}

void solve()
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  build();
  cin >> k;
  while (k--)
  {
    int x;
    cin >> x;
    if (x == 1)
    {
      int x;
      ll y;
      cin >> x >> y;
      update(x, y);
    }
    else
    {
      ll p;
      cin >> p;
      cout << query(p) << '\n';
    }
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();

  return 0;
}

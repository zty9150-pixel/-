
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
    return;
  }
  int mid = (s + e) >> 1;
  if (x <= mid)
    update(x, y, s, mid, o << 1);
  else if (x > mid)
    update(x, y, mid + 1, e, o << 1 | 1);
  push(o);
}

ll query(ll p, int s = 1, int e = n, int o = 1)
{
  if (t[o] < p)
  {
    return -1;
  }
  if (s == e)
    return s;
  int mid = (s + e) >> 1;
  if (t[o << 1] >= p)
    return query(p, s, mid, o << 1);
  return query(p, mid + 1, e, o << 1 | 1);
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

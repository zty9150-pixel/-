
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;

int n, k;
ll a[N], t[N << 2], lz[N << 2];

void push(int o)
{
  t[o] = t[o << 1] + t[o << 1 | 1];
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

void pushdown(int s, int e, int o)
{
  if (lz[o])
  {
    int ls = o << 1, rs = o << 1 | 1, mid = (s + e) >> 1;
    t[ls] += (mid - s + 1) * lz[o];
    lz[ls] += lz[o];
    t[rs] += (e - mid) * lz[o];
    lz[rs] += lz[o];
    lz[o] = 0;
  }
}

void update(int l, int r, ll v, int s = 1, int e = n, int o = 1)
{
  if (l <= s && e <= r)
  {
    t[o] += (e - s + 1) * v;
    lz[o] += v;
    return;
  }
  int mid = (s + e) >> 1;
  pushdown(s, e, o);
  if (mid >= l)
    update(l, r, v, s, mid, o << 1);
  if (mid + 1 <= r)
    update(l, r, v, mid + 1, e, o << 1 | 1);
  push(o);
}

ll query(int l, int r, int s = 1, int e = n, int o = 1)
{
  if (l <= s && e <= r)
  {
    return t[o];
  }
  int mid = (s + e) >> 1;
  ll ans = 0;
  pushdown(s, e, o);
  if (mid >= l)
    ans += query(l, r, s, mid, o << 1);
  if (mid + 1 <= r)
    ans += query(l, r, mid + 1, e, o << 1 | 1);
  return ans;
}

void solve()
{
  cin >> n >> k;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  build();
  while (k--)
  {
    int x;
    cin >> x;
    if (x == 1)
    {
      int l, r, k;
      cin >> l >> r >> k;
      update(l, r, k);
    }
    else
    {
      int l, r;
      cin >> l >> r;
      cout << query(l, r) << '\n';
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

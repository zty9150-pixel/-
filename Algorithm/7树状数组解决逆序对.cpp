#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e5 + 20;
int n, m;
int a[N], tree[N];

int lowbit(int x) { return x & -x; }

void update(int x, int k)
{
  for (int i = x; i <= n; i += lowbit(i))
    tree[i] += k;
}

int getPrefix(int x)
{
  int sum = 0;
  for (int i = x; i > 0; i -= lowbit(i))
    sum += tree[i];
  return sum;
}

int getSum(int a, int b)
{
  return getPrefix(a) - getPrefix(b - 1);
}

void solution()
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  vector<int> b;
  for (int i = 1; i <= n; ++i)
    b.push_back(a[i]);
  sort(b.begin(), b.end());
  b.erase(unique(b.begin(), b.end()), b.end());
  ll ans = 0;
  for (int i = 1; i <= n; ++i)
  {
    int id = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    ans += (i - 1) - getPrefix(id);
    update(id, 1);
  }
  cout << ans;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  solution();
  return 0;
}

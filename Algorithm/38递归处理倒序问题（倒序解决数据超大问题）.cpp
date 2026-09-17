#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;

int n, m;
int a[N];
int c[N];
char b[N];
int ans;

void dfs(int l, int r, int dep)
{
  if (l == r)
  {
    ans = a[r] % m;
    c[dep] = ans;
    return;
  }
  if (b[dep] == 'L')
    dfs(l + 1, r, dep + 1);
  else
    dfs(l, r - 1, dep + 1);
  ans = ((ans % m) * ((b[dep] == 'R' ? a[r] : a[l] % m))) % m;
  c[dep] = ans;
}

void solution()
{
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0; i < n; ++i)
    cin >> b[i];
  dfs(0, n - 1, 0);
  for (int i = 0; i < n; ++i)
    cout << c[i] << ' ';
  cout << "\n";
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
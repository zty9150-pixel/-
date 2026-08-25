#include <bits/stdc++.h>

using namespace std;

const int N = 1e7 + 10;
int n, a[N], stk[N], dpl[N], dpr[N];

void solution()
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  int top = 0;
  for (int i = 1; i <= n; ++i)
  {
    while (top && a[stk[top]] < a[i])
      top--;
    dpl[i] = top ? stk[top] : -1;
    stk[++top] = i;
  }
  top = 0;
  for (int i = n; i >= 1; --i)
  {
    while (top && a[stk[top]] < a[i])
      top--;
    dpr[i] = top ? stk[top] : -1;
    stk[++top] = i;
  }
  for (int i = 1; i <= n; ++i)
    cout << dpl[i] << ' ';
  cout << '\n';
  for (int i = 1; i <= n; ++i)
    cout << dpr[i] << ' ';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution();
  return 0;
}
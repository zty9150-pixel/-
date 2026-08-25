#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 1e5 + 10;

int n, a[N];

void solution1() // kadane******************************************
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  int cnt = a[1]; // cnt是以当前a[i]结尾的最大和子段
  int ans = cnt;  // 收集答案
  for (int i = 1; i <= n; ++i)
  {
    cnt = max(a[i], cnt + a[i]);
    ans = max(cnt, ans);
  }
  cout << ans;
}

int Sum(int l, int r) // 分治***************************************
{
  if (l == r)
    return a[l];
  int mid = (l + r) >> 1;
  int left_max = Sum(l, mid);
  int right_max = Sum(mid + 1, r);
  int left = INT_MIN, right = INT_MIN;
  int sum = 0;
  for (int i = mid; i >= l; --i)
  {
    sum += a[i];
    left = max(left, sum);
  }
  sum = 0;
  for (int i = mid + 1; i <= n; ++i)
  {
    sum += a[i];
    right = max(right, sum);
  }
  int cross_max = left + right;
  return max({left_max, right_max, cross_max});
}

void solution2()
{ // 分治
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  cout << Sum(1, n);
}

int one[N], two[N];
void solution3() // 子段至少2个数***********************************
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  int ans = INT_MIN;
  for (int i = 1; i <= n; ++i)
  {
    one[i] = a[i];                                      // 以a[i]结尾，长度为1
    two[i] = max(two[i - 1] + a[i], one[i - 1] + a[i]); // 以a[i]结尾，长度至少为2
    ans = max(ans, two[i]);
  }
  cout << ans;
}

int pre[N], L;
void solution4()
{ // 子段至少L个数*********************************
  cin >> n >> L;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i)
  {
    pre[i] = pre[i - 1] + a[i];
  }
  int mn = pre[0], ans = INT_MIN;
  for (int i = L; i <= n; ++i)
  {
    mn = min(mn, pre[i - L]);
    ans = max(ans, pre[i] - mn);
  }
  cout << ans;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution4();
  return 0;
}
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
const ll inf = 1e9;

int n;
string sx, sy;
ll dp[2][3];
int idx(int x)
{
  return x + 1;
}

void solution()
{
  cin >> n >> sx >> sy;
  for (int i = -1; i <= 1; ++i)
  {
    dp[0][idx(i)] = inf;
  }
  dp[0][idx(0)] = 0;
  for (int i = n - 1; i >= 0; --i)
  {
    int x = sx[i] - '0';
    int y = sy[i] - '0';
    for (int j = 0; j < 3; ++j)
      dp[1][j] = inf;
    for (int cin_c = -1; cin_c <= 1; ++cin_c)
    {
      if (dp[0][idx(cin_c)] == inf)
        continue;
      for (int k = -1; k <= 1; ++k)
      {
        ll delta = y + 10 * k - (x + cin_c);
        ll cost = abs(delta);
        dp[1][idx(k)] = min(dp[1][idx(k)], dp[0][idx(cin_c)] + cost);
      }
    }
    swap(dp[1], dp[0]);
  }
  ll ans = min({dp[0][0], dp[0][1], dp[0][2]});
  cout << ans;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();

  return 0;
}
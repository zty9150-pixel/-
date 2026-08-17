#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 20;
int n, pre[N], cnt_o[N], ans[N];
string s;
class MyQueue
{
public:
  deque<int> que;
  void pop(int value)
  {
    if (!que.empty() && value == que.front())
    {
      que.pop_front();
    }
  }
  void push(int value)
  {
    while (!que.empty() && value < que.back())
    {
      que.pop_back();
    }
    que.push_back(value);
  }
  int front()
  {
    return que.front();
  }
};
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  MyQueue mn;
  cin >> n;
  cin >> s;
  for (int i = 1; i <= n; ++i)
  {
    if (s[i - 1] == 'o')
      pre[i] = pre[i - 1];
    else
      pre[i] = pre[i - 1] - 1;
  }
  for (int i = 1; i <= n; ++i)
  {
    if (s[i - 1] == 'o')
      cnt_o[i] = cnt_o[i - 1] + 1;
    else
      cnt_o[i] = cnt_o[i - 1];
  }
  int k = 1, r = 1;
  // k是当前k值，r是目前可以走到的最大值
  mn.push(pre[1]);
  while (k <= n && r <= n)
  {
    if (cnt_o[k] + pre[r] - pre[k] >= mn.front())
    {
      r++;             // 计算下一个r
      mn.push(pre[r]); // 入队
    }
    else
    {
      ans[k] = r; // 记录答案
      mn.pop(k);  // 队列弹出
      k++;        // 计算下一个k
    }
  }
  if (k <= n)
  { // 此后全可以过，都算吃了n颗糖
    while (k <= n)
    {
      ans[k++] = n;
    }
  }
  for (int i = 1; i <= n; ++i)
  {
    cout << ans[i] << '\n';
  }
  return 0;
}
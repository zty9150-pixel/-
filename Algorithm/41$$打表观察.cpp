#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;

// 费佳在一所文理中学读书。费佳的数学家庭作业是计算下面这个式子：
//  (1^n + 2^n + 3^n + 4^n) mod 5
//  给定n的值。费佳已经算出了答案，你可以吗？注意给定的n可能极大（例如，它可以超出你所用编程语言的任意整数类型范围）。

// 输入
// 一行，包含一个整数$n$（$0 \le n \le 10^{105}$）。该数字不含前导零。

// 输出
// 输出表达式的值，不要带有前导零。

string s;

void solution()
{
  cin >> s;
  ll len = s.length();
  int x;
  if (len == 1)
  {
    x = (s[0] - '0') % 4;
  }
  else
  {
    x = stoi(s.substr(len - 2, 2)) % 4;
  }
  if (x == 0)
    cout << 4;
  else
    cout << 0;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();
  return 0;
}
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;

string s;

string bulidMin(int x)
{
  return string(x / 2, '4') + string(x / 2, '7');
}

bool super(string s)
{
  int cnt4 = 0;
  int cnt7 = 0;
  for (auto &i : s)
  {
    if (i == '4')
      cnt4++;
    else if (i == '7')
      cnt7++;
    else
      return false;
  }
  if (cnt4 == cnt7)
    return true;
  else
    return false;
}

void solution() // 自己写的版本
{
  cin >> s;
  int len = s.length();
  if (len % 2) // 奇数直接生成
  {
    cout << bulidMin(len + 1) << '\n';
    return;
  }
  if (super(s)) // 已经是幸运数，直接cout
  {
    cout << s << '\n';
    return;
  }
  int cnt4 = 0, cnt7 = 0;
  int best_i = -1; // best保存的是尽可能靠右的点，此点左边与幸运数一致，从此点向右开始构造更大数
  char best_d = 0;
  int best_c4 = 0, best_c7 = 0;

  for (int i = 0; i < len; ++i)
  {
    char c = s[i];
    char d = 0;
    if (c < '4')
      d = '4';
    else if (c < '7') // 如果c==4会把d变成7，因为4有变成7的可能
      d = '7';

    if (d != 0)
    {
      int n4 = cnt4 + (d == '4'); // 此点与可能的幸运数一致，测试能不能更新相同部分右端点
      int n7 = cnt7 + (d == '7');
      int rem = len - i - 1;

      if (abs(n4 - n7) <= rem) // 如果剩余位置可以实现47平衡就更新
      {
        best_i = i;
        best_d = d;
        best_c4 = cnt4;
        best_c7 = cnt7;
      }
    }
    if (c == '4') // 统计47数量
      cnt4++;
    else if (c == '7')
      cnt7++;
    else
      break; // 大于7的位置直接出来，最右端已确认是此位置的上一个位置
  }
  if (best_i != -1) // 开始构造更大的数
  {
    string ans;
    ans += s.substr(0, best_i);
    ans.push_back(best_d);
    if (best_d == '4')
      best_c4++;
    else if (best_d == '7') // 加上已确定的右端点的47数
      best_c7++;
    int cur4 = best_c4;
    int cur7 = best_c7;

    for (int i = best_i + 1; i < len; ++i)
    {
      int rem_after = len - i - 1;
      if (abs((cur4 + 1) - cur7) <= rem_after) // 测试剩余位置是否可以实现47平衡
      {
        ans += '4';
        cur4++;
      }
      else
      {
        ans += '7';
        cur7++;
      }
    }
    cout << ans << '\n';
  }
  else
  {
    cout << bulidMin(len + 2) << '\n'; // 不能构造直接生成，比如8400
  }
}

void solution2() // AI版本
{
  string s;
  cin >> s;

  int n = s.size();

  // 长度为奇数
  if (n % 2)
  {
    cout << bulidMin(n + 1) << '\n';
    return;
  }

  int cnt4 = 0, cnt7 = 0;

  // 先判断是不是本身就是超级幸运数
  for (char c : s)
  {
    if (c == '4')
      cnt4++;
    else if (c == '7')
      cnt7++;
  }

  if (cnt4 == n / 2 && cnt7 == n / 2)
  {
    cout << s << '\n';
    return;
  }

  // 从右往左找第一个可以增大的位置
  cnt4 = cnt7 = 0;

  for (int i = 0; i < n; i++)
  {
    if (s[i] == '4')
      cnt4++;
    else
      cnt7++;
  }

  for (int i = n - 1; i >= 0; i--)
  {
    // 删除当前位置对计数的影响
    if (s[i] == '4')
      cnt4--;
    else
      cnt7--;

    char d;

    // 当前位只能：
    // 4 -> 7
    // 7 -> 无法变大
    if (s[i] == '4')
      d = '7';
    else
      continue;

    int new4 = cnt4;
    int new7 = cnt7 + 1;

    int rem = n - i - 1;

    // 剩余位置可以把数量补平
    if (abs(new4 - new7) <= rem)
    {
      string ans = s.substr(0, i);
      ans += d;

      int need4 = n / 2 - new4;
      int need7 = n / 2 - new7;

      ans += string(need4, '4');
      ans += string(need7, '7');

      cout << ans << '\n';
      return;
    }
  }

  // 当前长度不存在答案
  cout << bulidMin(n + 2) << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution();
  return 0;
}
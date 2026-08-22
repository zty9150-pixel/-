#include <bits/stdc++.h>

using namespace std;

const int N = 1100000; // 考虑到数据范围 A_i <= 10^6，顺延开大一点
int n, a[N], b[N];

int lowbit(int x) { return x & -x; }

// 单点修改：标记位置 x 已被占用 (+1)
void update(int x, int k)
{
  for (int i = x; i < N; i += lowbit(i))
  {
    b[i] += k;
  }
}

// 区间查询：查询 1 ~ x 中已被占用的数量
int ask(int x)
{
  int sum = 0;
  for (int i = x; i > 0; i -= lowbit(i))
  {
    sum += b[i];
  }
  return sum; // 记得加上 return
}

void solution() // 官方二分加树状数组
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
  {
    cin >> a[i];
  }

  for (int i = 1; i <= n; ++i)
  {
    int target = a[i];
    int l = target, r = N - 1;
    int ans = target;

    // 二分查找第一个空闲位置
    while (l <= r)
    {
      int mid = l + (r - l) / 2;
      int used = ask(mid) - ask(target - 1);      // [target, mid] 被占用的个数
      int free_slots = (mid - target + 1) - used; // [target, mid] 空闲的个数

      if (free_slots >= 1)
      {
        ans = mid; // 找到了可行解，尝试向左找更小的空位
        r = mid - 1;
      }
      else
      {
        l = mid + 1; // 当前区间全满，向右找
      }
    }

    cout << ans << (i == n ? "" : " ");
    update(ans, 1); // 确定占用 ans，更新树状数组
  }
  cout << "\n";
}
void solution2() // 自己写的
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i)
  {
    int target = a[i];
    int l = target, r = N - 1;
    while (l < r)
    {
      int mid = (l + r) >> 1;
      int used = ask(mid) - ask(target - 1);    // mid到target中间有多少1
      int free_slots = mid - target + 1 - used; // mid到target中间有多少0
      if (free_slots >= 1)
      {
        r = mid;
      }
      else
      {
        l = mid + 1;
      }
    }
    cout << r << ' ';
    update(r, 1);
  }
}

int par[N]; // 记录i到最后第一个空着的点位置，初始都为自己本身

int root(int x)
{
  return par[x] = (par[x] == x ? x : root(par[x]));
}

void solution3()
{ // 并查集做法，将连续的已处理的连续元素视为连通块
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= N - 1; ++i)
  {
    par[i] = i;
  }
  for (int i = 1; i <= n; ++i)
  {
    int rt = root(a[i]);
    par[rt] = rt + 1; // 下一次root会自动修复rt+1到自己的root上，但也可以写成root(rt + 1)
    cout << rt << ' ';
  }
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution3();
  return 0;
}
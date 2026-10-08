/*时间限制：2 秒 / 内存限制：1024 MiB
分值：300 分

问题描述
给定长度为 N 的整数序列 A=(A₁,A₂,…,A_N)。
你需要对 A 执行恰好一次如下操作：
选择一个整数 i，满足 1 ≤ i ≤ N−K+1。将 A_i,A_{i+1},…,A_{i+K−1} 升序排序。形式化描述：把 A_i 到 A_{i+K−1} 的数从小到大排列得到 B₁,B₂,…,B_K，然后对 1≤j≤K，令 A_{i+j−1}=B_j。

判断：执行完这一次操作之后，整个数组是否可以变成升序数组（对所有 1≤i<N，满足 A_i ≤ A_{i+1}）。

约束条件
1 ≤ K < N ≤ 2×10⁵
1 ≤ A_i ≤ N
所有输入均为整数。

输入格式
N K A₁ A₂ … A_N

输出格式
如果恰好一次操作后数组能升序，输出 Yes；否则输出 No。
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;

int n, k;
int a[N];
bool pre[N], suf[N];

deque<int> qmin, qmax;

// 加入下标 idx
void push(int idx)
{
    // 维护最小值单调队列
    while (!qmin.empty() && a[qmin.back()] >= a[idx])
        qmin.pop_back();
    qmin.push_back(idx);

    // 维护最大值单调队列
    while (!qmax.empty() && a[qmax.back()] <= a[idx])
        qmax.pop_back();
    qmax.push_back(idx);
}

// 删除已经离开窗口的下标 idx
void pop(int idx)
{
    if (!qmin.empty() && qmin.front() == idx)
        qmin.pop_front();

    if (!qmax.empty() && qmax.front() == idx)
        qmax.pop_front();
}

void solve()
{
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    // pre[i]：1 ~ i 是否有序
    pre[1] = true;
    for (int i = 2; i <= n; ++i)
    {
        pre[i] = pre[i - 1] && (a[i - 1] <= a[i]);
    }

    // suf[i]：i ~ n 是否有序
    suf[n] = true;
    for (int i = n - 1; i >= 1; --i)
    {
        suf[i] = suf[i + 1] && (a[i] <= a[i + 1]);
    }

    qmin.clear();
    qmax.clear();

    // 初始化第一个窗口 [1, k]
    for (int i = 1; i <= k; ++i)
        push(i);

    // 枚举窗口左端点 l
    for (int l = 1; l + k - 1 <= n; ++l)
    {
        int r = l + k - 1;

        int mn = a[qmin.front()];
        int mx = a[qmax.front()];

        bool ok = true;

        // 左边 [1, l-1] 必须有序
        if (l > 1 && !pre[l - 1])
            ok = false;

        // 右边 [r+1, n] 必须有序
        if (r < n && !suf[r + 1])
            ok = false;

        // 左边最后一个 <= 排序后区间最小值
        if (l > 1 && a[l - 1] > mn)
            ok = false;

        // 排序后区间最大值 <= 右边第一个
        if (r < n && mx > a[r + 1])
            ok = false;

        if (ok)
        {
            cout << "Yes\n";
            return;
        }

        // 窗口向右移动
        if (r + 1 <= n)
        {
            pop(l);
            push(r + 1);
        }
    }

    cout << "No\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
题目：Polycarp's Tea Party 杯子倒茶问题
n个杯子，每个杯子容量a[i]，茶壶共有w毫升茶。
设b[i]为第i个杯子最终倒入的茶量，必须满足全部4个条件：
1. b[i]是整数，ceil(a[i]/2) <= b[i] <= a[i]，每个杯子至少装一半（向上取整）
2. sum(b) == w，茶壶所有茶必须全部倒入杯子
3. 单调性约束：若 a[i] > a[j]，则 b[i] >= b[j]
   人话：容量更大的杯子，里面的茶不能更少。
4. 输出任意合法方案；无解输出 -1

输入：
第一行 n w
第二行 a1 a2 ... an

输出：
一行整数 b1 b2 ... bn，无解输出 -1

算法思路：
1. 初始化每个杯子b[i] = (a[i]+1)/2 （整数除法，等价向上取整），计算sum_min所有下限总和
2. 如果 sum_min > w：直接无解，输出-1
3. rem = w - sum_min，剩余可以额外分配的茶量
4. 将杯子【保留原下标】按容量从大到小排序
5. 依次遍历排序后的杯子：
   当前杯子最多还能加 addMax = a[i] - b[i]
   add = min(rem, addMax)
   b[i] += add; rem -= add;
   rem == 0 就停止分配
6. 按原始下标顺序输出b数组

核心贪心原理：
优先给容量大的杯子补茶。这样永远保证：大杯子的茶量 >= 小杯子，不会破坏单调性约束。
如果反过来先给小杯子补，很容易出现大杯子茶更少，违反条件。

坑点提醒：
①排序的时候必须记录原来的下标，最后输出顺序不能乱
②条件是 >=，不是严格 >，相等是合法的
③b[i]不能超过杯子本身容量a[i]
*/


struct node{
    int a,idx;
};
int n,w;

bool cmp(node a,node b){
    return a.a> b.a;
}

void solve()
{
    //向上取cell，n+k-1/k //*************************
    cin>>n>>w;
    vector<node> a(n);
    vector<int> b(n);
    int sum = 0;
    for(int i = 0;i < n;++i){
        a[i].idx = i;
        cin>>a[i].a;
        b[i] = (a[i].a + 1) / 2;
        sum += b[i];
    }
    if(sum > w){
        cout<<-1;
        return;
    }
    sort(a.begin(),a.end(),cmp);
    int rem = 0;
    for(auto &i : a){
        int c = i.a - b[i.idx];
        int add = min(rem,c);
        b[i.idx] += add;
        rem -= add;
        if(rem == 0) break;
    }
    for(int i = 0;i < n;++i) cout<<b[i]<<' ';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}
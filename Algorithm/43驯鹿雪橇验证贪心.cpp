/*
题目：驯鹿雪橇问题
有 N 只驯鹿和一架雪橇。第 i 只驯鹿体重 W_i，力量 P_i。
每只驯鹿二选一：拉雪橇 / 坐在雪橇上。
约束条件：所有拉雪橇驯鹿的力量总和 ≥ 坐在雪橇驯鹿的总体重。
求最多可以让多少只驯鹿坐在雪橇上。

输入：
T 组测试用例。
每组第一行 N。
接下来 N 行，每行两个整数 W_i, P_i。

数据范围：
1 ≤ N ≤ 3e5
1 ≤ W_i,P_i ≤ 1e9
所有测试用例的 N 总和 ≤ 3e5

输出：
每组输出一个整数：最多坐在雪橇上的驯鹿数量。

思路：驯鹿选为乘客，**代价 = 增加的重量 W，同时损失掉原本可以提供的拉力 P，总代价就是 W+P**。
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;

void solve()
{
    cin>>n;
    vector<ll> s(n);
    ll sum_p = 0;
    for(int i = 0;i < n;++i){
        ll w,p;cin>>w>>p;
        sum_p += p;
        s[i] = p + w;
    }
    sort(s.begin(),s.end());
    vector<ll> pre(n+1,0);
    for(int i=0;i<n;i++){
        pre[i+1] = pre[i] + s[i];
    }
    auto check = [&](int x)
    {
        return pre[x] <= sum_p;
    };
    int l = 0, r = n;
    while(l < r){
        int mid = (l + r + 1) >> 1;
        if(check(mid)){
            l = mid;
        }else{
            r = mid - 1;
        }
    }
    cout<<l<<'\n';
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

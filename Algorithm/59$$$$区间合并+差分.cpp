/*
题目：区间加元素到集合，求每个集合最终元素个数（集合自动去重）
题意：
N个空集合S1~SN，Q次操作(L,R,X)：把X加入S[L]~S[R]。
所有操作结束后输出每个集合的元素数量，相同X多次加入同一集合只计1次。
限制：N,Q ≤ 2e5

思路：离线处理
1. 按X分组，收集每个X对应的所有区间[L,R]
2. 对同一个X的区间排序+合并重叠区间（同一个X只贡献1次）
3. 合并后的区间用差分数组区间+1
4. 差分求前缀和，得到每个位置答案

复杂度：O(Q log Q + N)
*/

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;

int n,q;
vector<pair<int,int>> v[N];
int diff[N];

void solve()
{
    cin>>n>>q;
    for(int i = 1;i <= q;++i){
        int l,r,x;
        cin>>l>>r>>x;
        v[x].push_back({l,r});
    }
    
    for(int x = 1;x <= q;++x){
        if(v[x].empty()) continue;
        sort(v[x].begin(),v[x].end());

        int l = v[x][0].first;
        int r = v[x][0].second;
        for(auto [nl,nr] : v[x]){
          if(nl <= r + 1){
            r = max(nr,r);
          }else{
            diff[l]++;
            diff[r + 1]--;

            l = nl;
            r = nr;
          }
        }
        diff[l]++;
        diff[r + 1]--;
    }
    int x = 0;
    for(int i = 1;i <= n;++i){
      x += diff[i];
      cout<<x<<' ';
    }

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

        solve();

    return 0;
}

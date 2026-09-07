#include <bits/stdc++.h>
using namespace std;

int q;
map<string, string> mp;
set<string> newName;
vector<string> old;
vector<string> allOld;

string find(string od)
{
  if (!mp.count(od))
    return od;

  return find(mp[od]);
}
void solution()
{
  cin >> q;

  for (int i = 1; i <= q; ++i)
  {
    string od, nw;
    cin >> od >> nw;

    mp[od] = nw;
    newName.insert(nw);

    allOld.push_back(od);
  }
  for (auto &od : allOld)
  {
    if (!newName.count(od))
    {
      old.push_back(od);
    }
  }
  for (auto &od : old)
  {
    cout << od << ' ' << find(od) << '\n';
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();

  return 0;
}
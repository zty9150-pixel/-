#include <iostream>
using namespace std;
int b[100], a[100], c[100], tmp[100];
// n*m��������ֻҪ������������һ�к�����Ը�������ż���Ƿ���ͬ�����ж����������Ƿ��ǹ�ͨ��
/*void Mergesort(int a[],int l,int r){ //�����鲢
  if(r == l) return;
  int mid = (r + l) / 2;
  Mergesort(a,l,mid);
  Mergesort(a,mid + 1,r);
  int pb = l,pr = mid + 1,pl = l;
  while(pl <= mid || pr <= r){
    if(pl > mid){
      b[pb++] = a[pr++];
    }else if(pr > r){
      b[pb++] = a[pl++];
    }else{
      if(a[pr] <= a[pl]) b[pb++] = a[pr++];
      else b[pb++] = a[pl++];
    }
  }
  for(int i = l;i <= r;++i){
    a[i] = b[i];
  }
}
int main(){
  int n;cin>>n;
  for(int i = 1;i <= n;++i){
    cin>>a[i];
  }
  Mergesort(a,1,n);
  for(int i = 1;i <= n;++i){
    cout<<a[i]<<' ';
  }
  return 0;
}*/
int ans = 0;
void Mergesort(int a[], int l, int r)
{
  if (r == l)
    return;
  int mid = (r + l) / 2;
  Mergesort(a, l, mid);
  Mergesort(a, mid + 1, r);
  int pb = l, pr = mid + 1, pl = l;
  while (pl <= mid && pr <= r)
  {
    if (a[pl] > a[pr])
    {
      ans += mid - pl + 1;
      pr++;
    }
    else
    {
      pl++;
    }
  }
  pb = l;
  pr = mid + 1;
  pl = l;
  while (pl <= mid || pr <= r)
  {
    if (pl > mid)
    {
      b[pb++] = a[pr++];
    }
    else if (pr > r)
    {
      b[pb++] = a[pl++];
    }
    else
    {
      if (a[pr] <= a[pl])
        b[pb++] = a[pr++];
      else
        b[pb++] = a[pl++];
    }
  }
  for (int i = l; i <= r; ++i)
  {
    a[i] = b[i];
  }
}
long long merge_sort(int l, int r)
{

  if (l >= r)
    return 0;

  int mid = (l + r) >> 1;
  long long ans = 0;

  ans += merge_sort(l, mid);
  ans += merge_sort(mid + 1, r);

  int i = l, j = mid + 1, k = 0;

  while (i <= mid && j <= r)
  {
    if (a[i] <= a[j])
      tmp[k++] = a[i++];
    else
    {
      ans += mid - i + 1; // ���Ĺ�ʽ
      tmp[k++] = a[j++];
    }
  }

  while (i <= mid)
    tmp[k++] = a[i++];
  while (j <= r)
    tmp[k++] = a[j++];

  for (int t = 0; t < k; t++)
    a[l + t] = tmp[t];

  return ans;
}
long long merge_sort2(int l, int r)
{
  if (l >= r)
    return 0;
  int tmp[100];
  int mid = (l + r) >> 1;
  long long ans = 0;
  ans += merge_sort2(l, mid);
  ans += merge_sort2(mid + 1, r);
  int pl = l, pr = mid + 1, pb = l;
  while (pl <= mid && pr <= r)
  {
    if (a[pl] <= a[pr])
    {
      tmp[pb++] = a[pl++];
    }
    else
    {
      ans += mid - pl + 1;
      tmp[pb++] = a[pr++];
    }
  }
  while (pl <= mid)
    tmp[pb++] = a[pl++];
  while (pr <= r)
    tmp[pb++] = a[pr++];
  for (int i = l; i <= r; ++i)
  {
    a[i] = tmp[i];
  }
  return ans;
}
int main()
{
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i)
  {
    cin >> a[i];
  }
  Mergesort(a, 1, n);
  cout << ans;
  return 0;
}

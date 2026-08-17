#include <iostream>
using namespace std;
int a[100];
// 标准快排
int Partition(int a[], int l, int r)
{
	int i = l, j = r;
	int pivot = a[r];
	while (i < j)
	{
		while (i < j && a[i] <= pivot)
			i++;
		while (i < j && a[j] >= pivot)
			j--;
		if (i < j)
			swap(a[i], a[j]);
	}
	swap(a[i], a[r]);
	return i;
}
void QuickSort(int a[], int l, int r)
{
	if (l < r)
	{
		int mid = Partition(a, l, r);
		QuickSort(a, l, mid - 1);
		QuickSort(a, mid + 1, r);
	}
}
// 快排优化第k大数
int Partition(int a[], int l, int r)
{
	int i = l, j = r;
	int pivot = a[r];
	while (i < j)
	{
		while (i < j && a[i] <= pivot)
			i++;
		while (i < j && a[j] >= pivot)
			j--;
		if (i < j)
			swap(a[i], a[j]);
	}
	swap(a[i], a[r]);
	return i;
}
int QuickSelect(int a[], int l, int r, int k)
{
	if (l == r)
		return a[l];

	int mid = Partition(a, l, r);

	if (mid == k)
		return a[mid];
	else if (mid > k)
		return QuickSelect(a, l, mid - 1, k);
	else
		return QuickSelect(a, mid + 1, r, k);
}
// 调试第k大数
int main()
{
	int n, k;
	cin >> n >> k;

	for (int i = 0; i < n; i++)
		cin >> a[i];

	cout << QuickSelect(a, 0, n - 1, n - k);
}
// 正常调试
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
	}
	QuickSort(a, 1, n);
	for (int i = 1; i <= n; ++i)
	{
		cout << a[i] << ' ';
	}
}

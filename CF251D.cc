/**************************************************
* Date:	2014-06-05 星期四 20:16:11
* Source: CF Round 251
* Comments: 构造凸函数的方法很难想到，但应该是正确的。
* 另一种方法，感觉说不出来为什么正确，但是似乎更容易想到。
**************************************************/
#include <iostream>
#include <algorithm>
using namespace std;
const int N=100002;
int main()
{
	int n,m;
	int a[N],b[N];
	cin>>n>>m;
	for(int i=0;i<n;++i)
		cin>>a[i];
	for(int i=0;i<m;++i)
		cin>>b[i];
	sort(a,a+n);
	sort(b,b+m);
	long long cnt=0;
	for(int i=0,j=m-1;i<n&&j>=0;++i,--j)
	{
		if(b[j]<=a[i])break;
		cnt += b[j]-a[i];
	}
	cout<<cnt<<endl;
	return 0;
}

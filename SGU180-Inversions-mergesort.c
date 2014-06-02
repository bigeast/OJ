/**************************************************
* Date:	2014-06-02-12:08:53
* Source: SGU 
* Comments: 逆序数。除了暴力的O(n^2)算法，还有其它的吗？
* 查了网上，还有两种O(n logn)的算法：归并排序和树状数组
*
* 注意元素相等时的情况；另外cnt设成int时会溢出，因为题目
* 故意给了2^16+1个元素，最坏情况下逆序数会超出2^31
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 65538
unsigned cnt=0;
int tmp[N];
int Merge(int *array,int l,int r)
{
	int m=l+(r-l)/2,p=l,q=m+1,pos=l;
	while(p<=m&&q<=r)
	{
		if(array[p]<=array[q])
			tmp[pos++]=array[p++];
		else
		{
			tmp[pos++]=array[q++];
			cnt+=m-p+1;
		}
	}
	while(p<=m)
		tmp[pos++]=array[p++];
	while(q<=r)
		tmp[pos++]=array[q++];
	memcpy(array+l,tmp+l,sizeof(int)*(r-l+1));
	return 0;
}
int MergeSort(int *array,int l,int r)
{
	if(l==r)return 0;
	int mid=l+(r-l)/2;
	MergeSort(array,l,mid);
	MergeSort(array,mid+1,r);
	Merge(array,l,r);
	return 0;
}
int main(int argc, const char *argv[])
{
	int n,a[N];
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d",&a[i]);
	MergeSort(a,0,n-1);
	printf("%u\n",cnt);
	return 0;
}

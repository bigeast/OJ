/**************************************************
* Date:	2014-06-02 星期一
* Source: SGU 
* Comments: 假设要频繁查询一个数组中，任意段的和。
* 显然要先计算出Sum{1..n}这个数组，然后每段的和只需要一次减法操作。
* 但如果数组元素会频繁更新，那么这种方法带来的好处就降低了。因为
* 一个元素的改变会影响到O(n)个Sum中的元素的改变。
* 树状数组的思想是，使每次改变影响到的Sum中的元素个数尽量少，所以
* Sum[n]中就不能直接存所有1到n的元素之和。记新的Sum数组为Csum。
*
* 树状数组中：
* 每改变位置在pos的一个元素，会影响到pop(pos)个Csum数组中的值；
* 每计算一次真正的和Sum[pos]，需要pop(pos)个Csum元素相加。
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 65538
unsigned cnt=0;
int csum[N],n;
int LowBit(int n)
{
	return n&(n^(n-1));
}
int Sum(int n)
{
	int res=0;
	while(n>0)
	{
		res+=csum[n];
		n-=LowBit(n);
	}
	return res;
}
int Add(int pos,int val)
{
	while(pos<=n)
	{
		csum[pos]+=val;
		pos+=LowBit(pos);
	}
	return 0;
}
typedef struct _node
{
	int val;
	int pos;
}node;
int cmp(const void *p1,const void *p2)
{
	return ((node *)p2)->val - ((node *)p1)->val;
}
int main(int argc, const char *argv[])
{
	scanf("%d",&n);
	node a[N];
	
	for(int i=1;i<=n;++i)
		a[i].pos=i;

	for(int i=1;i<=n;++i)
		scanf("%d",&a[i].val);

	qsort(a+1,n,sizeof(node),cmp);
	a[0].val=-1;
	for(int i=1,t,j;i<=n;++i)
	{
		t=a[i].val;
		j=0;
		do
		{
			Add(a[i+j].pos,1);
			cnt+=Sum(a[i+j].pos-1);
	//		printf("val:%d inv:%d\n",a[i].val,Sum(a[i+j].pos-1));
			Add(a[i+j].pos,-1);
			++j;
		}while(a[i+j].val==t);
		for(int k=0;k<j;++k)
		{
			Add(a[i+k].pos,1);
		}
		i+=j-1;
	}
	printf("%u\n",cnt);
	return 0;
}

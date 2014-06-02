/**************************************************
* Date:	2014-06-02-10:24:43
* Source: SGU
* Comments: 花了大概半个小时。先按线段的起点排序，然后根据终点的大小，
* 看能否包含后面的线段。这个应该有更好的实现，现在用的flag什么的应该太麻烦了。
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#define N 16000
typedef struct _node
{
	int x;
	int y;
}node;
node outpost[N];
int cmp(const void *p1,const void *p2)
{
	return ((node*)p1)->x - ((node*)p2)->x;
}
int main(int argc, const char *argv[])
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d %d",&outpost[i].x,&outpost[i].y);
	qsort(outpost,n,sizeof(node),cmp);
	int res=0,pos=0,t,flag;
	while(pos<n)
	{
		t=outpost[pos].y;
		flag=0;
		while(pos<n-1 && t>outpost[pos+1].y)
		{
	//		printf("%d %d\n",t,outpost[pos+1].y);
			++res;
			++pos;
			if(flag==0)flag=1;
		}
		if(flag==0)++pos;
	}
	printf("%d\n",res);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
int cmp(const void *p1,const void *p2)
{
	return (*(int *)p1)-(*(int *)p2);
}
int main(int argc, const char *argv[])
{
	int n,x;
	int a[100002];
	scanf("%d %d",&n,&x);
	for(int i=0;i<n;++i)
		scanf("%d",&a[i]);
	if(x>1)qsort(a,n,sizeof(int),cmp);
	long long cnt=0;
	for(int i=0;i<n;++i)
	{
		cnt+=(long long)a[i]*(i<x?(x-i):1);
	}
	printf("%I64d\n",cnt);
	return 0;
}

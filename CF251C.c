#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
	int n,k,p;
	int a,odd[100002],even[100002];
	scanf("%d %d %d",&n,&k,&p);
	int co=0,ce=0;
	for(int i=0;i<n;++i)
	{
		scanf("%d",&a);
		if(a&1)odd[co++]=a;
		else even[ce++]=a;
	}
	//if(p>ce+co/2 || co<k-p || (co-(k-p))%2!=0)
	//{
	//	puts("NO");
	//	return 0;
	//}
	/*
	if(p==ce)
	{
		if((co-(k-p))%2!=0)
		{
			puts("NO");
			return 0;
		}
		puts("YES");
		for(int i=0;i<p;++i)
			printf("1 %d\n",even[i]);
		for(int i=0;i<k-p-1;++i)
			printf("1 %d\n",odd[i]);
	}
	*/
	if(p<=ce)
	{
		if(co<(k-p) || (co-(k-p))%2!=0)
		{
			puts("NO");
			return 0;
		}
		puts("YES");
		for(int i=0;i<p;++i)
			printf("1 %d\n",even[i]);
		for(int i=0;i<k-p-1;++i)
			printf("1 %d\n",odd[i]);
		printf("%d",n-k+1);
		for(int i=p;i<ce;++i)
			printf(" %d",even[i]);
		for(int i=k-p-1;i<co;++i)
			printf(" %d",odd[i]);
		putchar('\n');
	}
	else
	{
		if(k-p+2*(p-ce) < co || (k-p+2*(p-ce)-co)%2!=0)
		{
			puts("NO");
			return 0;
		}
		puts("YES");
		for(int i=0;i<ce;++i)
			printf("1 %d\n",even[i]);
		for(int i=0;i<p-ce;++i)
		{
			printf("2 %d %d\n",odd[2*i],odd[2*i+1]);
		}
		for(int i=0;i<k-p-1;++i)
			printf("1 %d\n",odd[2*(p-ce)+i]);
		for(int i=k-p-1;i<co;++i)
			printf("1 %d\n",odd[i]);
	}
	return 0;
}

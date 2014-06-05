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
	if(p>ce+co/2 || co<k-p || (co-(k-p))%2!=0)
	{
		puts("NO");
		return 0;
	}
	if(p<=ce)
	{
		puts("YES");

		if(p==0)
		{
			for(int i=0;i<k-p-1;++i)
				printf("1 %d\n",odd[i]);
			printf("%d",n-(k-p-1));
			for(int i=k-p-1;i<co;++i)
				if(i>=0)printf(" %d",odd[i]);
			for(int i=0;i<ce;++i)
				printf(" %d",even[i]);
			putchar('\n');
		}
		else if(k==p)
		{
			for(int i=0;i<p-1;++i)
				printf("1 %d\n",even[i]);
			printf("%d",n-(p-1));
			for(int i=p-1;i<ce;++i)
				printf(" %d",even[i]);
			for(int i=0;i<co;++i)
				if(i>=0)printf(" %d",odd[i]);
			putchar('\n');

		}
		else
		{
			for(int i=0;i<p;++i)
				printf("1 %d\n",even[i]);
			for(int i=0;i<k-p-1;++i)
				printf("1 %d\n",odd[i]);
			printf("%d",n-k+1);
			for(int i=k-p-1;i<co;++i)
				printf(" %d",odd[i]);
			for(int i=p;i<ce;++i)
				printf(" %d",even[i]);
			putchar('\n');
		}
	}
	else
	{
		int t=k-p+2*(p-ce);
		if( t > co || (co-t)%2!=0)
		{
			puts("NO");
			return 0;
		}
		puts("YES");
		for(int i=0;i<ce;++i)
			printf("1 %d\n",even[i]);
		for(int i=0;i<k-p;++i)
			printf("1 %d\n",odd[i]);
		if(t==co)
		{
			for(int i=0;i<p-ce;++i)
			{
				printf("2 %d %d\n",odd[k-p+2*i],odd[k-p+2*i+1]);
			}
		}
		else
		{
			for(int i=0;i<p-ce-1;++i)
			{
				printf("2 %d %d\n",odd[k-p+2*i],odd[k-p+2*i+1]);
			}
	//		printf("%d ",co-t);
			printf("%d ",co-t+2);
			for(int i=t-2;i<co;++i)
				printf("%d%c",odd[i],i==co-1?'\n':' ');
		}

	}
	return 0;
}

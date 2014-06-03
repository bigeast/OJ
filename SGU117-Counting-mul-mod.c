/**************************************************
* Date:	2014-06-03 Tuesday 19:53:22
* Source: SGU
* Comments: 快速幂取模。
**************************************************/
#include <stdio.h>
int expmod(int a,int n,int M)
{
	if(n==1)
		return a%M;
	int t=expmod(a,n/2,M);
	t=t*t%M;
	return n&1?t*a%M:t;
}
int main(int argc, const char *argv[])
{
	int n,m,k,a;
	int cnt=0;
	scanf("%d %d %d",&n,&m,&k);
	while(n--)
	{
		scanf("%d",&a);
		if(expmod(a,m,k)==0)
			cnt++;
	}
	printf("%d\n",cnt);
	return 0;
}

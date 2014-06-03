/**************************************************
* Date:	2014-06-03 Tuesday 20:17:32
* Source: SGU 
* Comments: Catalan数。C(n)为圆周上2n个点组成n条互不相交的
* 弦的所有方法数。
**************************************************/
#include <stdio.h>
#include <string.h>
long long Catalan(int n)
{
	if(n==1)return 1;
	long long res=2;
	char vis[31];
	memset(vis,0,sizeof(vis));
	for(int i=n+2;i<2*n;++i)
	{
		res*=i;
		for(int j=2;j<n;++j)
			if(!vis[j] && res%j==0)
			{
				res/=j;
				vis[j]=1;
			}
	}
	return res;
}
int main(int argc, const char *argv[])
{
	int k;
	scanf("%d",&k);
	printf("%lld %d\n",Catalan(k),k+1);
	return 0;
}

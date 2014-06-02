/**************************************************
* Date:	2014-06-02-11:51:54
* Source: SGU 
* Comments: 暴力搜索即可。根据$ n - l + 1 < 2^l $算出l，那么在用while循环时，条件应为$ n + 1 >= 2^l +l $，少了等号则可能出错，例如"5 bbaab"的情况。会算出l=2，但所有l=2的串都会出现，答案是l=3。
* n==1的情况不单独拿出来好像也可以
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LOGN 19
#define N 500000
int main(int argc, const char *argv[])
{
	int n,logn=0;
	char s[N];
	scanf("%d\n%s",&n,s);
	/* Optional
	n=strlen(s);
	if(n==1)
	{
		printf("1\n%c\n",'a'+'b'-s[0]);
		return 0;
	}
	*/
	/* n - logn + 1 < 2^logn */
	while(n+1>=(1<<logn)+logn)
		++logn;
	//printf("logn:%d\n",logn);
	char *mark=(char *)malloc(sizeof(char)*(1<<logn));
	int mask,cnt;
	for(int i=1,j;i<=logn;++i)
	{
		memset(mark,0,sizeof(char)*(1<<i));
		mask=0;
		cnt=0;
		for(j=0;j<i;++j)
		{
			mask <<= 1;
			mask |= s[j]-'a';
		}
		mark[mask]=1;
		cnt++;
		while(j<n)
		{
			mask &= ((1<<(i-1))-1);
			mask <<= 1;
			mask |= s[j]-'a';
			if(mark[mask]==0)
			{
				++cnt;
				mark[mask]=1;
			}
			++j;
		}
		if(cnt<(1<<i))
		{
			for(j=0;j<(1<<i);++j)
			{
				if(mark[j]==0)
				{
					printf("%d\n",i);
					int k=i-1;
					while(k>=0)
					{
						putchar('a'+ ((j&(1<<k))==0?0:1));
						--k;
					}
					putchar('\n');
					return 0;
				}

			}
		}
	}
	return 0;
}

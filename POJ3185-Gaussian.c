/**************************************************
* Date:	2014-06-04 星期三 15:55:19
* Source: POJ3185
* Comments: 看了SGU200，见识了高斯消元的作用，找到了一道水题，但是没有用高斯消
* 元做出来。数据太小，暴力搜索过了。
**************************************************/
#include <stdio.h>
int pop(int n)
{
	int cnt=0;
	while(n)
	{
		if(n&1)++cnt;
		n>>=1;
	}
	return cnt;
}
int main(int argc, const char *argv[])
{
	int s[21],stat=0;
	for(int i=0;i<20;++i)
	{
		scanf("%d",&s[i]);
		stat<<=1;
		stat|=s[i];
	}
	if(stat==0)
	{
		puts("0");
		return 0;
	}
	int curr_pop=20;
	for(int i=1;i<(1<<21);++i)
	{
		if(((stat^i)^(stat^((i<<1)&0xfffff))^(stat^(i>>1)))==0)
			if(pop(i)<curr_pop)
			{
				curr_pop=pop(i);
			}
	}
	printf("%d\n",curr_pop);
	return 0;
}
/*
int main(int argc, const char *argv[])
{
	int s[21],x[21];
	for(int i=0;i<20;++i)
		scanf("%d",&s[i]);
	s[18]+=s[19];
	for(int i=17;i>0;--i)
		s[i]=s[i]^s[i+1]^s[i+2];
	int cnt1=0,cnt2=0;

	x[19]=0;
	for(int i=18;i>0;--i)
	{
		x[i]=(i%3==0?1:0)*x[19]^s[i];
		if(x[i]==1)cnt1++;
	}
	if(x[1]==1)cnt1++;

	x[19]=1;
	for(int i=18;i>0;--i)
	{
		x[i]=(i%3==0?1:0)*x[19]^s[i];
		if(x[i]==1)cnt2++;
	}
	if(x[1]==1)cnt2++;
	printf("%d\n",cnt1<cnt2?cnt1:cnt2);
	return 0;
}
*/

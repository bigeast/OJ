#include <stdio.h>
int main(int argc, const char *argv[])
{
	int n,d,a,cnt=0;
	scanf("%d %d",&n,&d);
	for(int i=0;i<n;++i)
	{
		scanf("%d",&a);
		cnt+=a;
	}
	int res=cnt+(n-1)*10;
	if((d-res)>=0)
		printf("%d\n",(d-cnt)/5);
	else puts("-1");
	return 0;
}

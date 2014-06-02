/**************************************************
* Date:	2014-06-02 星期一  16:30:21
* Source: SGU
* Comments: 自己想出来的，递归！
* 定义f(len,pos)为：在长为len的序列中，第pos个字符最终所处的位置。
* 状态转移分两种情况：
* 1.pos<=len/2 要整体移到后面，因此该子串中元素的最终位置，要整体加len-len/2。
* 需要注意的是，还需要把该子串反转，就是把其元素的位置号由pos变成len/2+1-pos
* 2.pos>len/2 同理。与前一种情况不同的是，最终位置不需要整体平移，但每个元素
* 在子串中的位置要整体减len/2
*
* 感觉难点主要在反转那一步怎么实现。开始想着另外定义一个g(len,pos)代表长为len
* 的字符串反转后，原来位置为pos的元素在变换后的最终位置。g与f退出条件的区分
* 在于len==2时不同。但一旦把定义想明白，很容易知道此时g(len,pos)就等于f(len,len+1-pos)。
**************************************************/
#include <stdio.h>
int f(int len,int pos)
{
	if(len==1)return 1;
	int k=len/2;
	if(pos<=k)
		return len-k+f(k,(k+1)-pos);
	else
		return f(len-k,(len-k+1)-(pos-k));
}
int main(int argc, const char *argv[])
{
	int N,q;
	scanf("%d %d",&N,&q);
	printf("%d\n",f(N,q));
	return 0;
}

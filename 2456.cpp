#include <cstdio>

int main()
{
	int n,x,num=0,now;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(!num)
		{
			now=x;
			++num;
		}
		else
			if(now==x)
				num++;
			else
				num--;
	}
	printf("%d",now);
	return 0;
}

#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

int n,ai[10005];

std::bitset<10005>bit1,bit2;

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

int main()
{
//	freopen("nt2011_sequence.in","r",stdin);
//	freopen("nt2011_sequence.out","w",stdout);
//	freopen("data.txt","r",stdin);
//	freopen("ade.txt","w",stdout);
	int T;
	read(T);
	while(T--)
	{
		read(n);
		bit1.reset();
		bit2.reset();
		for(int i=1;i<=n;i++) read(ai[i]),bit2[ai[i]]=1;
		bool ans=false;
		bit2[n-ai[1]+1]=false;
		for(int i=2;i<n;i++)
		{
			bit1[ai[i-1]]=true;
			bit2[n-ai[i]+1]=false;
			if(ai[i]*2-n-1>=0)
			{
				if((bit1&(bit2<<(ai[i]*2-n-1))).any())
				{
					ans=true;
					break;
				}
			}
			else
			{
				if((bit1&(bit2>>(1+n-ai[i]*2))).any())
				{
					ans=true;
					break;
				}
			}
		}
		if(ans) puts("Y");
		else puts("N");
	}
	return 0;
}

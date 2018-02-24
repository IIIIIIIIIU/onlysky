#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef unsigned long long ll;
const int mod1=29;
const int mod2=37;
const int mod=1e9+7;
const int maxn=1e6+5;
int T,n,num[maxn];
ll Hash1[maxn],Hash2[maxn],hpos1[maxn],hpos2[maxn];
char str[maxn];
inline int getlen(int x)
{
	int l=1,r=std::min(n-x+1,(x-1)*2-x+1),mid,res=0;
	while(l<=r)
	{
		mid=l+r>>1;
		if(Hash1[mid]==(Hash1[x+mid-1]-Hash1[x-1]*hpos1[mid])
				&&Hash2[mid]==(Hash2[x+mid-1]-Hash2[x-1]*hpos2[mid]))
		{
			res=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
	return res;
}
int main()
{
	hpos1[0]=hpos2[0]=1;
	for(int i=1;i<maxn;i++)
	{
		hpos1[i]=hpos1[i-1]*mod1;
		hpos2[i]=hpos2[i-1]*mod2;
	}
	std::cin>>T;
	while(T--)
	{
		scanf("%s",str+1);
		n=strlen(str+1);
		num[0]=0;
		for(int i=1;i<=n;i++)
		{
			num[i]=0;
			Hash1[i]=Hash1[i-1]*mod1+str[i]-'a'+1;
			Hash2[i]=Hash2[i-1]*mod2+str[i]-'a'+1;
		}
		for(int i=2,t;i<=n;i++)
		{
			t=getlen(i);
			num[i]++;
			num[i+t]--;
		}
		ll res=1,now=1;
		for(int i=1;i<=n;i++)
			(res*=(now+=num[i]))%=mod;
		std::cout<<res<<std::endl;
	}
	return 0;
}

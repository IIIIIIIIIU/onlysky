#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=1e2+5;
const int maxm=2e5+5;
const int mod1=30011;
const int mod2=11261;
const int mod3=19997;
const int mod4=14843;
//const int mod5=10007;
const int mod6=21893;

int n,m,ans[1000005],count[1000005];

ll ans1[maxm],ans2[maxm],ans3[maxm],ans4[maxm],ans5[maxm],ans6[maxm];
ll ai1[maxn],ai2[maxn],ai3[maxn],ai4[maxn],ai5[maxn],ai6[maxn];

char str[10005];

void get(int tag)
{
	scanf("%s",str+1);
	int len=strlen(str+1),s=1,f=1;
	if(str[1]=='-')
	{
		s=2;
		f=-1;
	}
	for(int i=s;i<=len;i++)
	{
		ai1[tag]=(ai1[tag]*10+str[i]-'0')%mod1;
		ai2[tag]=(ai2[tag]*10+str[i]-'0')%mod2;
		ai3[tag]=(ai3[tag]*10+str[i]-'0')%mod3;
		ai4[tag]=(ai4[tag]*10+str[i]-'0')%mod4;
//		ai5[tag]=(ai5[tag]*10+str[i]-'0')%mod5;
		ai6[tag]=(ai6[tag]*10+str[i]-'0')%mod6;
	}
	(ai1[tag]*=f)%=mod1;
	(ai2[tag]*=f)%=mod2;
	(ai3[tag]*=f)%=mod3;
	(ai4[tag]*=f)%=mod4;
//	(ai5[tag]*=f)%=mod5;
	(ai6[tag]*=f)%=mod6;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)
		get(i);
	for(int i=0,lit=std::min(mod1,m+1);i<lit;i++)
	{
		ll base=1;
		for(int v=0;v<=n;v++,base=base*i%mod1)
			ans1[i]=(ans1[i]+ai1[v]*base)%mod1;
	}
	for(int i=0,lit=std::min(mod2,m+1);i<lit;i++)
	{
		ll base=1;
		for(int v=0;v<=n;v++,base=base*i%mod2)
			ans2[i]=(ans2[i]+ai2[v]*base)%mod2;
	}
	for(int i=0,lit=std::min(mod3,m+1);i<lit;i++)
	{
		ll base=1;
		for(int v=0;v<=n;v++,base=base*i%mod3)
			ans3[i]=(ans3[i]+ai3[v]*base)%mod3;
	}
	for(int i=0,lit=std::min(mod4,m+1);i<lit;i++)
	{
		ll base=1;
		for(int v=0;v<=n;v++,base=base*i%mod4)
			ans4[i]=(ans4[i]+ai4[v]*base)%mod4;
	}
	/*
	for(int i=0,lit=std::min(mod5,m+1);i<lit;i++)
	{
		ll base=1;
		for(int v=0;v<=n;v++,base=base*i%mod5)
			ans5[i]=(ans5[i]+ai5[v]*base)%mod5;
	}
	*/
	for(int i=0,lit=std::min(mod6,m+1);i<lit;i++)
	{
		ll base=1;
		for(int v=0;v<=n;v++,base=base*i%mod6)
			ans6[i]=(ans6[i]+ai6[v]*base)%mod6;
	}
	int num=0;
	for(int i=0,v;i<mod1;i++)
		if(!ans1[i])
			for(v=0;v*mod1+i<=m;v++)
				++count[v*mod1+i];
	for(int i=0,v;i<mod2;i++)
		if(!ans2[i])
			for(v=0;v*mod2+i<=m;v++)
				++count[v*mod2+i];
	for(int i=0,v;i<mod3;i++)
		if(!ans3[i])
			for(v=0;v*mod3+i<=m;v++)
				++count[v*mod3+i];
	for(int i=0,v;i<mod4;i++)
		if(!ans4[i])
			for(v=0;v*mod4+i<=m;v++)
				++count[v*mod4+i];
				/*
	for(int i=0,v;i<mod5;i++)
		if(!ans5[i])
			for(v=0;v*mod5+i<=m;v++)
				++count[v*mod5+i];
				*/
	for(int i=0,v;i<mod6;i++)
		if(!ans6[i])
			for(v=0;v*mod6+i<=m;v++)
				++count[v*mod6+i];
	for(int i=1;i<=m;i++)
		if(count[i]==5)
			ans[++num]=i;
	printf("%d\n",num);
	for(int i=1;i<=num;i++)
		printf("%d\n",ans[i]);
	return 0;
}

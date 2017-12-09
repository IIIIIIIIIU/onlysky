#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=1e9;
const int maxlen=55;
const int maxn=2e2+5;

struct Int
{
	int len;
	
	ll ai[maxlen];
	
	Int()
	{
		memset(ai,0,sizeof(ai));
		len=1;
		ai[1]=0;
	}
	
	Int(int x)
	{
		memset(ai,0,sizeof(ai));
		len=1;
		ai[1]=1;
	}
	
	Int(char *S)
	{
		memset(ai,0,sizeof(ai));
		len=0;
		int l=strlen(S+1);
		short i;
		for(i=l;i-9>=0;i-=9)
		{
			ai[++len]=0;
			for(int v=8;v>=0;v--)
				ai[len]=S[i-v]-'0'+ai[len]*10;
		}
		if(i)
			ai[++len]=0;
		for(int v=1;v<=i;v++)
			ai[len]=S[v]-'0'+ai[len]*10;
	}
	
	bool operator<(const Int &tmp)const
	{
		if(len<tmp.len)
			return true;
		if(len>tmp.len)
			return false;
		for(short i=len;i!=0;--i)
			if(ai[i]<tmp.ai[i])
				return true;
			else if(ai[i]>tmp.ai[i])
				return false;
		return false;
	}
	
	bool operator==(const Int &tmp)const
	{
		if(len!=tmp.len)
			return false;
		for(short i=len;i!=0;--i)
			if(ai[i]!=tmp.ai[i])
				return false;
		return true;
	}
	
	bool operator==(const int &tmp)const
	{
		return len==1&&ai[len]==tmp;
	}
	
	Int operator+(const Int &tmp)const
	{
		Int res;
		res.len=std::max(len,tmp.len);
		ll cur=0;
		for(int i=1;i<=res.len;i++)
		{
			cur+=ai[i]+tmp.ai[i];
			res.ai[i]=cur%mod;
			cur/=mod;
		}
		while(cur)
		{
			res.ai[++res.len]=cur%mod;
			cur/=mod;
		}
		return res;
	}
	
	Int operator+(const int &tmp)const
	{
		Int res;
		res.len=len;
		ll cur=tmp;
		for(int i=1;i<=res.len;i++)
		{
			cur+=ai[i];
			res.ai[i]=cur%mod;
			cur/=mod;
		}
		while(cur)
		{
			res.ai[++res.len]=cur%mod;
			cur/=mod;
		}
		return res;
	}
	
	Int bin()
	{
		Int res;
		ll tmp=0;
		for(int i=len;i>=1;i--)
		{
			tmp+=ai[i];
			res.ai[i]=tmp/2;
			tmp%=2;
			tmp*=mod;
		}
		res.len=len;
		while(!res.ai[res.len])
			res.len--;
		if(res.len==0)
			res.len=1;
		return res;
	}
	
	bool has()
	{
		return ai[1]&1;
	}
	
	void out()
	{
		printf("%lld",ai[len]);
		for(int i=len-1;i!=0;i--)
			printf("%09lld",ai[i]);
		putchar('\n');
	}
};

int T;

std::map<Int,Int>Map;

Int dfs(Int now)
{
//	now.out();
	if(now==0)
		return Int(0);
	if(now==1)
		return Int(1);
	if(Map[now]==0)
	{
		if(now.has())
			Map[now]=dfs(now.bin()+1)+dfs(now.bin());
		else
			Map[now]=dfs(now.bin());
	}
	return Map[now];
}

int main()
{
//	freopen("data.txt","r",stdin);
//	freopen("sequencezj.in","r",stdin);
//	freopen("sequencezj.out","w",stdout); 
	std::cin>>T;
	while(T--)
	{
		char str[1000];
		scanf("%s",str+1);
		Int n=Int(str);
//		n.out();
		if(!T)
		{
			int kwedq=0;
		}
		dfs(n).out();
	}
	return 0;
}

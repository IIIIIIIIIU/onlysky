#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=1500;
const int mod=1e9+7;
int n,m,ch[maxn][10],tot=1,root=1,fail[maxn];
int que[maxn],num[maxn];
ll dp[maxn][maxn][2];
char N[maxn],S[maxn];
bool val[maxn],vis[maxn][maxn][2];
inline void add(ll &x,ll y)
{
	if((x+=y)>=mod)
		x-=mod;
}
ll dfs(int now,int pos,bool lit)
{
	if(now==n)
		return !val[pos];
	if(vis[now][pos][lit])
		return dp[now][pos][lit];
	vis[now][pos][lit]=true;
	ll &res=dp[now][pos][lit];
	res=0;
	if(lit)
	{
		if(!val[ch[pos][num[now+1]]])
			add(res,dfs(now+1,ch[pos][num[now+1]],true));
		for(int i=0;i<num[now+1];i++)
			if(!val[ch[pos][i]])
				add(res,dfs(now+1,ch[pos][i],false));
	}
	else
	{
		for(int i=0;i<=9;i++)
			if(!val[ch[pos][i]])
				add(res,dfs(now+1,ch[pos][i],false));
	}
	return res;
}
int main()
{
	std::cin>>N+1;
	n=strlen(N+1);
	std::cin>>m;
	for(int i=1,len;i<=m;i++)
	{
		std::cin>>S+1;
		len=strlen(S+1);
		int now=root;
		for(int v=1;v<=len;v++)
		{
			if(!ch[now][S[v]-'0'])
				ch[now][S[v]-'0']=++tot;
			now=ch[now][S[v]-'0'];
		}
		val[now]=true;
	}
	int h=0,tail=1;
	que[h]=1;
	while(h<tail)
	{
		int now=que[h++];
		if(now==root)
		{
			for(int i=0;i<=9;i++)
				if(ch[now][i])
				{
					fail[ch[now][i]]=root;
					que[tail++]=ch[now][i];
				}
		}
		else
		{
			for(int i=0;i<=9;i++)
				if(ch[now][i])
				{
					int temp=fail[now];
					while(temp&&!ch[temp][i])
						temp=fail[temp];
					if(!temp)
						fail[ch[now][i]]=root;
					else
						fail[ch[now][i]]=ch[temp][i];
					val[ch[now][i]]|=val[fail[ch[now][i]]];
					que[tail++]=ch[now][i];
				}
		}
	}
	for(int i=0;i<=9;i++)
		if(!ch[1][i])
			ch[1][i]=root;
	for(int i=2;i<=tot;i++)
		for(int v=0;v<=9;v++)
			if(!ch[i][v])
			{
				int temp=fail[i];
				while(temp&&!ch[temp][v])
					temp=fail[temp];
				if(!temp)
					ch[i][v]=root;
				else
					ch[i][v]=ch[temp][v];
			}
	for(int i=1;i<=n;i++)
		num[i]=N[i]-'0';
	ll ans=0;
	if(!val[ch[root][num[1]]])
		add(ans,dfs(1,ch[root][num[1]],true));
	for(int i=1;i<num[1];i++)
		if(!val[ch[root][i]])
			add(ans,dfs(1,ch[root][i],false));
	for(int i=2;i<=n;i++)
		for(int v=1;v<=9;v++)
			if(!val[ch[root][v]])
				add(ans,dfs(i,ch[root][v],false));
	std::cout<<ans;
	return 0;
}

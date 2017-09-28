#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=505;

int n,Tlen,len,ans,vis[maxn<<1|1][maxn];

char T[maxn<<1|1],str[maxn];

bool dp[maxn<<1|1][maxn];

bool dfs(int pa,int pb)
{
	if(pa==Tlen&&pb==len) return true;
	if(pa>Tlen||pb>len) return false;
	if(vis[pa][pb]!=-1) return dp[pa][pb];
	if(T[pa]==str[pb]) dp[pa][pb]=dfs(pa+1,pb+1);
	else if(T[pa]=='?') dp[pa][pb]=dfs(pa+1,pb+1);
	else if(T[pa]=='*') dp[pa][pb]=dfs(pa,pb+1)||dfs(pa+1,pb);
	else dp[pa][pb]=0;
	vis[pa][pb]=1;
	return dp[pa][pb];
}

int main()
{
	freopen("data.txt","r",stdin);
	std::cin>>T;Tlen=strlen(T);
	std::cin>>n;
	for(int i=1;i<=n;i++)
	{
		memset(dp,0,sizeof(dp));
		memset(vis,-1,sizeof(vis));
		std::cin>>str;
		len=strlen(str);
		ans+=!dfs(0,0);
	}
	std::cout<<ans;
	return 0;
}

#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mod=1e9+7;
const int maxn=4e5+5;
const int ai[4]={2,3,5,7};
struct node
{
	int x,y;
	ll val;
	node(){}
	node(int x_,int y_,ll val_)
	{
		x=x_;
		y=y_;
		val=val_;
	}
	bool operator<(const node &tmp)const
	{
		return val<tmp.val;
	}
};
int num,next[40005][12],out[20],len;
ll n,k,bi[maxn],ans[maxn],dp[15][12][40005][2];
std::priority_queue<node>que;
void dfs(ll s,int x)
{
	if(s>n)
		return;
	bi[++num]=s;
	if(x<3)
		dfs(s,x+1);
	dfs(s*ai[x],x);
}
int main()
{
	freopen("data.txt","r",stdin);
	std::cin>>n>>k;
	dfs(1,0);
	bi[++num]=0;
	bi[++num]=1;
	std::sort(bi+1,bi+num+1);
	num=std::unique(bi+1,bi+num+1)-bi-1;
	memset(next,-1,sizeof(next));
	ll tmp=n;
	while(tmp)
	{
		out[++len]=tmp%10;
		tmp/=10;
	}
	for(int i=1;i<=num;i++)
	{
		for(int e=0;e<10;e++)
		{
			tmp=bi[i]*e;
			if(tmp>n)
				break;
			next[i][e]=std::lower_bound(bi+1,bi+num+1,tmp)-bi;
		}
	}
	dp[0][1][2][0]=1;
	out[0]=10;
	for(int i=0;i<len;i++)
	{
		for(int v=0;v<=9;v++)
			for(int e=1;e<=num;e++)
			{
				if(dp[i][v][e][0])
				{
					for(int o=0;o<=9;o++)
						if(next[e][o]!=-1)
							dp[i+1][o][next[e][o]][0]+=dp[i][v][e][0];
					if(v<out[i])
						if(next[e][out[i+1]]!=-1)
							dp[i+1][out[i+1]][next[e][out[i+1]]][1]+=dp[i][v][e][0];
				}
				if(v==out[i]&&dp[i][v][e][1]&&next[e][out[i+1]]!=-1)
					dp[i+1][out[i+1]][next[e][out[i+1]]][1]+=dp[i][out[i]][e][1];
				if(v&&i)
					ans[e]+=dp[i][v][e][0];
			}
	}
	for(int i=1;i<out[len];i++)
		for(int e=1;e<=num;e++)
			ans[e]+=dp[len][i][e][0];
	for(int e=1;e<=num;e++)
		ans[e]+=dp[len][out[len]][e][1];
	std::sort(ans+2,ans+num+1);
	que.push(node(num,num,ans[num]*ans[num]));
	int cnt=0;
	ll out_ans=0;
	node now;
	ans[1]=0;
	while(!que.empty())
	{
		cnt++;
		now=que.top();
		if(!now.val)
			break;
		que.pop();
		(out_ans+=now.val)%=mod;
		if(cnt==k)
			break;
		if(now.x!=now.y)
		{
			(out_ans+=now.val)%=mod;
			++cnt;
			if(cnt==k)
				break;
			que.push(node(now.x-1,now.y,ans[now.x-1]*ans[now.y]));
		}
		if(now.x==num&&now.y>1)
			que.push(node(now.x,now.y-1,ans[now.x]*ans[now.y-1]));
	}
	std::cout<<out_ans<<std::endl;
	return 0;
}

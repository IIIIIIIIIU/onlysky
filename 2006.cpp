#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=500005,maxtree=maxn*20;

struct NodeType
{
	int s,k;

	ll val;

	NodeType(int s_=0,int k_=0,ll val_=0)
	{
		s=s_,k=k_,val=val_;
	}

	bool operator<(const NodeType &tmp)const
	{
		return val<tmp.val;
	}
};

int n,k,L,R,tot,size,ch[maxtree][2],val[maxtree],root[maxn];

ll ans,sum[maxn],bi[maxn];

std::priority_queue<NodeType>que;

inline void read(int &now)
{
	char Cget;now=0;int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
	now*=if_z;
}

inline void read(ll &now)
{
	char Cget;now=0;int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
	now*=if_z;
}

void add(int &now,int pre,int l,int r,int to)
{
	now=++tot,val[now]=val[pre]+1;
	if(l==r) return;
	int mid=l+r>>1;
	if(to<=mid) add(ch[now][0],ch[pre][0],l,mid,to),ch[now][1]=ch[pre][1];
	if(to>mid) add(ch[now][1],ch[pre][1],mid+1,r,to),ch[now][0]=ch[pre][0];
}

int query(int now,int pre,int l,int r,int k)
{
	if(l==r) return l;
	int mid=l+r>>1,dis=val[ch[now][0]]-val[ch[pre][0]];
	if(dis>=k) return query(ch[now][0],ch[pre][0],l,mid,k);
	else return query(ch[now][1],ch[pre][1],mid+1,r,k-dis);
}

int main()
{
//	freopen("piano.in","r",stdin);
//	freopen("piano.out","w",stdout);
	read(n),read(k),read(L),read(R);
	for(int i=1;i<=n;i++)
		read(sum[i]),sum[i]+=sum[i-1],bi[i]=sum[i];
	std::sort(bi+1,bi+n+1);
	size=std::unique(bi+1,bi+n+1)-bi-1;
	for(int i=1;i<=n;i++)
		sum[i]=std::lower_bound(bi+1,bi+size+1,sum[i])-bi;
	for(int i=1;i<=n;i++)
		add(root[i],root[i-1],1,size,sum[i]);
	for(int i=1;i<=n;i++)
	{
		int l=i+L-1,r=std::min(n,i+R-1);
		if(l>n) break;
		int tmp=query(root[r],root[l-1],1,size,r-l+1);
		que.push(NodeType(i,r-l+1,bi[tmp]-bi[sum[i-1]]));
	}
	while(k--)
	{
		NodeType now=que.top();
		que.pop();
		ans+=now.val;
		if(now.k>1)
		{
			now.k--;
			int l=now.s+L-1,r=std::min(n,now.s+R-1);
			now.val=bi[query(root[r],root[l-1],1,size,now.k)]-bi[sum[now.s-1]];
			que.push(now);
		}
	}
	std::cout<<ans;
	return 0;
}

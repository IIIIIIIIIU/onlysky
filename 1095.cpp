#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int M=100100;
struct Priority_Queue
{
	std::priority_queue<int>heap,delmark;
	void Insert(int x)
	{
		heap.push(x);
	}
	void Erase(int x)
	{
		delmark.push(x);
	}
	void Pop()
	{
		while(delmark.size()&&heap.top()==delmark.top())
		{
			heap.pop();
			delmark.pop();
		}
		heap.pop();
	}
	int Top()
	{
		while(delmark.size()&&heap.top()==delmark.top())
		{
			heap.pop();
			delmark.pop();
		}
		return heap.top();
	}
	int Second_Top()
	{
		int tmp=Top();
		Pop();
		int re=Top();
		Insert(tmp);
		return re;
	}
	int Size()
	{
		return heap.size()-delmark.size();
	}
};
struct Priority_Queue s1[M],s2[M],ans;
struct abcd
{
	int to,next;
	bool ban;
};
struct abcd table[M<<1];
int head[M],tot=1,n,m,cnt,fa[M],log_2[M<<1],dpt[M],a[M<<1][20],T,pos[M];
bool status[M];
void Add(int x,int y)
{
	table[++tot].to=y;
	table[tot].next=head[x];
	head[x]=tot;
}
int Get_Size(int x,int from)
{
	int i,re=1;
	for(i=head[x];i;i=table[i].next)
	{
		if(table[i].ban||table[i].to==from)
			continue;
		re+=Get_Size(table[i].to,x);
	}
	return re;
}
int Get_Centre_Of_Gravity(int x,int from,int size,int &cg)
{
	int i,re=1,flag=true;
	for(i=head[x];i;i=table[i].next)
	{
		if(table[i].ban||table[i].to==from)
			continue;
		int temp=Get_Centre_Of_Gravity(table[i].to,x,size,cg);
		if(temp<<1>size)
			flag=false;
		re+=temp;
	}
	if(size-re<<1>size)
		flag=false;
	if(flag)
		cg=x;
	return re;
}
void DFS(int x,int from,int dpt,Priority_Queue &s)
{
	int i;
	s.Insert(dpt);
	for(i=head[x];i;i=table[i].next)
	{
		if(table[i].ban||table[i].to==from)
			continue;
		DFS(table[i].to,x,dpt+1,s);
	}
}
void Insert(Priority_Queue &s)
{
	if(s.Size()>=2)
	{
		int temp=s.Top()+s.Second_Top();
		ans.Insert(temp);
	}
}
void Erase(Priority_Queue &s)
{
	if(s.Size()>=2)
	{
		int temp=s.Top()+s.Second_Top();
		ans.Erase(temp);
	}
}
int Tree_Divide_And_Conquer(int x)
{
	int i,size,cg;
	size=Get_Size(x,0);
	Get_Centre_Of_Gravity(x,0,size,cg);
	s2[cg].Insert(0);
	for(i=head[cg];i;i=table[i].next)
		if(!table[i].ban)
		{
			table[i].ban=table[i^1].ban=true;
			Priority_Queue s;
			DFS(table[i].to,0,1,s);
			int temp=Tree_Divide_And_Conquer(table[i].to);
			fa[temp]=cg;
			s1[temp]=s;
			s2[cg].Insert(s1[temp].Top());
		}
	Insert(s2[cg]);
	return cg;
}
void DFS(int x,int from)
{
	int i;
	a[pos[x]=++T][0]=dpt[x]=dpt[from]+1;
	for(i=head[x];i;i=table[i].next)
		if(table[i].to!=from)
		{
			DFS(table[i].to,x);
			a[++T][0]=dpt[x];
		}
}
int LCA_Depth(int x,int y)
{
	x=pos[x];
	y=pos[y];
	if(x>y)
		std::swap(x,y);
	int L=log_2[y-x+1];
	return std::min(a[x][L],a[y-(1<<L)+1][L]);
}
int Distance(int x,int y)
{
	return dpt[x]+dpt[y]-2*LCA_Depth(x,y);
}
void Turn_On(int x)
{
	int i;
	Erase(s2[x]);
	s2[x].Insert(0);
	Insert(s2[x]);
	for(i=x;fa[i];i=fa[i])
	{
		Erase(s2[fa[i]]);
		if(s1[i].Size())
			s2[fa[i]].Erase(s1[i].Top());
		s1[i].Insert(Distance(fa[i],x));
		if(s1[i].Size())
			s2[fa[i]].Insert(s1[i].Top());
		Insert(s2[fa[i]]);
	}
}
void Turn_Off(int x)
{
	int i;
	Erase(s2[x]);
	s2[x].Erase(0);
	Insert(s2[x]);
	for(i=x;fa[i];i=fa[i])
	{
		Erase(s2[fa[i]]);
		if(s1[i].Size())
			s2[fa[i]].Erase(s1[i].Top());
		s1[i].Erase(Distance(fa[i],x));
		if(s1[i].Size())
			s2[fa[i]].Insert(s1[i].Top());
		Insert(s2[fa[i]]);
	}
}
int main()
{
	int i,v,x,y;
	char p[10];
	std::cin>>n;
	cnt=n;
	for(i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		Add(x,y);
		Add(y,x);
	}
	Tree_Divide_And_Conquer(1);
	DFS(1,0);
	for(i=2;i<=T;i++)
		log_2[i]=log_2[i>>1]+1;
	for(v=1;v<=log_2[T];v++)
		for(i=1;i+(1<<v)-1<=T;i++)
			a[i][v]=std::min(a[i][v-1],a[i+(1<<v-1)][v-1]);
	for(i=1;i<=n;i++)
		status[i]=true;
	std::cin>>m;
	for(i=1;i<=m;i++)
	{
		scanf("%s",p);
		if(p[0]=='G')
		{
			if(cnt<=1)
				printf("%d\n",cnt-1);
			else
				printf("%d\n",ans.Top());
		}
		else
		{
			scanf("%d",&x);
			if(status[x]==true)
			{
				--cnt;
				status[x]=false;
				Turn_Off(x);
			}
			else
			{
				++cnt;
				status[x]=true;
				Turn_On(x);
			}
		}
	}
	return 0;
}

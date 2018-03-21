#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

#define begin {
#define end }

const ll maxn=5e5+5;
const ll INF=1e18;

struct point
begin
	ll x,y,p;
end;

struct point pi[maxn];

struct matrix
begin
	ll x1,y1,x2,y2;
end;

struct matrix mi[maxn];

ll n,m,bx[maxn],by[maxn],numx,numy;
ll headS[maxn],ES[maxn],VS[maxn],cntS;
ll headT[maxn],ET[maxn],VT[maxn],cntT;
ll headP[maxn],EP[maxn],VP[maxn],cntP;

ll tree[maxn],ans[maxn];

inline void read(ll &now)
begin
	char Cget;
	now=0;
	ll if_z=1;
	while(!isdigit(Cget=getchar()))
		if(Cget=='-')
			if_z=-1;
	while(isdigit(Cget))
	begin
		now=now*10+Cget-'0';
		Cget=getchar();
	end
	now*=if_z;
end

inline void edge_add_S(ll u,ll v)
begin
	ES[++cntS]=headS[u];
	VS[cntS]=v;
	headS[u]=cntS;
end

inline void edge_add_T(ll u,ll v)
begin
	ET[++cntT]=headT[u];
	VT[cntS]=v;
	headT[u]=cntT;
end

inline void edge_add_P(ll u,ll v)
begin
	EP[++cntP]=headP[u];
	VP[cntP]=v;
	headP[u]=cntP;
end

inline void add(ll pos,ll x)
begin
	while(pos<=numx)
	{
		tree[pos]+=x;
		pos+=(pos&(-pos));
	}
end

inline ll query(ll pos)
begin
	ll res=0;
	while(pos>0)
	begin
		res+=tree[pos];
		pos-=(pos&(-pos));
	end
	return res;
end

inline ll query(ll l,ll r)
begin
	if(l>r)
		return 0; 
	return query(r)-query(l-1);
end

int main()
begin
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	read(m);
	bx[numx=1]=-INF;
	bx[numx=2]=INF;
	by[numy=1]=-INF;
	by[numy=2]=INF;
	for(ll i=1;i<=n;i++)
	begin
		read(pi[i].x);
		read(pi[i].y);
		read(pi[i].p);
		bx[++numx]=pi[i].x;
		by[++numy]=pi[i].y;
	end
	std::sort(bx+1,bx+numx+1);
	std::sort(by+1,by+numy+1);
	numx=std::unique(bx+1,bx+numx+1)-bx-1;
	numy=std::unique(by+1,by+numy+1)-by-1;
	for(ll i=1;i<=n;i++)
	begin
		pi[i].x=std::lower_bound(bx+1,bx+numx+1,pi[i].x)-bx;
		pi[i].y=std::lower_bound(by+1,by+numy+1,pi[i].y)-by;
		edge_add_P(pi[i].y,i);
	end
	for(ll i=1;i<=m;i++)
	begin
		read(mi[i].x1);
		read(mi[i].y1);
		read(mi[i].x2);
		read(mi[i].y2);
		if(mi[i].x1>mi[i].x2)
			std::swap(mi[i].x1,mi[i].x2);
		if(mi[i].y1>mi[i].y2)
			std::swap(mi[i].y1,mi[i].y2);
		mi[i].x1=std::lower_bound(bx+1,bx+numx+1,mi[i].x1)-bx;
		mi[i].x2=std::upper_bound(bx+1,bx+numx+1,mi[i].x2)-bx-1;
		mi[i].y1=std::lower_bound(by+1,by+numy+1,mi[i].y1)-by;
		mi[i].y2=std::upper_bound(by+1,by+numy+1,mi[i].y2)-by-1;
		if(mi[i].y1<=mi[i].y2)
		begin
			edge_add_S(mi[i].y1,i);
			edge_add_T(mi[i].y2,i);
		end
	end
	for(ll i=1;i<=numy;i++)
	begin
		for(ll v=headS[i];v!=0;v=ES[v])
			ans[VS[v]]=query(mi[VS[v]].x1,mi[VS[v]].x2);
		for(ll v=headP[i];v!=0;v=EP[v])
			add(pi[VP[v]].x,pi[VP[v]].p);
		for(ll v=headT[i];v!=0;v=ET[v])
			ans[VT[v]]=query(mi[VT[v]].x1,mi[VT[v]].x2)-ans[VT[v]];
	end
	for(ll i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
end

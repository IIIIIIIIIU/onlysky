#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mn=2e5+5,mnt=mn<<2|1;
inline ll max(const ll &a,const ll &b){
	return a>b?a:b;
}
struct Q_{
	std::priority_queue<ll>q1,q2;
	inline ll o(){
		while(!q2.empty()&&q1.top()==q2.top()){
			q1.pop();
			q2.pop();
		}
		if(q1.empty())
			return 0;
		return q1.top();
	}
	inline void i(const ll &x){
		q1.push(x);
	}
	inline void d(const ll &x){
		q2.push(x);
	}
}ci[mn];
struct P{
	ll s,l,r,m;
	P(){
		s=l=r=m=0;
	}
	inline P operator+(const P &t)const{
		P rs;
		rs.s=s+t.s;
		rs.l=max(l,s+t.l);
		rs.r=max(r+t.s,t.r);
		rs.m=max(m,t.m);
		rs.m=max(rs.m,r+t.l);
		rs.m=max(rs.m,max(rs.l,rs.r));
		return rs;
	}
}vi[mnt],o;
int n,q,L[mnt],R[mnt],md[mnt],hd[mn],E[mn<<1],V[mn<<1],cnt;
int dep[mn],top[mn],id[mn],li[mn],ri[mn],wi[mn],bk[mn];
int f[mn],sz[mn],lar[mn];
ll bs[mn],ti[mn];
bool tag;
inline void in(int &x){
	char c;
	x=0;
	int i=1;
	while(!isdigit(c=getchar()))
		if(c=='-')
			i=-1;
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	x=x*i;
}
void D1(int x,int fa){
	f[x]=fa;
	sz[x]=1;
	dep[x]=dep[fa]+1;
	for(int i=hd[x];i!=0;i=E[i])
		if(V[i]!=fa){
			D1(V[i],x);
			sz[x]+=sz[V[i]];
			if(sz[V[i]]>=sz[lar[x]])
				lar[x]=V[i];
		}
}
void D2(int x,int c){
	top[x]=c;
	id[x]=++cnt;
	bk[cnt]=x;
	if(!li[c])
		li[c]=cnt;
	ri[c]=cnt;
	if(lar[x])
		D2(lar[x],c);
	for(int i=hd[x];i!=0;i=E[i])
		if(V[i]!=lar[x]&&V[i]!=f[x])
			D2(V[i],V[i]);
}
void B(int x,int l,int r){
	L[x]=l;
	R[x]=r;
	if(l==r){
		bs[l]=wi[bk[l]];
		vi[x].s=bs[l];
		vi[x].l=vi[x].r=vi[x].m=max(bs[l],0LL);
		return;
	}
	md[x]=l+r>>1;
	B(x<<1,l,md[x]);
	B(x<<1|1,md[x]+1,r);
	vi[x]=vi[x<<1]+vi[x<<1|1];
}
void Q(int x,int l,int r){
	if(L[x]>=l&&R[x]<=r){
		if(tag){
			tag=false;
			o=vi[x];
		}
		else
			o=o+vi[x];
		return;
	}
	if(l<=md[x])
		Q(x<<1,l,r);
	if(r>md[x])
		Q(x<<1|1,l,r);
}
void Q(int x){
	tag=true;
	Q(1,id[x],ri[top[x]]);
}
void C(int x,int p){
	if(L[x]==R[x]){
		if(tag){
			if(o.l>0)
				ti[p]+=o.l;
			ci[p].i(o.m);
		}
		else{
			if(o.l>0)
				ti[p]-=o.l;
			ci[p].d(o.m);
		}
		vi[x].s=bs[p]+ti[p];
		vi[x].l=vi[x].r=vi[x].s;
		vi[x].m=max(vi[x].s,ci[p].o());
		return;
	}
	if(p<=md[x])
		C(x<<1,p);
	else
		C(x<<1|1,p);
	vi[x]=vi[x<<1]+vi[x<<1|1];
}
void C(int x,int p,ll y){
	if(L[x]==R[x]){
		bs[p]=y;
		vi[x].s=bs[p]+ti[p];
		vi[x].l=vi[x].r=vi[x].s;
		vi[x].m=max(vi[x].s,ci[p].o());
		return;
	}
	if(p<=md[x])
		C(x<<1,p,y);
	if(p>md[x])
		C(x<<1|1,p,y);
	vi[x]=vi[x<<1]+vi[x<<1|1];
}
void D(int x){
	for(int i=hd[x];i!=0;i=E[i])
		if(V[i]!=f[x]){
			D(V[i]);
			if(V[i]!=lar[x]){
				Q(V[i]);
				tag=true;
				C(1,id[x]);
			}
		}
}
void cl(int x){
	if(top[x]==1)
		return;
	cl(f[top[x]]);
	Q(top[x]);
	tag=false;
	C(1,id[f[top[x]]]);
}
void sl(int x){
	if(top[x]==1)
		return;
	Q(top[x]);
	tag=true;
	C(1,id[f[top[x]]]);
	sl(f[top[x]]);
}
int main(){
	freopen("data.txt","r",stdin);
	in(n);
	in(q);
	for(int i=1;i<=n;i++)
		in(wi[i]);
	for(int i=1,u,v;i<n;i++){
		in(u);
		in(v);
		E[++cnt]=hd[u];
		V[cnt]=v;
		hd[u]=cnt;
		E[++cnt]=hd[v];
		V[cnt]=u;
		hd[v]=cnt;
	}
	cnt=0;
	D1(1,0);
	D2(1,1);
	B(1,1,n);
	D(1);
	char op[3];
	for(int i=1,x,y;i<=q;i++){
		scanf("%s",op);
		in(x);
		if(op[0]=='M'){
			in(y);
			cl(x);
			C(1,id[x],y);
			sl(x);
		}
		else{
			Q(x);
			printf("%lld\n",o.m);
		}
	}
	return 0;
}

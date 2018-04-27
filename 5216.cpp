#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int mn=1e5+5,mnt=mn<<2|1;
int n;
struct P{
	short f[105],N,U[105],V[105];
	int C[105];
	P(){
		N=0;
		memset(f,0,sizeof(f));
		memset(U,0,sizeof(U));
		memset(V,0,sizeof(V));
		memset(C,0,sizeof(C));
	}
	inline short find(short x){
		if(f[x]==x)
			return x;
		return f[x]=find(f[x]);
	}
	inline P operator+(const P&t)const{
		P rs;
		for(short i=1;i<=n;i++)
			rs.f[i]=i;
		short l=0,r=0,x,y;
		while(l<N&&r<t.N)
			if(C[l]<=t.C[r]){
				x=rs.find(U[l]);
				y=rs.find(V[l]);
				if(x!=y){
					rs.f[x]=y;
					rs.U[rs.N]=U[l];
					rs.V[rs.N]=V[l];
					rs.C[rs.N]=C[l];
					rs.N++;
				}
				l++;
			}
			else{
				x=rs.find(t.U[r]);
				y=rs.find(t.V[r]);
				if(x!=y){
					rs.f[x]=y;
					rs.U[rs.N]=t.U[r];
					rs.V[rs.N]=t.V[r];
					rs.C[rs.N]=t.C[r];
					rs.N++;
				}
				r++;
			}
		while(l<N){
			x=rs.find(U[l]);
			y=rs.find(V[l]);
			if(x!=y){
				rs.f[x]=y;
				rs.U[rs.N]=U[l];
				rs.V[rs.N]=V[l];
				rs.C[rs.N]=C[l];
				rs.N++;
			}
			l++;
		}
		while(r<t.N){
			x=rs.find(t.U[r]);
			y=rs.find(t.V[r]);
			if(x!=y){
				rs.f[x]=y;
				rs.U[rs.N]=t.U[r];
				rs.V[rs.N]=t.V[r];
				rs.C[rs.N]=t.C[r];
				rs.N++;
			}
			r++;
		}
		return rs;
	}
}vi[mnt],o;
int m,q,L[mnt],R[mnt],md[mnt],tag;
void B(int x,int l,int r){
	L[x]=l;
	R[x]=r;
	if(l==r){
		for(short i=1;i<=n;i++)
			vi[x].f[i]=i;
		vi[x].N=1;
		scanf("%hd%hd%d",&vi[x].U[0],&vi[x].V[0],&vi[x].C[0]);
		vi[x].f[vi[x].U[0]]=vi[x].V[0];
		return;
	}
	md[x]=l+r>>1;
	B(x<<1,l,md[x]);
	B(x<<1|1,md[x]+1,r);
	vi[x]=vi[x<<1]+vi[x<<1|1];
}
void query(int x,int l,int r){
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
		query(x<<1,l,r);
	if(r>md[x])
		query(x<<1|1,l,r);
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	B(1,1,m);
	int l,r,t;
	while(q--){
		scanf("%d%d",&l,&r);
		tag=true;
		query(1,l,r);
		t=0;
		for(int i=0;i<o.N;i++)
			t+=o.C[i];
		printf("%d\n",t);
	}
	return 0;
}

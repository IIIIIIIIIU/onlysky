#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mn=1e7+5,M=1e9+7;
int n,m,k,wi[305];
ll fac[mn],inv[mn],f[100005],g[100005];
inline void A(int &x,ll y){
    if((x+=y)>=M)
        x-=M;
}
inline void A(ll &x,ll y){
    if((x+=y)>=M)
        x-=M;
}
inline ll C(int x,int y){
    if(x<y)
        return 0;
    return fac[x]*inv[y]%M*inv[x-y]%M;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    int lit=0;
    for(int i=1;i<=m;i++){
        scanf("%d",&wi[i]);
        lit+=wi[i];
    }
    if(lit>k)
        lit=k;
    g[0]=1;
    for(int i=1;i<=m;i++){
        for(int v=1;v<=lit;v++)
            A(g[v],g[v-1]);
        for(int v=0;v<=lit;v++){
            f[v]=g[v];
            if(v>wi[i])
                A(f[v],M-g[v-wi[i]-1]);
        }
        for(int v=0;v<=lit;v++)
            g[v]=f[v];
    }
    fac[0]=fac[1]=inv[0]=inv[1]=1;
    for(int i=2;i<=k+n;i++){
        fac[i]=fac[i-1]*i%M;
        inv[i]=(-M)/i*inv[M%i]%M;
        A(inv[i],M);
    }
    for(int i=2;i<=n+k;i++)
        inv[i]=inv[i-1]*inv[i]%M;
    int o=0;
    if(n>m)
        for(int i=0;i<=lit;i++)
            A(o,g[i]*C(k-i+n-m-1,n-m-1)%M);
    else if(k<=lit)
        o=g[k];
    else
        o=0;
    printf("%d\n",o);
    return 0;
}

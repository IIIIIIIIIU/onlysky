#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mn=1e7+5;
int pi[mn],num,n;
ll phi[mn];
bool vis[mn];
std::map<ll,ll>Map;
void pre(){
	phi[1]=1;
	for(int i=2;i<=1e7;i++){
		if(!vis[i]){
			phi[i]=i-1;
			pi[++num]=i;
		}
		for(int v=1;v<=num&&pi[v]*i<=1e7;v++){
			vis[pi[v]*i]=true;
			if(i%pi[v]==0){
				phi[i*pi[v]]=phi[i]*pi[v];
				break;
			}
			phi[i*pi[v]]=phi[i]*phi[pi[v]];
		}
	}
	for(int i=2;i<=1e7;i++)
		phi[i]+=phi[i-1];
}
ll S(int x){
	if(x<=1e7)
		return phi[x];
	if(Map[x])
		return Map[x];
	ll r=0;
	for(int i=2,t;i<=x;i=t+1){
		t=x/(x/i);
		r+=(t-i+1)*S(x/i);
	}
	return Map[x]=1LL*x*(x+1)/2-r;
}
int main(){
	pre();
	std::cin>>n;
	std::cout<<S(n)<<std::endl;
	return 0;
}

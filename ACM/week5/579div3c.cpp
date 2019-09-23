#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n;
    ll mx=0,zz,ans=0;
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%lld",&zz); 
        mx = __gcd(mx,zz);
	if(mx == 1){
	    break;
	}
    }
    for(int i = 1;i*i <= mx;i++){
        if(mx%i==0){
            ans++;
		if(mx/i!=i){
			ans++;
		}
        }
    }
    printf("%lld\n",ans);
    return 0;
}


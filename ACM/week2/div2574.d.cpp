#include<bits/stdc++.h>
using namespace std;
long long a1[10000+10];
const long long  mod=998244353;
 
long long ans;
 
long long  calc(ll x){
    ll res=0;
    ll base=1;
    while(x){
        ll r=x%10ll;
        res=(res+base*11ll%mod*r%mod)%mod;
        x/=10;
        base=(base*100ll)%mod;
    }
    return res%mod;
}
 
int main() {
    int n;
    while(~scanf("%d", &n)) {
        for(int i=1;i<=n;++i){
            scanf("%lld",&a[i]);
        }
        ans=0;
        for(int i=1;i<=n;i++){
            ans=(ans+calc(a[i]))%mod;
        }
        printf("%lld\n",ans*n%mod);
    }
}

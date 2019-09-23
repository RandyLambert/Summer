#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll a,ll b){
    if(a%b == 0) return b;
    else return gcd(b,a%b);
}

ll x,y,c,d;
int judge(ll mid){
    unsigned long long c1 = c*mid;
    unsigned long long d1 = d*mid;

    if(d1 >= y){
        if((d1 - y) + x >= c1 && x <= c1){
           return 1;
        }
    }
    return 0;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>x>>y>>c>>d;
        if(c==d){
            if(x==y){
                cout<<"0"<<"\n";
                continue;
            }
            else{
                cout<<"-1"<<"\n";
                continue;
            }
        }
        else if(c == 0){
            if(x == 0){
                cout<<"0"<<"\n";
                continue;
            }
            else{
                cout<<"-1"<<"\n";
                continue;
            }
        }
        int gai = gcd(c,d);
        c = c/gai; d = d/gai;
        ll l = 0,r = 1000000000,ans = 0,mid;
        while(l<=r){
            mid = (l+r)>>1;
            if(judge(mid)){
                r = mid - 1;
                ans = mid;
            }
            else{
                l = mid + 1;
            }
        }
            cout<<ans*d - y<<"\n";
    }
    return 0;
}


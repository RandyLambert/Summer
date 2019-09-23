#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull t,q = 1,flag = 0,ans;

int judge(ull mid){
    ull cnt = 0,xx = 5;
    while(xx <= mid){
        cnt += mid/xx;
        xx=xx*5;
    }
    /* printf("%lld\n",cnt); */

    if(cnt >= q)
    {
        if(cnt > q)
            flag = 1;
        else if(cnt == q)
            flag = 2;
        return 1;
    }
    else 
        return 0;
}
int main(){

    scanf("%lld",&t);
    for(ull i = 1;i<=t;i++){
        ull l = 5,r = 100000000000;
        ans = 0;
        scanf("%lld",&q);

        while(l <= r){
            ull mid = (l+r)>>1;
            if(judge(mid)){
                ans = mid;
                r = mid - 1;
            }
            else{
                l = mid + 1;
            }
        }
        if(flag == 2)
            printf("Case %lld: %lld\n",i,ans);
        else
            printf("Case %lld: impossible\n",i);
    }
    return 0;
}

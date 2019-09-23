#include <bits/stdc++.h>
using namespace std;
long long int ans,n,k;
inline long long int judge(long long int x){
    long long a = x*(x+1)/2;
    long long xxx = n - x;
    /* printf("xxx = %lld a =%lld x=%d\n",xxx,a,x); */
    if(a - xxx > k){
        return 1;
    }
    else if(a-xxx < k){
        return -1;
    }
    else if(a-xxx == k){
        return 11;
    }
}
int main(){
    cin>>n>>k;
    long long int l = 0,r = n+1;
    while(l<=r){
        long long int mid = (l+r)/2;
        /* printf("%d\n",mid); */
        if(judge(mid) == 1){
            r = mid - 1;
        }
        else if(judge(mid) == -1){
            l = mid + 1;
        }
        else if(judge(mid) == 11){
            ans = mid;
            /* exit(0); */
            break;
        }
    }

    printf("%lld\n",n-ans);
    return 0;
}


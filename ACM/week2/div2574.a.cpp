#include <bits/stdc++.h>
using namespace std;
int a[1005];
int main(){
    int n,k,m;
    int ans = 0,cnt = 0;
    cin>>n>>k;
    for(int i = 0;i < n;i++){
        cin>>m;
        a[m]++;
        if(a[m] == 2){
            a[m] = 0;
            ans+=2;
        }
    }
    

    for(int i = 0;i <= k+1;i++){
        if(a[i] == 1){
            cnt++;
        }
    }

    if(cnt%2 == 0){
        ans = ans + cnt/2;
    }
    else if(cnt%2 == 1){
        ans = ans + cnt/2+1;
    }

    printf("%d\n",ans);

    return 0;
}


#include <bits/stdc++.h>
using namespace std;
int n;
struct node{
    int v,k,c,l;
}a[1005];
int dp[1005];
bool cmp(struct node a,struct node b){
    return a.v < b.v;
}
int main(){
    while(cin>>n&&n!=0){
        memset(dp,0,sizeof(dp));
        memset(a,0,sizeof(a));

        int sum = 0;
        for(int i = 1;i <= n;i++){
            cin>>a[i].v>>a[i].k>>a[i].c>>a[i].l;
            sum = a[i].l*a[i].c+a[i].k+sum;
        }
        sort(a+1,a+n+1,cmp);

        dp[0] = sum;
        /* cout<<sum<<endl; */
        /* int mi; */

        for(int i = 1;i <= n;i++){
            /* mi = dp[i-1]; */
            for(int j = 0;j < i;j++){
                int x = a[i].l*a[j].c; 
                int y = a[j].k+a[j].l*a[j].c;
                /* cout<<x<<' '<<y<<endl; */
                /* printf("dp[i]+x-y:%d\n",dp[i]+x-y); */
                dp[i] = min(dp[i],dp[j] + x - y);
            }
                /* printf("dp[i] = %d\n",dp[i]); */
            /* dp[i] = mi; */
        }
        /* for(int i = 0;i < n;i++) */
        cout<<dp[n]<<endl;

    }

    return 0;
}


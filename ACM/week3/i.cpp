#include <bits/stdc++.h>
using namespace std;
struct node{
    int q,zhong,flag;
}mp[405];
bool cmp(struct node a,struct node b){
    return a.q < b.q;
}
int main(){
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        int tem1,tem2,tt;
        memset(mp,0,sizeof(mp));
        for(int i = 0;i < n;i++){
            cin>>tem1>>tem2;
            if(tem1 > tem2){
                tt = tem1;
                tem1 = tem2;
                tem2 = tt;
            }
            if(tem1%2==0){
                mp[i].q = tem1-1;
            }
            else{
                mp[i].q = tem1;
            }

            if(tem2%2==1){
                mp[i].zhong = tem2+1;
            }
            else{
                mp[i].zhong = tem2;
            }
        }
        sort(mp,mp+n,cmp);
        int cnt = 0,ans = -1;
        while(!cnt){
            cnt = 1;
            ans++;

            int ppp = 0;
            for(int i = 0;i < n;i++){
               if(!mp[i].flag && ppp < mp[i].q){
                    ppp = mp[i].zhong;
                    mp[i].flag = 1;
                    cnt = 0;
                }
            }
        }
        printf("%d\n",ans*10);
    }
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
int vis[1000];
int main(){
    int q,m;
    cin >> q;
    while(q--){
        int cnt=0,flag = 0;
        memset(vis,0,sizeof(vis));
        cin >> m;
        for(int i=1;i<=4*m;i++)
            cin >> vis[i];
        sort(vis+1,vis+1+4*m);
        for(int i=1;i<=4*m;i+=2){
            if(vis[i]!=vis[i+1]){
                cout << "NO\n";
                cnt=1;
                break;
            }
        }
        if(cnt)
            continue;
        int temp=4*m;
        int ans=vis[1]*vis[temp];
        for(int i=1;i<=2*m;i+=2){
            if(vis[i]*vis[temp-i]!=ans){
                flag=1;
                break;
            }
        }
        if(flag)
            cout <<"NO"<<"\n";
        else
            cout <<"YES"<<"\n";
    }
    return 0;
}

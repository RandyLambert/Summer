#include <bits/stdc++.h>
using namespace std;

int a[100010],du[100010],tuo[100010];
vector<int>mp[100010];
const int mod = 142857;
queue<int> q;
int main(){
    int n,k,m,ans = 0,u,v,uva;
    cin>>n>>m>>k;
    for(int i = 0;i < k;i++){
        cin>>uva;
        a[uva] = 1;
    }
    for(int i = 0;i < m;i++){
        cin>>u>>v;
        mp[u].push_back(v);
        du[v]++;
    }

    while(!q.empty()) q.pop();

    for(int i = 1;i <= n;i++){
        if(du[i] == 0)
            q.push(i);
    }
    while(!q.empty()){
        int temp = q.front();
        q.pop();
        ans = (ans + a[temp])%mod;

        for(int i = 0;i < mp[temp].size();i++){
            if(du[mp[temp][i]] >= 1){
                du[mp[temp][i]]--;
                a[mp[temp][i]]+=a[temp];
                a[mp[temp][i]]%=mod;
                if(du[mp[temp][i]] == 0){
                    q.push(mp[temp][i]);
                }
            }
        }
    }

    printf("%d\n",ans);

    return 0;
}


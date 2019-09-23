#include <bits/stdc++.h>
using namespace std;
int main(){

    set<int>q;
    int n,m,z,ans = 0;
    cin>>n>>m>>z;
    
    int x = 1,i = 1;
    while(m*i<=z){
        q.insert(m*i);
        i++;
    }
    i=  1,x = 1;
    while(n*i<=z){
        if(q.count(n*i) == 1){
            ans++;
        }
        i++;
    }

    cout<<ans<<"\n";
    return 0;
}


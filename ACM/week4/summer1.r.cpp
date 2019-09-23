#include <bits/stdc++.h>
using namespace std;
int main(){

    int n;
    while(scanf("%d",&n)&&n){
        map<int,int>q;
        int x;
        for(int i = 0;i < n;i++){
            cin>>x;
            if(q.count(x) == 0){
                q[x] = 0;
            }
            q[x]++;
        }

        for(auto it = q.begin();it!=q.end();it++)
            if(it->second == 1){
                x = it->first;
                break;
            }
        cout<<x<<"\n";
    }


    return 0;
}


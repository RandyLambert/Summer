#include <bits/stdc++.h>
using namespace std;
map<int,int>a;
int main(){

    int n,m,x,y;
    cin>>n>>m;
    for(int i = 0;i < m;i++){
        cin>>x>>y;
        if(a.count(x)== 0){
            a[x] = 0;
        }
        if(a.count(y) == 0){
            a[y] = 0;
        }
        a[x]++;
        a[y]++;
    }

    int flag = 0,cnt = 0;

    for(auto it = a.begin();it != a.end();it++){

        if(it->second%2==1){
            if(it->second == 1)
                cnt++;
            else{
                flag = 1;
                break;
            }
        }
    }

    if(flag == 0){
        cout<<"YES"<<"\n";
    }
    else if(flag == 1){
        cout<<"NO"<<"\n";
    }

    return 0;
}


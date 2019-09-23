#include <bits/stdc++.h>
 
using namespace std;
int main(){
    int k,n;
    cin>>k>>n;
    vector<string>q;
    vector<string>name;
    map<int,string> mp;
    string a = "A";
    string a1 = "Aa";
 
    for(int i = 0;i < 2;i++){
        for(int j = 0;j < 26;j++){
            if(i == 0){
                name.push_back(a);
                a[0] = a[0] + 1;
            }
            if(i == 1){
                name.push_back(a1);
                a1[0] = a1[0] + 1;
            }
        }
    }
 
    int cnt = 0;
    q.push_back("xx");
    for(int i = 1;i <= k-n+1;i++){
        cin>>a;
        q.push_back(a);
    }
 
    for(int i = 1;i <= n-1;i++){
        cout<<name[cnt]<<' ';
        mp[i] = name[cnt];
        cnt++;
    }

    
 
    for(int i = 1;i <= k+1-n;i++){
        /* cout<<q[i]<<"=q[i]"<<'\n'; */
        if(q[i] == "YES"){
            cout<<name[cnt]<<' ';
            mp[i+n-1] = name[cnt];
            cnt++;
        }
        else if(q[i] == "NO"){
            /* cout<<"dasdasd"<<'\n'; */
            cout<<mp[i]<<' ';
            mp[i+n-1] = mp[i];
        }
    }
 
    return 0;
}

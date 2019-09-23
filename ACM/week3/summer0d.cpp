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
    for(int i = 0;i < k-n+1;i++){
        cin>>a;
        q.push_back(a);
    }

    mp[0] = "A";

    for(int i = 0;i < k-n+1;i++){
        if(q[i] == "YES"){
            for(int j = i+1;j <= i+n;j++){
                if(mp.count(j)==0)
                    mp[j] = name[cnt++];        
            }
        }
    }

    for(int i = 1;i <= k;i++){
        if(mp.count(i) == 0){
            mp[i] = mp[i-1];
        }
        else if(q[i] == "NO"){
            mp[i-1] = mp[i];
        }
    }

    for(int i = 1;i <= k;i++)
        cout<<mp[i]<<" ";

    return 0;
}


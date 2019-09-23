#include <bits/stdc++.h>
using namespace std;
map<string,int>word;
vector<string> a;
string repr(string s){
    string ans = s;
    for(int i = 0;i < ans.length();i++)
        ans[i] = tolower(ans[i]);
    sort(ans.begin(),ans.end());
    return ans;
}
int main(){
    string a1;
    while(cin>>a1&&a1[0]!='#'){
       string b1 = repr(a1);
        a.push_back(a1); 
        if(word.count(b1) == 0)
            word[b1] = 0;
        word[b1]++;
    }

    vector<string>ans;
    
    for(int i = 0;i < a.size();i++){
        if(word[repr(a[i])] == 1) ans.push_back(a[i]);
    }

    sort(ans.begin(),ans.end());
    for(int i = 0;i < ans.size();i++)
        cout<<ans[i]<<"\n";
    return 0;
}

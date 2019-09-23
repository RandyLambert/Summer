#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll h[100010],r[100010],l[100010];
stack<int> q;
int main(){

    int n;
    while(cin>>n,n){
        for(int i = 0;i < n;i++){
            cin>>h[i];
        }
        while(!q.empty()) q.pop();

        for(int i = 0;i < n;i++){
            while(q.size() && h[q.top()] >= h[i])
                q.pop();

            if(q.empty()){
                l[i] = 0;
            } 
            else
                l[i] = q.top()+1;
            
            q.push(i);
        }

        while(!q.empty()) q.pop();


        for(int i = n-1;i >= 0;i--){
            while(q.size() && h[q.top()] >= h[i])
                q.pop();
            if(q.empty())
                r[i] = n;
            else
                r[i] = q.top();

            q.push(i);
        }


        ll ans = 0;
        for(int i = 0;i < n;i++)
            ans = max(ans,h[i] * (r[i] - l[i]));
        cout<<ans<<endl;
    }
    return 0;
}

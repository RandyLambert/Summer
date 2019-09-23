#include<bits/stdc++.h>
using namespace std;
long long int ans[300000+10];
int main(){
    int n,flag=0;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>ans[i];

    sort(ans+1,ans+1+n);

    for(int i=2;i<=n-1;i++){
        if(ans[i]+ans[i-1]>ans[i+1])
            flag = 1;
    }
    if(flag)
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
}

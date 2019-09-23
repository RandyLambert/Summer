#include <bits/stdc++.h>
using namespace std;
int a[100000+10];
vector<int>ans;

int main()
{
    int n;
    cin>>n;

    for(int i=0;i<n;i++)
        cin>>a[i];

    sort(a,a+n);
    int t=a[0],j=a[n-1];

    for(int i=0;i<n;i++){
        if(a[i]!=t&&a[i]!=j)
            ans.push_back(a[i]);
    }
    cout<<ans.size()<<"\n";
    return 0;
}

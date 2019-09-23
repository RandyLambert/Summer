#include <bits/stdc++.h>
using namespace std;
int a[100000+10];
int main(){
    int n,mn = 999999999,mx = -1,xx = 0;
    /* map<int,int>a; */
    cin>>n;

    for(int i = 0;i<n;i++){
        int temp;
        cin>>temp;
        /* if(a.count(temp) == 0){ */
        /*     a[temp] = 0; */
        /* } */
        if(a[temp] == 0)
            xx++;
        mx = max(mx,temp);
        mn = min(mn,temp);

        a[temp] = a[temp]+1;
        /* cout<<temp<<a[temp]<<endl; */
    }

    if(xx<=2)
        cout<<0<<"\n";
    else
        cout<<n-a[mx]-a[mn]<<"\n";


    return 0;
}


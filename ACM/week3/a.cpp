#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    double a,b,ans = 999999999;
    cin>>n>>m;
    for(int i = 0;i < n;i++){
        cin>>a>>b;
        double x = a/b;
        ans = min(x,ans);
    }
    printf("%.8lf\n",ans*m);
    return 0;
}


#include <bits/stdc++.h>
using namespace std;
int f[150000+10];
long long t[150000+10];

int findf(int x){
    if(x == f[x])
        return f[x];
    else{
        f[x] = findf(f[x]);
        return f[x];
    }
}
int main(){

    for(int i = 0;i < 150010;i++)
        f[i] = i;
    
    int n,x,y;
    long long m;
    cin>>n>>m;
    for(int i = 0;i < m;i++){

        scanf("%d%d",&x,&y);
        int fx = findf(x);
        int fy = findf(y);

        if(fx!=fy){
            f[fx] = fy;
        }
    }

    
    for(int i=1;i<=n;i++){
        t[findf(i)]++;
    }

    long long sum = 0;

    for(int i = 1;i <= n;i++){
        if(t[i]!=0&&t[i]!=1){
            sum += (t[i]*(t[i]-1)/2);
        }
    }
    
    if(sum != m)
        printf("NO\n");
    else
        printf("YES\n");
    
    return 0;
}


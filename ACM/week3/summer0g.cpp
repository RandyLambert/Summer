#include<bits/stdc++.h>
using namespace std;
int a[10];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    printf("%d\n",a[(1+n)/2]);
}


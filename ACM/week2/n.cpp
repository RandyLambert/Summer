#include <iostream>
#include <algorithm>
using namespace std;
int n;
int a[4005],b[4005],c[4005],d[4005],x1[4005*4005],x2[4005*4005];
int main(){
    scanf("%d",&n);
    for(int i = 0;i < n;i++)
        scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
    int len  = 0,len1 = 0,nn = n*n;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            x1[len++] = a[i]+b[j];
            x2[len1++] = c[i]+d[j];
        }
    }
    sort(x1,x1+nn);
    sort(x2,x2+nn);
    int ans = 0;
    for(int i = 0;i < nn;i++)
        ans = ans + (upper_bound(x2,x2+nn,-x1[i]) - lower_bound(x2,x2+nn,-x1[i]));
    printf("%d\n",ans);
    return 0;
}

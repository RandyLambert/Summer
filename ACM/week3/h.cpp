#include<bits/stdc++.h>
using namespace std;
struct node{
    int a,b;
}aa[105];
bool cmp(struct node a,struct node b){
    return a.b < b.b;
}
int main(){
    int tim;
    int n,i,j,sum;
    while(scanf("%d",&n)!=EOF&&n)
    {
        memset(aa,0,sizeof(aa));
        for(i=1;i<=n;i++)
            scanf("%d %d",&aa[i].a,&aa[i].b); 
        sort(aa+1,aa+n+1,cmp);
        sum=1;
        tim=aa[1].b;
        for(j=1;j<=n;j++)
        {
            if(aa[j].a>=tim)
            {
                sum++;
                tim=aa[j].b;
            }
        }
        printf("%d\n",sum);
    }
}

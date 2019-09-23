#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
const int maxm = maxn*(maxn);
int T,n,m,rec,q,cnt,pa[maxn], x[maxn],y[maxn];
struct node{
    int n,c,a[maxn];
}p[9];

struct edge{
    int a,b;
    int v;
}ed[maxm],e[maxn];

int findf(int x){
    if(x == pa[x])
        return x;
    else 
        return pa[x] = findf(pa[x]);
}

bool cmp(edge a,edge b){
    return a.v < b.v;
}

int solve(){
    for(int j = 1;j <=n ;j++)
        pa[j] = j;
    sort(ed,ed+cnt,cmp);
    int ans = 0,res = 1;
    rec = 0;
    for(int i = 0;i < cnt;i++){
        int fx = findf(ed[i].a);
        int fy = findf(ed[i].b);

        if(fx!=fy){
            ans = ans + ed[i].v;
            e[rec].a = ed[i].v;
            e[rec].b = ed[i].b;
            e[rec++].v = ed[i].v;
            pa[fx] = fy;
            res++;
        }
        if(res == n)
            break;
        printf("%d\n",ans);
    }


    for(int s = 0;s < (1<<q);s++){
        int cur = 0;
        for(int j = 1;j <=n ;j++)
            pa[j] = j;

        for(int j = 0;j < q;j++){
            if(s&(1 << j)){
                cur = cur + p[j].c;
                for(int i=1;i<=p[j].n;i++) {
                    int x = findf(p[j].a[i]) , y = findf(p[j].a[1]);
                    if(x != y)
                        pa[x] = y;
                }
            }
        }
        for(int i=0;i<rec;i++) { //补边
            int x = findf(e[i].a) , y = findf(e[i].b);
            if(x != y) {
                cur += e[i].v;
                pa[x] = y;
            }
        }
        ans = min(ans,cur); //更新
    }
    return ans;
}

int main(){

    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&q);
        for(int i=0;i<q;i++){
            scanf("%d%d",&p[i].n,&p[i].c);
            for(int j=1;j<=p[i].n;j++)
                scanf("%d",&p[i].a[j]);
        }
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x[i],&y[i]);


        cnt = 0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                int v = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
                ed[cnt].a = i;
                ed[cnt].b = j;
                ed[cnt++].v = v;
            }


        printf("%d\n",solve());
        if(T) printf("\n");
    }
    return 0;
}

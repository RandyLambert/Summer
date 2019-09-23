#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
const int maxm = maxn*(maxn);
int T,n,m,rec,q,cnt,par[maxn], x[maxn],y[maxn];
struct node {
    int n,c,a[maxn];
}p[9];
struct edge{
    int a,b;
    int v;
}ed[maxm],e[maxn];
bool cmp(edge a,edge b) {
    return a.v < b.v;
}
int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
int solve() {
    for(int i=1;i<=n;i++) par[i] = i;
    sort(ed,ed+cnt,cmp);
    int res = 1 ,ans = 0;
    rec = 0;
    for(int i=0;i<cnt;i++) {  //拿出原始最小生成树的边集
        int x = find(ed[i].a) , y = find(ed[i].b);
        if(x != y) {
            ans += ed[i].v;
            e[rec].a = ed[i].a;
            e[rec].b = ed[i].b;
            e[rec++].v = ed[i].v;
            par[x] = y; res++;
        }
        if(res == n) break;
        printf("%d\n",ans);
    }
    for(int s=0;s<(1<<q);s++) {    //二进制枚举所有套餐的可能情况
        for(int j=1;j<=n;j++) par[j] = j;  //初始化并查集
        int cur = 0;
        for(int j=0;j<q;j++) {
            if(s & (1<<j)) {
                cur += p[j].c;
                for(int i=1;i<=p[j].n;i++) {
                    int x = find(p[j].a[i]) , y = find(p[j].a[1]);
                    if(x != y)
                        par[x] = y;
                }
            }
        }
        for(int i=0;i<rec;i++) { //补边
            int x = find(e[i].a) , y = find(e[i].b);
            if(x != y) {
                cur += e[i].v;
                par[x] = y;
            }
        }
        ans = min(ans,cur); //更新
    }
    return ans;
 
}
int main() {
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&q);
        for(int i=0;i<q;i++) {
            scanf("%d%d",&p[i].n,&p[i].c);
            for(int j=1;j<=p[i].n;j++) scanf("%d",&p[i].a[j]);
        }
        for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
        cnt = 0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++) {
                int v = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
                ed[cnt].a = i; ed[cnt].b = j; ed[cnt++].v = v;
            }
        printf("%d\n",solve());
        if(T) printf("\n");
    }
    return 0;
}

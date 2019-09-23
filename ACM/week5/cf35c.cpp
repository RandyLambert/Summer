#include <bits/stdc++.h> 
using namespace std; 
int mp[2005][2005];
bool vis[2005][2005];
int kk1,kk2;
int xx[4] = {0,1,0,-1};
int yy[4] = {1,0,-1,0};
int n,m,k;


struct node{
    int x,y,step;
};
int judge(int x,int y){
	if(vis[x][y] == 0&&x>=1&&x<=n&&y>=1&&y<=m){
		return 1;
	}
	return 0;
}

void bfs(int x,int y){
    queue<node>q;
    while(!q.empty()) q.pop();

    node start;
    start.x = x;
    start.y = y;
    start.step = 1;
    q.push(start);

    while(!q.empty()){
        node temp = q.front();
        q.pop();
        int x1 = temp.x;
        int y1 = temp.y;

        for(int i = 0;i < 4;i++){
            int nx = x1 + xx[i];
            int ny = y1 + yy[i];
            
            if(judge(nx,ny) == 1){

                node nw;
                nw.x = nx;
                nw.y = ny;
                nw.step = temp.step+1;
                vis[nx][ny] = 1;
                mp[nx][ny] = min(mp[nx][ny],mp[x1][y1]+1);
                q.push(nw);
            }
        }
	}
}
int main(){
    freopen("input.txt", "r", stdin); //只改变输入流的文件指针，读入这个文件的内容（必须要有input这个文件）stdin是标准输入流的文件指针
    freopen("output.txt", "w", stdout); //只改变输出流的文件指针，写入output内（如果没有output这个文件就会自动生成）stdout是标准输出流的文件指针

	cin>>n>>m>>k;

    memset(mp,999999,sizeof(mp));
	
	for(int i = 0;i < k;i++){
        memset(vis,0,sizeof(vis));
		cin>>kk1>>kk2;
        mp[kk1][kk2] = 1;
        vis[kk1][kk2] = 1;
		bfs(kk1,kk2);
	}

	
	int minx,miny,ans = -111;
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(mp[i][j] > ans){
				ans = mp[i][j];
				minx = i;
				miny = j;
			}
		}
	}
	cout<<minx<<' '<<miny<<"\n";
return 0;
}

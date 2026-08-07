#include <bits/stdc++.h>
using namespace std;
int r, c;
char adj[21][21];
int visited[30];
int dy[4] = {-1,1,0,0};
int dx[4] = {0,0,-1,1};
int ret = 0;
void go(int i, int j, int cnt){
    ret = max(ret, cnt);
    for(int d=0; d<4; d++){
        int ny = i+ dy[d];
        int nx = j+ dx[d];
        if(ny<0 || nx<0 || ny>=r || nx>=c) continue;
        int next = (int)(adj[ny][nx] - 'A');
        if(visited[next]) continue;
        visited[next] = 1;
        go(ny,nx,cnt+1);
        visited[next] = 0;
    }
    return;
}


int main(){
    cin >> r >> c;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cin >> adj[i][j];
        }
    }

    visited[adj[0][0] - 'A'] = 1;
    go(0,0,1);
    cout << ret;

}

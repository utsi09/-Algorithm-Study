#include <bits/stdc++.h>
using namespace std;
int r,c,k;
int adj[10][10];
int visited[10][10];

int dy[4] = {-1,1,0,0};
int dx[4] = {0,0,-1,1};
int ret = 0;

void go(int i, int j, int cost){
    if(i == 0 && j == c-1 && cost == k){
        ret++;
        // cout << "-------\n";
        // for(int i=0; i<r; i++){
        //     for(int j=0; j<c; j++){
        //         cout << visited[i][j] << " ";
        //     }
        //     cout <<'\n';
        // }
        // cout << "-------\n";
        return;
    }

    for(int d=0; d<4; d++){
        int ny = i + dy[d];
        int nx = j + dx[d];
        if(ny<0 || nx<0 || ny>=r || nx>=c || visited[ny][nx] || adj[ny][nx]) continue;

        visited[ny][nx] = visited[i][j] + 1;
        go(ny,nx, cost+1);
        visited[ny][nx] = 0;
    }

    return;
}


int main(){
    cin >> r >> c >> k;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            char tmp; cin >> tmp;
            if(tmp == '.') adj[i][j] = 0;
            else adj[i][j] = 1;
        }
    }

    visited[r-1][0] = 1;
    go(r-1, 0, 1);

    cout << ret;
    return 0;
}

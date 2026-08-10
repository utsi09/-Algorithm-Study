#include <bits/stdc++.h>
using namespace std;
int n;
int adj[11][11];
int visited[11][11];

int dy[5] = {-1,1,0,0,0};
int dx[5] = {0,0,-1,1,0};
int ret = 98765432;


int calculate_cost(){
    int ret = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(visited[i][j]){
                ret += adj[i][j];
            }
        }
    }
    return ret;
}


void explore(int i, int j, int cost){
    if(cost > 3) return;
    if(cost == 3){
        ret = min(ret, calculate_cost());
        return;
    }
    if(j==n-1){
        return;
    }
    if(i==n-1){ // 행 초과나 이미 꽃 있으면 다음열 검사
        explore(1,j+1,cost);
        return;
    }
    if(visited[i][j] || adj[i][j] > ret){
        explore(i+1,j,cost);
        return;
    }
    //안놓기
    explore(i+1, j, cost);

    bool checker = true;
    for(int d=0; d<5; d++){ //4방향에 놓인 꽃 있는지 검사
        int ny = i + dy[d];
        int nx = j + dx[d];
        if(visited[ny][nx]) checker = false;
    }
    if(!checker){ //겹치면 
        explore(i+1, j, cost);
        return;
    }

    for(int d=0; d<5; d++){
        int ny = i + dy[d];
        int nx = j + dx[d];
        visited[ny][nx] = 1;
    }
    explore(i+1, j, cost+1); //놓기
    for(int d=0; d<5; d++){
        int ny = i + dy[d];
        int nx = j + dx[d];
        visited[ny][nx] = 0;
    }


    return;
}

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> adj[i][j];
        }
    }

    explore(1,1,0);
    
    cout << ret;


    return 0;
}

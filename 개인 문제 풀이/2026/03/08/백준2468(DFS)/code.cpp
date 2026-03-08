#include <bits/stdc++.h>

using namespace std;
const int map_size = 101;
int adj[map_size][map_size];
int visited[map_size][map_size];
int max_ground = 0;


int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void DFS(int i, int j, int d){
    visited[i][j] = 1;
    for(int k=0; k<4; k++){
        int there_y = i + dy[k];
        int there_x = j + dx[k];
        if(there_y<0 || there_y>=map_size || there_x<0 || there_x>=map_size) continue;
        if(adj[there_y][there_x]<=d) continue;
        if(visited[there_y][there_x]) continue;
        DFS(there_y,there_x,d);
    }
    
}

int main() {
    int N=0;
    cin >> N;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cin >> adj[i][j];
        }
    }
    for(int d=0; d<=100; d++){
        fill(&visited[0][0], &visited[0][0]+map_size*map_size,0);
        int cnt_ground = 0;

        for (int i=0; i<N; i++){
            for (int j=0; j<N; j++){
                if (visited[i][j] | adj[i][j]<=d) continue; 
                cnt_ground++;
                DFS(i,j,d);
            }
        }
        if(max_ground < cnt_ground) max_ground = cnt_ground;
    }
    cout << max_ground;
}

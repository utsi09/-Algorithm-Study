#include <bits/stdc++.h>
using namespace std;
int n,m;
const int map_size = 10;
int adj_init[map_size][map_size];
int adj[map_size][map_size];
int visited[map_size][map_size];

vector<pair<int,int>> empty_v;
vector<pair<int,int>> virus;
vector<vector<int>> wall_combi;
int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};
int cnt;

void combi(int start, vector<int> v){
    if(v.size() == 3){
        wall_combi.push_back(v);
        return;
    }
    for(int i=start+1; i<empty_v.size(); i++){
        v.push_back(i);
        combi(i,v);
        v.pop_back();
    }
}

void bfs(int i,int j){
    adj[i][j] = 2; //바이러스 오염
    for(int k=0; k<4; k++){
        int ny = i + dy[k];
        int nx = j + dx[k];
        if(ny<0 || nx<0 || ny>=n || nx>=m) continue;
        if(visited[ny][nx]>0 || adj[ny][nx]!=0) continue;
        visited[ny][nx] = 1;
        bfs(ny,nx);
    }
}

int main() {
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0; j<m; j++){
            cin >> adj[i][j];
            adj_init[i][j] = adj[i][j];
            if (adj[i][j] == 0) empty_v.push_back(make_pair(i,j));
            if (adj[i][j] == 2) virus.push_back(make_pair(i,j));
        }
    }
    vector<int> v;
    combi(-1,v);
    
    for (vector<int> wall_idx : wall_combi){ //조합마다
        int ret = 0;
        for(int i=0;i<n;i++){
            for(int j=0; j<m; j++){
                adj[i][j] = adj_init[i][j];
            }
        }
        fill(&visited[0][0], &visited[0][0] + 10*10, 0);
        for (int j : wall_idx){ //3번
            int y = empty_v[j].first; 
            int x = empty_v[j].second;
            adj[y][x] = 1;
        }
        //벽을 세훈 후
        for (pair<int,int> single_virus : virus){
            
            visited[single_virus.first][single_virus.second] = 1;
            bfs(single_virus.first, single_virus.second);
        }
        //바이러스 퍼진 후
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(adj[i][j]==0){
                    ret++;
                }
            }
        }

        cnt = max(cnt,ret);
    }
    cout << cnt;
    return 0;
}

// '''
// 1. adj[10][10]에 맵을 입력받는다
// 2. vector<pair<int,int>> empty 을 받는다
// 3. (주의 empty 후보 공간들 좌표 기준으로)콤비 함수에서 각 조합에 따른 이중 벡터 wall_combi 를 저장한다
// 4. for (vector<int> i : wall_combi) 로 검사할 인덱스
//     for (그 후보 공간들을 벽 1 로 세운다)

// 5. for (바이러스 좌표 : 바이러스좌표벡터) 
// 6. bfs 함수에 넣기 
//     6.1 방문검사 bfs visited 만날때마다 2로 만들기 기저사례등등

// 7. 맵 크기 nxm에서 0의 개수 계산해서 출력
// '''

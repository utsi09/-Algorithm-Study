#include <bits/stdc++.h>
using namespace std;
int n, m;
int sr,sc;
int er,ec;
int adj[304][304];
int visited[304][304];

int ret = 0; //결과
int dy[4] = {-1,1,0,0};
int dx[4] = {0,0,-1,1};

int main(){
    cin >> n >> m;
    cin >> sr >> sc >> er >> ec;
    sr--; sc--;
    er--; ec--;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            char tmp;
            cin >> tmp;
            if(tmp == '#' || tmp == '*'){
                adj[i][j] = 2;
            }
            else{
                adj[i][j] = tmp - '0';
            }
        }
    }    

    queue<pair<int,int>> q;
    bool checker = false;
    while(1){
        q.push({sr,sc}); //다시 출발지에서 시작
        memset(visited, 0, sizeof(visited));
        while(q.size()){
            int ii = q.front().first;
            int jj = q.front().second;
            if(ii == er && jj == ec){
                checker = true;
                break;
            }
            if(adj[ii][jj] == 1){ //1겹만
                adj[ii][jj] = 8;
                q.pop();
                continue;
            }
            q.pop();
            for(int dd=0; dd<4; dd++){
                int ny = ii + dy[dd];
                int nx = jj + dx[dd];
                if(ny<0 || nx<0 || ny>=n || nx>=m || visited[ny][nx]) continue;
                visited[ny][nx] = 1;
                q.push({ny,nx});
            }
        }
        ret++;
        if(checker) break;
        
    }
    
    cout << ret;
}

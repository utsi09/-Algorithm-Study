#include <bits/stdc++.h>
using namespace std;
int n,m,k;
int adj[21][21];
int visited[21][21];
int fire_map[21][21];

int dy[4] = {0,1,0,-1}; //우하좌상
int dx[4] = {1,0,-1,0};

struct turtle{
    int r,c;
    bool is_stoned = false;
    bool is_arrived = false;
    int arrived_time = -1;
};
vector<turtle> turtles;

struct volcano{
    int r,c;
    int p;
    int now_p = 0;
    bool boom_now = false;
};
vector<volcano> volcanos;

void db_visited(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << visited[i][j] << " ";
        }
        cout << '\n';
    }
}
void db_fire(){
    cout << "----- fire map -----\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << fire_map[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "----- fire map -----\n";
}

//초기 인풋
void get_input(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> adj[i][j];
        }
    }
    for(int i=0; i<m; i++){
        turtle tmp;
        cin >> tmp.r >> tmp.c;
        turtles.push_back(tmp);
    }
    for(int i=0; i<k; i++){
        volcano tmp;
        cin >> tmp.r >> tmp.c >> tmp.p;
        volcanos.push_back(tmp);
    }
}

void turtle_bfs(){
    queue<pair<int,int>> q;
    q.push({n-1,n-1});
    visited[n-1][n-1] = 1;
    while(q.size()){
        int ii = q.front().first;
        int jj = q.front().second;
        q.pop();
        for(int dd=0; dd<4; dd++){
            int ny = ii + dy[dd];
            int nx = jj + dx[dd];
            if(nx<0 || ny<0 || nx>=n || ny>=n || visited[ny][nx]) continue;
            if(adj[ny][nx] == 1) continue;
            bool is_there = false;
            for(const turtle& t : turtles){
                if(t.r == ny && t.c == nx){
                    is_there = true;
                    break;
                }
            }
            if(is_there) continue;
            q.push({ny,nx});
            visited[ny][nx] = visited[ii][jj] + 1;
        }
    }
    return;
}

void move_turtles(int turn){
    for(turtle& t : turtles){
        if(t.is_arrived || t.is_stoned) continue;
        memset(visited, 0, sizeof(visited));
        turtle_bfs();
        //db_visited();
        int best_dis=98765432;
        int best_i = -1;
        int best_j = -1;
        for(int dd=0; dd<4; dd++){
            int ny = t.r + dy[dd];
            int nx = t.c + dx[dd];
            if(ny<0 || nx<0 || ny>=n || nx>=n || adj[ny][nx]) continue;
            if(visited[ny][nx] != 0 && visited[ny][nx] < best_dis){
                best_dis = visited[ny][nx];
                best_i = ny;
                best_j = nx;
            }
        }

        if(best_i == -1) continue;
        //cout << t.r << "," << t.c << "-->";
        t.r = best_i;
        t.c = best_j;
        if(t.r == n-1 && t.c == n-1){
            t.arrived_time = turn;
            t.is_arrived = true;
            t.r = -1;
            t.c = -1;
        }
        //cout << t.r << "," << t.c << '\n';
    }



}

void increase_volcano(){
    for(volcano& v : volcanos){
        v.now_p = min(v.now_p+10, v.p);
    }
    return;
}

void blow_fire(volcano& v){
    v.boom_now = true;
    int heat = v.p;
    fire_map[v.r][v.c] += heat;
    int ii = v.r;
    int jj = v.c;
    for(int dd=0; dd<4; dd++){
        heat = v.p / 2;
        while(1){
            int ny = ii + dy[dd];
            int nx = jj + dx[dd];
            if(ny<0 || nx<0 || ny>=n || nx>=n || adj[ny][nx] == 1 || heat <= 0) break; //해당방향 종료
            fire_map[ny][nx] += heat;
            heat /= 2;
            for(volcano& next_v : volcanos){
                if(next_v.boom_now == false && next_v.r == ny && next_v.c == nx){
                    if(fire_map[ny][nx] + next_v.now_p >= next_v.p){
                        blow_fire(next_v);
                    }
                }
            }
        }
    }

}

void transfer_heat(){
    for(volcano& v : volcanos){
        //cout << v.now_p << " : now p &" << v.p << ": v p\n";    
        if(v.now_p < v.p) continue;
        blow_fire(v);
    }
    //db_fire();
}

void stoning_turtle(){
    for(turtle& t : turtles){
        if(fire_map[t.r][t.c] >= 20){
            t.is_stoned = true;
        }
    }
}

void volcano_attack(){
    // 1. 열기 전파
    //2. 연쇄 반응
    transfer_heat();
    //3.바다거북의 위기
    stoning_turtle();
    

    
}

int main(){
    cin >> n >> m >> k;
    get_input();
    
    for(int t=1; t<=100; t++){
        memset(fire_map, 0, sizeof(fire_map));
        //화산들 초기화
        for(volcano& v : volcanos){
            if(v.boom_now){
                v.now_p = 0;
            }
            v.boom_now = false;
        }

        // 1. 바다 거북 이동
        move_turtles(t);
        //2. 화산 압력 증가 
        increase_volcano();
        //3. 화산 분출 및 연쇄 반응
        volcano_attack();
    }

    for(turtle& t : turtles){
        cout << t.arrived_time << "\n";
    }
}
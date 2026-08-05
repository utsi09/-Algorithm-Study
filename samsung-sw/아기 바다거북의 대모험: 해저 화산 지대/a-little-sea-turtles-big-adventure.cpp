#include <bits/stdc++.h>
using namespace std;
int n, m, k;
int adj[21][21];
int visited[21][21];
int fire_map[21][21];


int dy[4] = {0,1,0,-1}; //우(→), 하(↓), 좌(←), 상(↑)
int dx[4] = {1,0,-1,0};

struct turtle{
   int r,c;
   bool is_arrived = false;
   bool is_stoned = false;
   int arrive_time = -1;
};
vector<turtle> turtles;

struct volcano{
   int r,c;
   int p;
   int nowp = 0;
   bool now_boom = false;
};
vector<volcano> volcanos;

void db_visited(){
   cout << "---- visited ----\n";
   for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
         cout << visited[i][j] << " ";
      }
      cout << '\n';
   }
   cout << "---- visited end ----\n";
   return;
}

void db_fire(){
   cout << "---- fire ----\n";
   for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
         cout << fire_map[i][j] << " ";
      }
      cout << '\n';
   }
   cout << "---- fire end ----\n";
   return;
}

void db_map(){
   cout << "---- map ----\n";
   for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
         bool checker = false;
         for(turtle& t : turtles){
            if(t.r == i && t.c == j){
               cout << "T ";
               checker = true;
            }
         } 
         if(checker) continue;
         cout << adj[i][j] << " ";
      }
      cout << '\n';
   }
   cout << "---- map end ----\n";
   return;
}

void init(){
   cin >> n >> m >> k;
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
   return;
}

void turtle_bfs(){
   memset(visited, 0, sizeof(visited));
   int i = n-1;
   int j = n-1;
   visited[i][j] = 1;
   queue<pair<int,int>> q;
   q.push({i, j});
   while(q.size()){
      int ii = q.front().first;
      int jj = q.front().second;
      q.pop();
      for(int d=0; d<4; d++){
         int ny = ii + dy[d];
         int nx = jj + dx[d];
         if(ny<0 || nx<0 || ny>=n || nx>=n || visited[ny][nx]) continue;
         if(adj[ny][nx] == 1) continue;
         bool checker = false;
         for(const turtle& t : turtles){
            if(t.r == ny && t.c == nx){
               checker = true;
               break;
            }
         }
         if(checker) continue;
         visited[ny][nx] = visited[ii][jj] + 1;
         q.push({ny,nx});
      }
   }
   return;
}

void move_turtles(int turn){
   for(turtle& t : turtles){
      if(t.is_arrived || t.is_stoned) continue;
      turtle_bfs();
      // db_visited();
      // return;
      int i = t.r;
      int j = t.c;
      int best_dis = 98765432;
      int best_i = -1;
      int best_j = -1;
      for(int d=0; d<4; d++){
         int ny = i + dy[d];
         int nx = j + dx[d];
         if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
         if(adj[ny][nx] == 1) continue;
         if(visited[ny][nx] != 0 && best_dis > visited[ny][nx]){
            best_dis = visited[ny][nx];
            best_i = ny;
            best_j = nx;
         }
      }
      if(best_i != -1){ // 이동
         t.r = best_i;
         t.c = best_j;
         if(t.r == n-1 && t.c == n-1){ // 도착
            t.is_arrived = true;
            t.r = -1;
            t.c = -1;
            t.arrive_time = turn;
         }
      }

   }


   return;
}

void upgrade_volcano(){
   for(volcano& v : volcanos){
      v.nowp = min(v.nowp + 10, v.p);
   }
   return;
}

void blame_fire(volcano& v){
   v.now_boom = true;
   int heat = v.p; 
   fire_map[v.r][v.c] += heat;
   
   //cout << "test" << '\n';
   for(int d=0; d<4; d++){ //방향별로
      //cout << "test" << '\n';
      heat = v.p / 2;
      int ii = v.r;
      int jj = v.c;
      while(1){ // 맵 끝까지
         int ny = ii + dy[d];
         int nx = jj + dx[d];
         
         if(ny<0 ||nx<0 || ny>=n || nx>=n){
            break;
         }
         //cout << ny << "," << nx << '\n';
         fire_map[ny][nx] += heat;         
         heat /= 2;
         for(volcano& vv : volcanos){
            if(vv.r == v.r && vv.c == v.c) continue;
            if(vv.now_boom == false && vv.r == ny && vv.c == nx && vv.nowp + fire_map[ny][nx] >= vv.p){ //영역이 겹치고 
               //cout << " chain\n";
               blame_fire(vv);
            }
         }
         ii = ny;
         jj = nx;
      }
   }
}

void chaining_heat(){
   for(volcano& v : volcanos){
      if(v.nowp < v.p || v.now_boom) continue;
      blame_fire(v);
   }

}

void check_turtles(){
   for(turtle& t : turtles){
      if(t.is_arrived || t.is_stoned) continue;
      if(fire_map[t.r][t.c] >= 20){
         t.is_stoned = true;
      }
   }
}

void active_volcano(){
   // 1. 열기 전파 & 2. 연쇄 반응
   chaining_heat();

   // 3. 바다거북의 위기
   check_turtles();
}

int main(){

   init();

   for(int t=1; t<=100; t++){
      memset(fire_map, 0, sizeof(fire_map));
      for(volcano& v : volcanos){
         if(v.now_boom){
            v.now_boom = false; //now boom 초기화
            v.nowp = 0;
         }
         
      }
      // 1. 바다 거북의 이동
      //db_map();
      move_turtles(t);
      //db_map();
      // 2. 화산 압력 증가
      upgrade_volcano();

      //3. 화산 분출 및 연쇄 반응
      active_volcano();
      //db_fire();

   }

   for(turtle& t : turtles){
      cout << t.arrive_time <<'\n';
   }
   return 0;
}
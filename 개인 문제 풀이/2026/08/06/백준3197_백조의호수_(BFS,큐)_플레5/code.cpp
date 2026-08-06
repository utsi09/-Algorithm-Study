#include <bits/stdc++.h>
using namespace std;
int r, c;
int adj[1504][1504];
int visited[1504][1504];
int bird_visited[1504][1504];

int dy[4] = {-1,1,0,0};
int dx[4] = {0,0,-1,1};
int turn = 0;


queue<pair<int,int>> now_go;
queue<pair<int,int>> next_go;
vector<pair<int,int>> birds;

queue<pair<int,int>> now_bird;
queue<pair<int,int>> next_bird;


int main(){
   cin >> r >> c;
   for(int i=0; i<r; i++){
      for(int j=0; j<c; j++){
         char tmp; cin >> tmp;
         if(tmp == '.'){ //물
            now_go.push({i,j});
            adj[i][j] = 0;
         }
         else if(tmp == 'X'){ //빙판
            adj[i][j] = 1;
         }
         else if(tmp == 'L'){
            adj[i][j] = 2;
            now_go.push({i,j});
            if(now_bird.size() == 0) now_bird.push({i,j}); //첫번째만 넣어
            birds.push_back({i,j});
         }
      }
   }

   memset(visited, 0, sizeof(visited));
   bird_visited[birds[0].first][birds[0].second] = 1;

   while(1){
      bool checker = false;
      while(now_bird.size() && !checker){
         int b_i = now_bird.front().first;
         int b_j = now_bird.front().second;
         now_bird.pop();
         
         for(int d=0; d<4; d++){
            int ny = b_i + dy[d];
            int nx = b_j + dx[d];
             
            if(ny<0 || nx<0 || ny>=r || nx>=c || bird_visited[ny][nx]) continue;
            if(adj[ny][nx] == 1){
               next_bird.push({ny,nx});
               bird_visited[ny][nx] = 1;
               continue;
            }
            if(ny == birds[1].first && nx == birds[1].second){ //만남
               checker = true;
               break;
            }
            now_bird.push({ny,nx});
            bird_visited[ny][nx] = 1;
         }
      }

      if(checker) break;

      while(now_go.size()){ //현재 큐 처리

         int ii = now_go.front().first;
         int jj = now_go.front().second;
         now_go.pop();

         visited[ii][jj] = 1; //꺼내진 놈은 방문처리
         
         for(int d=0; d<4; d++){
            int ny = ii + dy[d];
            int nx = jj + dx[d];
            if(ny<0 || nx<0 || ny>=r || nx>=c) continue;
            if(visited[ny][nx]) continue; //전에 꺼냈던 놈은 안감
            if(adj[ny][nx] == 1){ //빙판 만나면
               next_go.push({ny,nx}); //다음에 갈곳에 추가
               adj[ny][nx] = 0;
            }
         }

      }

      now_go = next_go;
      now_bird = next_bird;

      while(next_go.size()){ //비우기
         next_go.pop();
      }
      while(next_bird.size()){ //비우기
         next_bird.pop();
      }
      turn++;
   }
   // 1500 x 1500 
   cout << turn;
   return 0;
}

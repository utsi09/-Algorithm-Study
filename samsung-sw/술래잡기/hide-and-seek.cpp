#include <bits/stdc++.h>
using namespace std;
int n,m,h,k;

int odd_dy[2] = {-1, 0}; //상 , 우
int odd_dx[2] = {0, 1};

int even_dy[2] = {1, 0}; //하, 좌
int even_dx[2] = {0, -1};
int adj[100][100];
int pi=0;
int dy[4] = {-1,0,1,0}; //상우하좌
int dx[4] = {0,1,0,-1};

int r_dy[2][2] = {{0,0},{1,-1}}; //우좌 / 하상
int r_dx[2][2] = {{1,-1}, {0,0}};
int score = 0;
bool back_check = false;
int pr; //경찰 위치 정중앙
int pc;
struct runner{
   int r,c;
   int d;
   //bool in_tree = false;
   bool is_catch = false;
};
vector<runner> runners;

struct tree
{
   int r,c;
   vector<pair<int,int>> people;
};
vector<tree> trees;

vector<pair<int,int>> police_move;
vector<int> police_dir;

void db_police(){
   cout << "---- p map ----\n";
   for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
         cout << setw(3) << adj[i][j] << " ";
      }
      cout << '\n';
   }
}
void db_map(){
   cout << "---- map ----\n";
   for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
         if(police_move[pi].first == i && police_move[pi].second == j){
            cout << "P ";
            continue;
         }
         bool checker = false;
         for(runner& r : runners){
            if(r.r == i && r.c == j){
               cout << "R ";
               checker = true;
               break;
            }
         }
         if(!checker) cout << "0 ";
      }
      cout << '\n';
   }
}
void init(){
   cin >> n >> m >> h >> k;
   pr = n/2;
   pc = n/2;
   for(int i=0; i<m; i++){
      runner tmp;
      cin >> tmp.r >> tmp.c;
      tmp.r--; tmp.c--;
      cin >> tmp.d;
      runners.push_back(tmp);
   }

   for(int i=0; i<h; i++){
      tree tmp;
      cin >> tmp.r >> tmp.c;
      tmp.r--; tmp.c--;
      trees.push_back(tmp);
   }

   int idx = 1;
   bool is_end = false;
   int ii = pr;
   int jj = pc;
   int ptr=1;
   adj[ii][jj] = ptr;
   //cout << pr << ","<< pc <<'\n';
   ptr++;
   police_move.push_back({ii, jj});
   //police_dir.push_back(0); //상우하좌
   while(1){
      if(idx % 2 == 1){ //홀수
         for(int dd=0; dd<2; dd++){
            for(int i=0; i<idx; i++){ //인덱스만큼 1,2,
               int ny = ii + odd_dy[dd];
               int nx = jj + odd_dx[dd];
               if(ny<0 || nx<0 || ny>=n || nx>=n) break; //방향 종료
               if(ny == 0 && nx == 0) is_end = true;
               police_move.push_back({ny, nx});
               police_dir.push_back(dd);
               ii = ny; jj = nx;
               adj[ii][jj] = ptr; ptr++;
            }
            if(is_end) break;
         }
         if(is_end) break;
         idx++;
      }
      if(idx % 2 == 0){ //짝수
         for(int dd=0; dd<2; dd++){
            for(int i=0; i<idx; i++){ //인덱스만큼 1,2,
               int ny = ii + even_dy[dd];
               int nx = jj + even_dx[dd];
               if(ny<0 || nx<0 || ny>=n || nx>=n) break; //방향 종료
               if(ny == 0 && nx == 0) is_end = true;
               police_move.push_back({ny, nx});
               police_dir.push_back(dd+2);
               ii = ny; jj = nx;
               adj[ii][jj] = ptr; ptr++;
            }
            if(is_end) break;
         }
         if(is_end) break;
         idx++;
      }

      
   }

}

int check_distance(runner& r){
   int now_pi = police_move[pi].first;
   int now_pj = police_move[pi].second;
   return abs(r.r - now_pi) + abs(r.c - now_pj);
}
pair<int,int> get_rmove(runner& r){
   int minus = (r.d > 0 ? 0 : 1);
   int ny = r.r + r_dy[abs(r.d) - 1][minus];
   int nx = r.c + r_dx[abs(r.d) - 1][minus];
   return {ny,nx};
}

void run_runner(){
   for(runner& r : runners){
      if(r.is_catch) continue;
      if(check_distance(r) > 3) continue;
      int ny,nx;
      //cout << r.r << "," << r.c << " >> ";
      tie(ny,nx) = get_rmove(r);
      if(ny<0 || nx<0 || ny>=n || nx>=n){
         //cout << "change d!!! " << ny <<"," << nx <<'\n';
         r.d = -r.d;
         tie(ny,nx) = get_rmove(r);
         //cout << " >> " << ny <<"," << nx <<'\n';
      }
      if(ny == police_move[pi].first && nx == police_move[pi].second){
         continue; //술래 있으면 움직이지않는다
      }
      r.r = ny;
      r.c = nx;
      //cout << r.r << "," << r.c << "\n";
   }
   return;
}

//상하좌우

void run_police(int turn){
   int catch_num = 0;

   pi++;
   if(pi >= police_move.size()){ //끝에 도달하면 뒤집어서 가기
      //cout << "max vector \n";
      reverse(police_move.begin(), police_move.end());
      reverse(police_dir.begin(), police_dir.end());
      back_check == false ? back_check = true : back_check = false;
      pi = 1;
   }
   // for(auto tmp : police_move){
   //    cout << tmp.first << "," << tmp.second << '\n';
   // }
   //cout << "test1\n";
   int ii = police_move[pi].first;
   int jj = police_move[pi].second;
   int d=0;
   if(ii==0 && jj ==0){
      d = 2; //하
   }
   else if(ii == n/2 && jj== n/2){
      d = 0;
   }
   else {
      d = police_dir[pi];
      if(back_check) d = (d+2) % 4; //상우하좌니깐 2더한걸 4로 나머지하면 됨
   }
   //cout << "test2\n";
   
   //db_map();
   //cout << "d : " << d << '\n';
   bool checker = true; 
   for(tree& t : trees){
      if(t.r == ii && t.c == jj){
         checker = false;
         break;
      }
   }
   for(runner& r: runners){
      if(!checker) break;
      if(r.r == ii && r.c == jj){
         catch_num++;
         r.is_catch = true;
         r.r = -1;
         r.c = -1;
      } 
   }
   for(int i=0; i<2; i++){
      int ny = ii + dy[d];
      int nx = jj + dx[d];
      //cout << ny << "," << nx <<'\n';
      if(ny<0 || nx<0 || ny>=n || nx>=n) break;
      ii = ny;
      jj = nx;
      checker = true; 
      for(tree& t : trees){
         if(t.r == ny && t.c == nx){
            checker = false;
            break;
         }
      }
      if(!checker) continue;
      for(runner& r: runners){
         if(r.r == ny && r.c == nx){
            catch_num++;
            r.is_catch = true;
            r.r = -1;
            r.c = -1;
         } 
      }
   }
   score += catch_num * turn;
   return;
}
int main(){
   
   init();
   //db_police();
   for(int t=1; t<=k; t++){
    
      run_runner();
      //db_map();
      run_police(t);
      //db_map();
      //return 0;
      //cout << t << " : turn , score : " <<  score << '\n';
   }
   
   cout << score;
   return 0;
}
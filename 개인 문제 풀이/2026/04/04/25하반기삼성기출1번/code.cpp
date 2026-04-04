#include <bits/stdc++.h>
using namespace std;
int n, k, l; 
const int map_size = 31;
int adj[map_size][map_size];
int visited[map_size][map_size];
int tmp_adj[map_size][map_size]; //마지막 복사용 맵

vector<pair<int,int>> robots;
vector<pair<int,int>> best_robots;
vector<int> robot_heading; //로봇 방향 {0:오른쪽, 1:아래쪽, 2:왼쪽, 3:위쪽}

int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};
int tmp_in;
int tmp_i, tmp_j;
int heading = 0;

void BFS(int i,int j, int robot_idx){
    best_robots.clear();
    visited[i][j] = 1;
    queue<pair<int,int>> q;
    q.push(make_pair(i,j));
    int min_dis = 987654;
    while(q.size()){
        
        int curr_i = q.front().first;
        int curr_j = q.front().second;
        q.pop();
        if(adj[curr_i][curr_j]>0){ //양수(먼지가 있고 처음 찾았을때 그 거리
            if(min_dis == 987654){
                min_dis = visited[curr_i][curr_j]; // 최소 거리 갱신
            }
            if(visited[curr_i][curr_j] != min_dis) continue; //최소거리 아니면 이제 보내기
            best_robots.push_back(make_pair(curr_i, curr_j)); // 먼지에 도달한 좌표 푸쉬
        }

        for(int d=0; d<4; d++){
            int same_pos = 0;
            int ny = curr_i + dy[d];
            int nx = curr_j + dx[d];
            if(ny<0 || nx<0 || nx>=n || ny>=n) continue; //오버플로우
            if(visited[ny][nx]!=0) continue; //방문노드체크
            if(adj[ny][nx] == -1) continue; //물건체크
            for(pair<int,int> robot : robots){ //로봇 순회하며 같은지 체크
                if(ny == robot.first && nx == robot.second) {
                    same_pos = 1;
                    continue;
                }
            }
            if(same_pos==1) continue;
            visited[ny][nx] = visited[curr_i][curr_j]+1;
            q.push(make_pair(ny,nx));
        }
    }
    // 루프 끝낫으므로 최소 거리인 좌표들 정렬해서 위치 결정
    if(best_robots.empty()) return;
    int best_i=1e8;
    int best_j=1e8;
    pair<int,int> best_pos;
    for(pair<int,int> pos : best_robots){ //좌표 후보들 마다 검사
        if(pos.first < best_i){ //행이 더 작으면
            best_i = pos.first; //현재 베스트값 갱신
            best_j = pos.second;
            best_pos = pos; // 현재 포즈로 갱신
        } 
        if(pos.first == best_i){ //행이 같으면
            if(pos.second < best_j){ //열 비교, 열이 더 작으면 
                best_i = pos.first; //현재 베스트값 갱신
                best_j = pos.second;
                best_pos = pos; // 현재 포즈로 갱신
            }
        }
    }
    robots[robot_idx].first = best_pos.first;
    robots[robot_idx].second = best_pos.second;
    return;
}

int main(){
    cin >> n >> k >> l;
    for(int i=0; i<n; i++){
        for(int j=0;j<n;j++){
            cin >> tmp_in;
            adj[i][j] = tmp_in;
        }
    }
    for(int i=0; i<k; i++){
        cin >> tmp_i >> tmp_j;
        robots.push_back(make_pair(tmp_i-1,tmp_j-1));
    }

    for(int i=0; i<l; i++){ //L번만큼 반복 시작

        // 1. 청소기 이동 
        for(int j=0; j<k; j++){ //청소기 개수만큼 진행
            fill(&visited[0][0], &visited[0][0] + 31*31, 0);
            int dis = 1e8;
            tmp_i = robots[j].first;
            tmp_j = robots[j].second;
            BFS(tmp_i, tmp_j, j); //현재 방향 거리 가져오기, 몇번째로봇
            //로봇 위치 업데이트
        }
        //  for(pair<int,int> robot : robots){ 
        //     cout << robot.first+1 << " " <<  robot.second+1<< endl;
        // }
        // 2. 청소
        for(int i=0; i<k; i++){//청소기마다 청소 진행
            //청소기 원점
            int clean_i = robots[i].first;
            int clean_j = robots[i].second;
            if(adj[clean_i][clean_j]>0){//양수(먼지) 있으면 청소 진행
                adj[clean_i][clean_j] -= 20;
                if(adj[clean_i][clean_j] < 0) adj[clean_i][clean_j]=0; //음수될수는없으니까 음수되면 0으로 초기화
            }
            int best_dust=-1; //최고먼지양
            
            vector<pair<int,int>> all_pos;
            vector<pair<int,int>> tmp_pos; //임시 pos들 저장용
            //나머지 격자들도 청소 (4방향에서 오른쪽이면 왼쪽만 빼기)
            for(int o=0;o<4;o++){ //빼는거 기준 왼,위,오른,아래
                tmp_pos.clear();
                int curr_dust=0; //현재 먼지양
                for(int j=0; j<4; j++){ // 오른, 아래, 왼, 위쪽 순서로 진행
                    if(j==o) continue; //각 방향마다 빼고 4번 반복
                    int ny = clean_i + dy[j];
                    int nx = clean_j + dx[j];
                    if(ny<0 || nx<0 || nx>=n || ny>=n) continue; //오버플로우
                    if(adj[ny][nx] == -1) continue; //물건체크
                    for(pair<int,int> robot : robots){ //로봇 순회하며 같은지 체크
                        if(ny == robot.first && nx == robot.second) continue;
                    }
                    if(adj[ny][nx] > 0){ //먼지면 더하기
                        tmp_pos.push_back(make_pair(ny,nx));
                        curr_dust += min(adj[ny][nx],20);
                    } 
                }   
                //모든 방향 더한 후, 방향에 따른 먼지량과 그 방향 저장
                if(best_dust < curr_dust){ //먼지양이 더 많으면
                    best_dust = curr_dust;
                    all_pos.clear();
                    for(pair<int,int> pos : tmp_pos){
                        all_pos.push_back(make_pair(pos.first,pos.second));
                    }
                }
                if(best_dust == curr_dust){ // 이전과 같으면 종료 (예전 정보로- 우선순위 적용)
                    continue;
                }
                
            }
            for(pair<int,int> pos : all_pos){
                //cout << pos.first+1 << "," << pos.second+1 << "delete" << endl;
                adj[pos.first][pos.second] -= 20;
                if(adj[pos.first][pos.second] < 0) adj[pos.first][pos.second] = 0;
            }
            //해당 로봇 끝
        }

        
        
        // 3. 먼지 축적
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(adj[i][j]>0){
                    adj[i][j] += 5; //5씩 축적
                }
            }
        }
        
        // 4. 먼지 확산
        
        fill(&tmp_adj[0][0],&tmp_adj[0][0]+31*31,0);
        for(int i=0;i<map_size;i++){
            for(int j=0; j<map_size;j++){
                tmp_adj[i][j] = adj[i][j]; // 3단계 전까지의 복사본 만들기
            }
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(tmp_adj[i][j]==0){
                    int plus_dust=0;
                    for(int p=0; p<4; p++){ // 오른, 아래, 왼, 위쪽 순서로 진행
                        int ny = i + dy[p];
                        int nx = j + dx[p];
                        if(ny<0 || nx<0 || nx>=n || ny>=n) continue; //오버플로우
                        if(tmp_adj[ny][nx] == -1) continue; //물건체크
                        // for(pair<int,int> robot : robots){ //로봇 순회하며 같은지 체크
                        //     if(ny == robot.first && nx == robot.second) continue;
                        // }
                        if(tmp_adj[ny][nx] > 0){ //먼지면 더하기
                            plus_dust += tmp_adj[ny][nx];
                        }
                    }
                    plus_dust /= 10;
                    adj[i][j] = plus_dust; //확산완료
                }
            }
        }


        // 5. 출력
        int cnt=0;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(adj[i][j]>0){
                    cnt += adj[i][j];
                }
            }
        }
        cout << cnt << endl;

        }
    return 0;
}

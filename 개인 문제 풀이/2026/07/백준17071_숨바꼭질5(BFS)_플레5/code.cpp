#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000004
int n, k;
int visited[2][MAXN];
int target_map[MAXN];
int t, here;
int ret;

//시간별 k의 위치 맵핑
void find_k(){
    target_map[0] = k;
    for(int i=1; i<=500000; i++){
        target_map[i] = target_map[i-1] + i;
    }
}

int main(){
    cin >> n >> k;
    find_k();
    memset(visited, -1, sizeof(visited));
    visited[0][n] = 0;
    queue<pair<int,int>> q; // 시간, 위치
    q.push({0, n});
    while(q.size()){
        tie(t, here) = q.front();
        q.pop();
        int next_t = t + 1;
        int now_k = target_map[t];
        //cout << t <<" : t || " << now_k << " : now_k || "<< here << " : here \n";
        if(visited[t % 2][now_k] != -1){ //발견
            //cout << t << '\n';
            if(now_k > 500000){
                ret = -1;
                break;
            }
            ret = t;
            break;
        }
        for(int next_n : {here+1, here-1, here*2}){
            if(next_n < 0 || next_n >= MAXN || visited[next_t % 2][next_n] != -1) continue;
            visited[next_t % 2][next_n] = visited[t % 2][here] + 1;
            q.push({next_t, next_n});
        }

        
    }

    cout << ret;
}

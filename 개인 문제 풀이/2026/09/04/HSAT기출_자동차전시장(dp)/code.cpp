#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

int n, m, k;
vector<vector<int>> edges;

vector<int> start_points;
int dp[10][100000];



void bfs(int person){
    int start = start_points[person];

    dp[person][start] = 0;
    queue<int> q;
    q.push(start);
    while(q.size()){
        int now = q.front();
        q.pop();
        for(auto& next : edges[now]){
            if(dp[person][next] != -1) continue;
            q.push(next);
            dp[person][next] = dp[person][now] + 1;
        }
    }
    return;
}



int main() {
    cin >> n >> m >> k;

    edges.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        edges[x].push_back(y);
    }

    start_points.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> start_points[i];
        start_points[i]--;
    }

    memset(dp, -1, sizeof(dp));
    
    for(int i=0; i<k; i++){
        bfs(i);
    }

    int real_cnt = 100000;
    for(int i=0; i<n; i++){ //  전시장 찾기
        bool noob = false;
        int max_dis = 0;
        for(int j=0; j<k; j++){ //start 사람

            
            if(dp[j][i] == -1){
                noob = true;
                break;
            }
            max_dis = max(max_dis, dp[j][i]);

        }
        if(noob) continue;
        real_cnt = min(real_cnt, max_dis);

    }

    if(real_cnt == 100000) cout << -1;
    else cout << real_cnt;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
#define INF 98765432
#define MAX_N 200004
int n,k;
int visited[MAX_N];
int prev_n[MAX_N];
vector<int> ret;


int main(){
    cin >> n >> k;
    
    visited[n] = 1;
    prev_n[n] = -1;
    queue<int> q;
    q.push(n);
    while(q.size()){
        int here = q.front();
        q.pop();
        if(here == k){
            break;
        }
        for(int next : {here+1, here-1, here*2}){
            if(0 > next || next >= MAX_N) continue;
            if(visited[next]) continue;
            visited[next] = visited[here] + 1;
            prev_n[next] = here;
            q.push(next);
        }
    }

    cout << visited[k] - 1 << '\n';
    for(int ptr = k; prev_n[ptr]!=-1; ptr=prev_n[ptr]){
        ret.push_back(ptr);
    }
    ret.push_back(n);
    reverse(ret.begin(), ret.end());
    for(int i=0; i<ret.size(); i++){
        cout << ret[i] << " ";
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;
int n,m,h;
int adj[35][15];

int ret = 98765432;

bool check(){

    bool checker = true;
    for(int j=0; j<n; j++){ //첫 스타트 01234
        int c = j; //현재 열 포인터
        for(int i=0; i<h; i++){
            if(c > 0 && adj[i][c-1] == 1){ //왼쪽 사다리
                c--;
            }
            else if(c < n-1 && adj[i][c] == 1){ //오른쪽 사다리
                c++;
            }
        }
        if(j != c) checker = false;
        if(!checker) break;
    }

    return checker;
}

void go(int i, int j, int cnt){
    if(cnt > 3) return;

    if(j == n-1){ //열이 초과해버리면 끝
        if(check()) ret = min(ret, cnt); //유효시 최소 갱신
        return;
    }
    if(i == h){ // 해당 열 다 진행했으면
        go(0, j+1, cnt); //다음 열로 이동
        return;
    }

    if(adj[i][j]) {
        go(i+1, j, cnt); //해당 자리 체크
        return;
    }

    go(i+1, j, cnt); // 안놓는다
    
    
    if(j > 0 && adj[i][j-1]) {
        return;
    }
    if(j < n-2 && adj[i][j+1]){
        return;
    } 
    adj[i][j] = 1; //사다리 놓아보기
    go(i+1, j, cnt+1); //다음으로
    adj[i][j] = 0;
    
    return;
}

int main(){
    cin >> n >> m >> h;

    for(int i=0; i<m; i++){
        int tmpi, tmpj;
        cin >> tmpi >> tmpj;
        adj[tmpi-1][tmpj-1] = 1;            
    }
    

   


    go(0,0,0);

    if(ret == 98765432) cout << "-1";
    else cout << ret;
    
    return 0;
}

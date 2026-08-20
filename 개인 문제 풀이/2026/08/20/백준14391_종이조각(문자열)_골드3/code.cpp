#include <bits/stdc++.h>
using namespace std;
int n,m;
int adj[5][5];

int cnt = 0;

int main(){
    cin >> n >> m;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%1d", &adj[i][j]);
        }
    }


    for(int s=0; s<(1 << 16)-1; s++){
        
        //가로 검사
        int col = 0;
        for(int i=0; i<n; i++){
            
            int cur = 0; //한 행에 쌓인 값
            for(int j=0; j<m; j++){

                if(s & 1 << (i * m + j)){ //격자의 특정 부분이 현재 무작위값 s 에서 0 즉 가로면 
                    cur = cur*10 + adj[i][j];
                }
                else{
                    col += cur;
                    cur = 0;
                }
            }
            col += cur;
        }


        //세로 검사
        int row = 0;
        for(int j=0; j<m; j++){
           
            int cur = 0; //한 행에 쌓인 값
            for(int i=0; i<n; i++){

                if(!(s & 1 << (i * m + j))){ //격자의 특정 부분이 현재 무작위값 s 에서 0 즉 가로면 
                    cur = cur*10 + adj[i][j];
                }
                else{
                    row += cur;
                    cur = 0;
                }
            }
            row += cur;
        }
        //cout << "this turn cnt is " << row + col << '\n';
        cnt = max(cnt, row + col);
    }
    cout << cnt;

    return 0;
}

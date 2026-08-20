#include <iostream>
using namespace std;
int n,m;
string paper[5];
string paper2[5];
int best = 0;

void solve(const string p[5], int c, int r){
    int cnt = 0;
    for(int j=0; j<c; j++){
        int this_num = 0;
        for(int i=0; i<r; i++){
            this_num = (this_num*10) + (p[i][j] - '0');
            
        }
        cnt += this_num;
        //cout << cnt << '\n';
    }
    best = max(best, cnt);
    //cout << "best : " << best << '\n';
    return;
}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        cin >> paper[i];
        
    }
  
    for(int j=0; j<m; j++){
        for(int i=0; i<n; i++){
            char c = paper[i][j];
            paper2[j] += c;
        } 
    }
    
    solve(paper,m,n);
    solve(paper2,n,m);

    cout << best;
    return 0;
}

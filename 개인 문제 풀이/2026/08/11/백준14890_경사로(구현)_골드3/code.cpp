#include <bits/stdc++.h>
using namespace std;
#define maps 104
int a[maps][maps];
int b[maps][maps];
int n, l;
int ret = 0;


void solve(int m[maps][maps]){
    for(int i=0; i<n; i++){
        bool checker = true;
        int my_h = 0;
        int cont = 1; //연속
        for(int j=0; j<n; j++){
            if(my_h == 0){
                my_h = m[i][j];
                continue;
            }
            int now = m[i][j];  
            if(my_h == now) cont++;
            else if(my_h + 1 == now && cont >= l){
                cont = 1;
            }
            else if(my_h - 1 == now && cont >= 0){
                cont = -l + 1;
            }
            else{
                checker = false;
                break;
            }
            my_h = now;
        }
        if(cont < 0 || !checker){
            continue;
        }
        else{
            ret++;
        }
    }

}

int main(){
    cin >> n >> l;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> a[i][j];
            b[j][i] = a[i][j];
        }
    }

    solve(a);
    solve(b);
    cout << ret;

    return 0;
}

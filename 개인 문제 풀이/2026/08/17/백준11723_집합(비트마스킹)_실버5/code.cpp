#include <iostream>
#include <vector>
using namespace std;

int m;
int s = 0; //공집합

int main(){
    cin >> m;
    for(int i=0; i<m; i++){
        string cmd;
        cin >> cmd;
        if(cmd == "all"){
            for(int p=0; p<21; p++){
                s |= (1 << p);
            }
            continue;
        }
        else if(cmd == "empty"){
            s = 0;
            continue;
        }
        int x;
        cin >> x;
        if(cmd == "add"){
            s |= 1 << x;
        }
        else if(cmd == "remove"){
            s &= ~(1 << x); 
        }
        else if(cmd == "check"){
            if(s & (1 << x)){
                cout << "1\n";
            }
            else cout << "0\n";
        }
        else if(cmd == "toggle"){
            s ^= (1 << x); 
        }
    }
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

string m[3] = {"pi", "ka", "chu"};
int now = -1;
int idx = -1; //[] 에서 몇번째까지 했는지

string s;

int main(){
    cin >> s;

    for(int i=0; i<s.size(); i++){ //pikapi
        if(now == -1){ //첫
            for(int ii=0; ii<3; ii++){
                if(s[i] == m[ii][0]){ // p , k , c
                    now = ii; //맵 배열의 idx 가르킴
                    idx = 1; //이제 이거랑 매칭되는지 봐야함
                }
            }
            if(now == -1){
                cout << "NO\n";
                return 0;
            }
        }
        else{ //이미 가르키고 있음
            if(s[i] == m[now][idx]){
                idx++;
                if(idx == m[now].size()){
                    now = -1;
                    idx = -1;
                }
            }
            else{
                cout << "NO\n";
                return 0;
            }
        }

    }

    if(idx != -1) cout << "NO";
    else cout << "YES";

    return 0;
}

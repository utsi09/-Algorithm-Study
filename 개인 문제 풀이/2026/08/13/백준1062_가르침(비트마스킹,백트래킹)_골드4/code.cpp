#include <bits/stdc++.h>
using namespace std;
int n,k;
int words[51];
int ret = 0;

void solve(int i, int saved, int k, int cnt){
    if(i == n){
        ret = max(ret, cnt);
        return;
    }
    if(n-1 - i + cnt < ret){ // 3 - 2 다배운다고 쳣을때 ret 보다 적으면
        return;
    }
    //몇개 단어 배워야하는지 검사
    
    int apb = 0;
    for(int idx=0; idx<26; idx++){
        if((words[i] & 1<<idx) && !(saved & 1<<idx)){ //해당 알파벳이 안배운거면 배워야할 단어+
            apb++;
        }
    }
    
    //안배움 먼저
    solve(i+1, saved, k, cnt);

    int next = 0;
    
    //남아있는 배울수있는 글자 이하면 배움
    if(apb <= k){ // 복사
        //cout << i << " idx check ... we have to learn " << apb << "!! \n";
        next = words[i];
        next |= saved; 
        solve(i+1, next, k-apb, cnt+1);
    }
    
    return;
}

int main(){
    cin >> n >> k;
    if(k < 5){ // a n t i c 5개는 무조건 배움
        cout << 0;
        return 0;
    }

    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        for(char tmp : s){
            words[i] |= 1 << tmp - 'a';
        }
    }

    int saved = 0;
    solve(0, saved, k, 0);
    /*
    n개의 글자 구성이 잇다
    각 i별로 배우는 글자들을 저장해서 백트래킹
    k를 넘거나 그러면 리턴
    */
    cout << ret;


    return 0;
}

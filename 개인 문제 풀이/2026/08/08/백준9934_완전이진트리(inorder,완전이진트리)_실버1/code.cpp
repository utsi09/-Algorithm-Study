#include <bits/stdc++.h>
using namespace std;
int _end;
int k;
int max_num = pow(2, 10);
vector<int> inorder(max_num);
vector<vector<int>> level(11);

void go(int s, int e, int l){
    int mid = (s + e) / 2;
    //cout << s << e << mid <<'\n';
    if(s >= mid){
        //cout << "final : ";
        for(int i=s; i<=e; i++){
            //cout << inorder[i];
            level[l].push_back(inorder[i]);
        }
        //cout <<'\n';
        return;
    }

    level[l].push_back(inorder[mid]);
    //cout << "level : "<< l << ", put :" << inorder[mid]<<'\n';
    go(s, mid-1, l+1);
    go(mid+1, e, l+1);

    return;
}


int main(){
    cin >> k;
    _end = pow(2, k) - 1;
    //cout << _end;
    for(int i=0; i< _end; i++){
        int tmp; cin >> tmp;
        inorder[i] = tmp;
    }

    go(0, _end - 1, 0);

    for(int i=0; i<k; i++){
        for(int ptr : level[i]){
            cout << ptr << " ";
        }
        cout << '\n';
    }
}

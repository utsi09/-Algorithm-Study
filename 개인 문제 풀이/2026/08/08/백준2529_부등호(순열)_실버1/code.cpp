#include <bits/stdc++.h>
using namespace std;
int k;
char kmap[10];
vector<int> bigv;
vector<int> smallv;

void check(vector<int> thisv){
    bool checker = true;
    for(int i=0; i<k; i++){
        if(kmap[i] == '>'){
            if(thisv[i] < thisv[i+1]){ //비유효
               checker = false;
            }
        }
        else {
            if(thisv[i] > thisv[i+1]){ //비유효
               checker = false;
            }
        }
    }

    if(checker == true){
        if(bigv.empty() || thisv > bigv){
            bigv = thisv;
        }
        if(smallv.empty() || thisv < smallv){
            smallv = thisv;
        }
    }
    return;
}


void make_num(int depth, vector<int> thisv){
    if(depth == k+1){
        check(thisv);
        return;
    }
    for(int i=depth; i<thisv.size(); i++){
        swap(thisv[i], thisv[depth]);
        make_num(depth+1, thisv);
        swap(thisv[i], thisv[depth]);
    }
}

int main(){
    cin >> k;
    for(int i=0; i<k; i++){
        cin >> kmap[i];
    }
    vector<int> v;
    for(int i=0; i<=9; i++){
        v.push_back(i);
    }

    make_num(0, v);

    for(int i=0; i<k+1; i++){
        cout << bigv[i];
    }
    cout <<'\n';
    for(int i=0; i<k+1; i++){
        cout << smallv[i];
    }
}

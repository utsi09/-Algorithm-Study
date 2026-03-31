#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int N = 0;
vector<int> v;
int cnt = 0;

bool check(int sum){
    if (sum <= 1) return 0;
    if (sum == 2) return 1;
    if (sum % 2 == 0) return 0;
    for (int i = 3; i*i<=sum; i++){
        if(sum % i == 0) return 0;
    }
    return 1;
}
 
int go(int idx, int sum){
    if(idx == N){
        return check(sum);
    }
    return go(idx+1,sum)+ go(idx+1, sum+v[idx]);
}

int main() {
    cin >> N;
    for(int i=0; i<N; i++) {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
    cout << go(0,0) << endl;
    return 0;
}

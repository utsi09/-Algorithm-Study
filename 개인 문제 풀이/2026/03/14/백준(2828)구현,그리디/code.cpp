#include <bits/stdc++.h>
using namespace std;
int n,m,j;
int l,r;
int ret = 0;

int main(){
    cin >> n >> m;
    int l = 1;
    cin >> j;
    for(int i=0; i<j ; i++){
        r = l + m - 1;
        int temp = 0;
        cin >> temp;
        if (temp>=l && temp<=r) continue;
        else if(temp < l){
            ret += l - temp;
            l = temp;
        }
        else{
            int dis =  temp - r;
            ret += dis;
            l = l + dis;
        }
    }
    
    cout << ret;
    return 0; 
}

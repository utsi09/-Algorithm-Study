#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int N;
string s, ret;
vector<string> v;
void go(){
    while(ret.size()){
        if(ret.front() != '0') break;
        // cout<<":will pop 0 > " << ret.front()<<endl;
        ret.erase(ret.begin());
    }
    if (ret.size()==0) ret.push_back('0');
    v.push_back(ret); 
    // cout<<ret<<":plused"<<endl;
    ret="";
}

bool cmp(string a, string b){
    if(a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

int main() {
    cin >> N;
    for(int i=0; i<N; i++){
        ret = "";
        cin >> s;
        for(int j=0; j<s.size(); j++){
            if (s[j] < 65) ret+=s[j]; 
            else if(ret.size()) go();
            if(j==s.size()-1 && ret.size()) go();
        }
    }

    sort(v.begin(),v.end(),cmp);

    for (auto i : v){
        cout << i << endl;
    }
    
    return 0;
}

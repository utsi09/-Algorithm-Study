#include <bits/stdc++.h>
using namespace std;

int n,k;
vector<int> nums;

long long cnt = 10000000000;
long long ans;

int main(){
    cin >> n >> k;

    for(int i=0; i<n; i++){
        int tmp; cin >> tmp;
        nums.push_back(tmp);
    }

    if(nums.size() == k){
        cout << "1";
        return 0;
    }

    long long ll = 1;
    long long rr = 10000000000; 
    long long mid = (ll + rr) / 2;  //현재의 패치 길이

    while(ll <= rr){
        mid = (rr+ll) / 2;
        int remained_k = k;
        int begin_idx = -1;
        //cout << min_length << " : start\n";
        for(int i=0; i<n; i++){
            // v.push_back(nums[i]); // 1. 스택에 넣어놓는다

            if(begin_idx == -1) begin_idx = nums[i];

            else if(begin_idx != -1 && nums[i] - begin_idx + 1 <= mid) { //현재 길이로 커버되면
                continue;
            }

            else if(begin_idx != -1 && nums[i] - begin_idx + 1 > mid){
                //cout << begin_idx << "~" << nums[i] << " : can't cover \n";
                begin_idx = nums[i];
                remained_k--;

            }           
            if(remained_k < 0) break;
        }
        remained_k--;
        if(remained_k >= 0){ //넉넉하면
            rr = mid - 1;
            ans = mid;
        }
        else if(remained_k < 0){
            ll = mid + 1;
        }
        cnt = min(cnt, ans);
    }

    cout << cnt;
    return 0;
}
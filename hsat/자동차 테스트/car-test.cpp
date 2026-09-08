#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, q;
vector<int> efficiency;


int main() {
    cin >> n >> q;

    efficiency.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> efficiency[i];
    }

    sort(efficiency.begin(), efficiency.end());

    for (int i = 0; i < q; i++) {
        int m;
        cin >> m;
        int ll = 0;
        int rr = n-1;
        int mid;
        while(1){
            mid = (ll + rr) / 2;
            if(efficiency[mid] == m){
                cout << mid * (n-1 - mid) << '\n';
                break; 
            }

            else if(efficiency[mid] > m){
                rr = mid - 1;
            }
            else{
                ll = mid + 1;
            }
            if(ll > rr){
                puts("0");
                break;
            }
        }

    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
int x;
int stick = 64;
int ret = 98765432;



int main(){
	cin >> x;

	if(x == stick){
		cout << "1";
		return 0;
	}


	for(int mask=0; mask<(1<<6); mask++){
		if(mask == x){
			int cnt = 0;
			for(int oft=0; oft<6; oft++){
				if(mask & 1<<oft) cnt++;
			}
			ret = min(ret, cnt);
		}
	}

	cout << ret;
	return 0;
}

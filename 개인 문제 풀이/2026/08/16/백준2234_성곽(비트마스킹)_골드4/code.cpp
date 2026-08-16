#include <bits/stdc++.h>
using namespace std;
int n,m;
int rawm[1000][1000];
int room[1000][1000];

int dy[4] = {0,-1,0,1}; // 서북동남
int dx[4] = {-1,0,1,0}; // 서북동남

int room_idx = 0;
int biggest_room = 0;
vector<vector<int>> adj(1000*1000);
int rsize[10000];


void db_room(){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cout << room[i][j] << " ";
		}
		cout << '\n';
	}


}


void explore(int i, int j){
	room_idx++;
	int room_size = 1;
	room[i][j] = room_idx;
	queue<pair<int,int>> q;
	q.push({i,j});
	while(q.size()){
		int ii = q.front().first;
		int jj = q.front().second;
		q.pop();
		for(int d=0; d<4; d++){
			int ny = ii + dy[d];
			int nx = jj + dx[d];
			bool checker = true;
			if(ny<0 || nx<0 || ny>=n || nx>=m) checker = false;
			if(room[ny][nx]){
				checker = false;
				if(room[ny][nx] != room_idx){
					//cout << "다른방 찾았다\n";
					adj[room_idx].push_back(room[ny][nx]);
				}
			}

			if(checker && !(rawm[ii][jj] & 1)){  //벽이 없으면
				//cout << d << " : 벽 없음 \n";
				q.push({ny,nx});
				room[ny][nx] = room_idx;
				room_size++;
			}
			rawm[ii][jj] /= 2;
			
		}
	}
	biggest_room = max(biggest_room, room_size);
	rsize[room_idx] = room_size;
	return;

}

int new_big = 0;

void find_new_big_room(){
	for(int i=0; i<adj.size(); i++){
		for(auto adj_room : adj[i]){
			new_big = max(new_big, rsize[i]+ rsize[adj_room]);
		}
	}
	return;

}

int main(){
	cin >> m >> n;

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> rawm[i][j];
		}
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(room[i][j] == 0) explore(i,j);
		}
	}

	for(auto tmp : adj){
		unique(tmp.begin(), tmp.end());
	}

	find_new_big_room();
	
	//db_room();
	cout << room_idx << '\n';
	cout << biggest_room << '\n';
	cout << new_big;
	return 0;
}

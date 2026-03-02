#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

vector<int> adj[1004];
int visited[1004];

// 후위 순회 : 왼쪽 -> 오른쪽 -> 루트
void postOrder(int here) {
    if(visited[here]==1) return;
    if(adj[here].size()==1) postOrder(adj[here][0]);
    if(adj[here].size()==2) {
        postOrder(adj[here][0]);
        postOrder(adj[here][1]);
    }
    visited[here] = 1;
    cout << here << endl;
}

// 전위 순회 : 루트 -> 왼쪽 -> 오른쪽
void preOrder(int here) {
    if(visited[here]==1) return;
    if(adj[here].size()==1) {
        visited[here] = 1;
        cout << here << endl;
        preOrder(adj[here][0]);
    }
    if(adj[here].size()==2) {
        visited[here] = 1;
        cout << here << endl;
        preOrder(adj[here][0]);
        preOrder(adj[here][1]);
    }
    if(visited[here] == 0){
        visited[here] = 1;
        cout << here << endl;
    }
}

// 중위 순회 : 왼쪽 -> 루트 -> 오른쪽
void inOrder(int here) {
    if(visited[here]==1) return;
    if(adj[here].size()==1) inOrder(adj[here][0]);
    if(adj[here].size()==2) {
        inOrder(adj[here][0]);
        visited[here] = 1;
        cout << here << endl;
        inOrder(adj[here][1]);
    }
    if(visited[here] == 0){
        visited[here] = 1;
        cout << here << endl;
    }
}

int main() {
    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(4);
    adj[2].push_back(5);

    int root = 1;

    cout << "\n 트리순회 : postOrder \n";
    postOrder(root); 
    memset(visited, 0, sizeof(visited));

    cout << "\n 트리순회 : preOrder \n";
    preOrder(root); 
    memset(visited, 0, sizeof(visited));

    cout << "\n 트리순회 : inOrder \n";
    inOrder(root);

    return 0;
}

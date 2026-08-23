#include <bits/stdc++.h>
using namespace std;

int n,m;

struct box{
    int k,h,w,c;
    int r = -1;
    bool is_delete = false;
};
vector<box> boxes;

int dx[2] = {-1,1};
int delete_cnt = 0;
int db[51][51];


void db_map(){
    memset(db, 0 , sizeof(db));
    
    for(box& b : boxes){
        cout << b.k << " : " << b.r << "," << b.c << '\n';
        for(int i=b.r; i<b.r + b.h; i++){
            for(int j=b.c; j<b.c+b.w; j++){
                db[i][j] = b.k;
            }
        }
    }

    for(int i=n-1; i>=0; i--){
        for(int j=1; j<=n; j++){
            cout << db[i][j] << " ";
        }
        cout << '\n';
    }

}


void init(){
    cin >> n >> m;
    for(int i=0; i<m; i++){
        box tmp;
        cin >> tmp.k >> tmp.h >> tmp.w >> tmp.c;
        boxes.push_back(tmp);
    }
    return;
}

void stack_box(){
    for(int i=0; i<boxes.size(); i++){
        if(boxes[i].is_delete) continue;
        int best_r = -1;
        bool can_stack = false;
        //cout << boxes[i].k << ": k\n";
        for(int j=0; j<i; j++){
            if(boxes[j].is_delete) continue;
            //가로 겹침
            for(int ii = boxes[i].c; ii < boxes[i].c + boxes[i].w; ii++){
                for(int jj = boxes[j].c; jj < boxes[j].c + boxes[j].w; jj++){
                    if(ii == jj){
                        //cout << ii << ": stacked!\n";
                        best_r = max(best_r, boxes[j].r + boxes[i].h);
                        can_stack = true;
                        break;
                    }
                }
            }
        }
        if(!can_stack){
            boxes[i].r = boxes[i].h - 1;
        }
        else{
            boxes[i].r = best_r;
        }   
        //cout << boxes[i].r << '\n';
    }


}


void delete_box(int t){
    int best_k = 98765432;
    int best_idx = -1;
    for(int i=0; i<boxes.size(); i++){ //박스들마다
        if(boxes[i].is_delete) continue;
        bool can_escape = true;
        for(int j=0; j<boxes.size(); j++){ //한개씩 일일히 지목하면서 체크
            if(boxes[j].is_delete) continue;
            if(i == j) continue;
            if((t % 2 == 0 && boxes[i].c > boxes[j].c) || (t % 2== 1 && boxes[i].c < boxes[j].c)){
                for(int ii = boxes[i].r; ii >= boxes[i].r - boxes[i].h + 1; ii--){
                    for(int jj = boxes[j].r; jj>=boxes[j].r - boxes[j].h + 1; jj--){
                        if(ii == jj){
                            //cout << boxes[i].k << "vs" << boxes[j].k << "cant escape \n";
                            can_escape = false;
                            break;
                        }

                    }
                    if(!can_escape) break;
                }
            }
            if(!can_escape) break;
        }
        if(can_escape){
            if(best_k > boxes[i].k){
                best_idx = i;
                best_k = boxes[i].k;
            }
        }
    }
    boxes[best_idx].is_delete = true;
    delete_cnt++;
    cout << best_k << '\n';
    return;
}


int main(){
    init();


    for(int t=0; t>=0; t++){
        stack_box();
        //db_map();
        delete_box(t);
        //db_map();
        if(delete_cnt == m){
            break;
        }
    }

    return 0;
}

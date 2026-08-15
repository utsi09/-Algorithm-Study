#include <bits/stdc++.h>
using namespace std;
int m, t;
int pr, pc;

int my[8] = {-1,-1,0,1,1,1,0,-1};
int mx[8] = {0,-1,-1,-1,0,1,1,1};

int py[4] = {-1,0,1,0}; // 상-좌-하-우
int px[4] = {0,-1,0,1}; // 상-좌-하-우

int dead[5][5]; //칸에 시체 남은 턴수
int cnt_map[5][5]; //칸에 살아있는 몬스터 수

int best_catch = 0;
int best_cost = 999;

struct monster{
    int r, c;
    int d;
    bool is_egg = false;
    bool is_deleted = false;
};
vector<monster> monsters;


void db_map(){

    cout << "------- map ------\n";
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            bool checker = false;
            for(const monster& m : monsters){
                if(!m.is_egg && !m.is_deleted){
                    if(m.r == i && m.c == j){
                        cout << "M ";
                        checker = true;
                        break;
                    }
                }
            }
            if(pr == i && pc == j){
                cout << "P ";
                checker = true;
            }
            if(!checker) cout << "0 ";
        }
        cout << '\n';
    }
    cout << "------- map end ------\n";
    return;

}

void init(){
    cin >> m >> t;
    cin >> pr >> pc;
    pr--;
    pc--;
    for(int i=0; i<m; i++){
        monster tmp;
        cin >> tmp.r >> tmp.c >> tmp.d;
        tmp.r--; tmp.c--; tmp.d--;
        monsters.push_back(tmp);
    }

    return;
}

void copy_monster(){
    int original_num = monsters.size();
    for(int i=0; i<original_num; i++){
        if(monsters[i].is_egg || monsters[i].is_deleted) continue;
        monster tmp;
        tmp.r = monsters[i].r;
        tmp.c = monsters[i].c;
        tmp.d = monsters[i].d;
        tmp.is_egg = true;
        monsters.push_back(tmp);
    }


    return;
}

void move_monster(){
    for(monster& m : monsters){
        if(m.is_deleted || m.is_egg) continue;

        int i = m.r;
        int j = m.c;
        int d = m.d;

        for(int t=0; t<8; t++){
            bool can_go = true;
            int ny = i + my[d];
            int nx = j + mx[d];

            if(ny<0 || nx<0 || ny>=4 || nx>=4 || dead[ny][nx] > 0) can_go = false;
            else if(ny == pr && nx == pc) can_go = false;

            if(!can_go){
                d = (d+1) % 8;
                continue;
            }
            else{
                m.r = ny;
                m.c = nx;
                m.d = d;
            }
        }

    }
    return;
}

void search_path(int i, int j, int cnt, int catched, int cost){

    if(cnt == 3){
        if(catched > best_catch){
            best_catch = catched;
            best_cost = cost;
        }
        else if(catched == best_catch){
            if(cost < best_cost){
                best_catch = catched;
                best_cost = cost;
            }
        }
        return;
    }

    for(int d=0; d<4; d++){
        int ny = i + py[d];
        int nx = j + px[d];
        if(ny<0 || nx<0 || ny>=4 || nx>=4) continue;
        int this_catch = cnt_map[ny][nx];
        cnt_map[ny][nx] = 0;

        search_path(ny,nx, cnt+1, catched + this_catch, cost*10+d);
        cnt_map[ny][nx] = this_catch;
    }



}


void move_pacman(){
    memset(cnt_map, 0, sizeof(cnt_map));

    for(monster& m : monsters){ //미리 살아 있는 몬스터 개수 채워넣기
        if(!m.is_deleted && !m.is_egg){
            cnt_map[m.r][m.c]++;
        }
    }
    best_catch = 0;
    best_cost = 999;
    search_path(pr,pc,0,0,0);
    //cout << best_cost << '\n';
    // 3 1 2
    for(int ptr = 100; ptr>=1; ptr/=10){
        //cout << "ptr : " << ptr << '\n';
        int this_d = best_cost / ptr;
        best_cost -= this_d * ptr;

        pr = pr + py[this_d];
        pc = pc + px[this_d];

        for(monster& m : monsters){
            if(!m.is_egg && !m.is_deleted){
                if(m.r == pr && m.c == pc){
                    m.is_deleted = 1;
                    m.r = -1;
                    m.c = -1;
                    dead[pr][pc] = 3;
                }
            }
        }


    }
    return;
}

void clean_dead_monster(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            dead[i][j]--;
        }
    }


}

void make_monster(){
    for(monster& m : monsters){
        if(m.is_egg){
            m.is_egg = false;
        }
    }
    return;
}

int check_alive_mosnter(){
    int ret = 0;
    for(monster& m : monsters){
        if(!m.is_egg && !m.is_deleted){
            ret++;
        }
    }

    return ret;
}

int main(){

    init();

    for(int turn=0; turn<t; turn++){
        //1. 몬스터 복제 시도
        copy_monster();
        //db_map();

        //2. 몬스터 이동
        move_monster();
        //db_map();

        //3. 팩맨 이동
        move_pacman();
        //db_map();

        //4. 몬스터 시체 소멸
        clean_dead_monster();

        //5. 몬스터 복제 완성
        make_monster();

    }

    cout << check_alive_mosnter();
    
    return 0;
}
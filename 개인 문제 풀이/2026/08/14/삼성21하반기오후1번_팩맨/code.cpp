#include <bits/stdc++.h> 
using namespace std; 
int m, t; 
int pr, pc; 
int my[8] = {-1,-1,0,1,1,1,0,-1}; 
int mx[8] = {0,-1,-1,-1,0,1,1,1}; 
 
int py[4] = {-1,0,1,0}; //상좌하우 
int px[4] = {0,-1,0,1}; 
int visited[5][5]; 
 
int dead[4][4];        // 시체 남은 턴 
int cnt_map[4][4];      // 현재 칸별 살아있는 몬스터 수 
 
struct monster{ 
    int r,c; 
    int d; 
    bool is_egg = false; 
    int is_died = 0; //시체 있음 
    bool will_eat = false; 
    bool is_deleted = false; //시체도 없어짐 
}; 
vector<monster> monsters; 
 
int max_catch = 0; 
int best_cost = 0; 
 
void db_map(){ 
    for(int i=0; i<4; i++){ 
        for(int j=0; j<4; j++){ 
            bool checker = false; 
            for(const monster& m : monsters){ 
                if(!m.is_deleted && !m.is_egg && !m.is_died){ 
                    if(m.r == i && m.c == j){ 
                        cout << "M "; 
                        checker = true; 
                        break; 
                    } 
                } 
            } 
            if(i == pr && j == pc){ 
                cout << "P "; 
                checker =true; 
            } 
            if(!checker) cout << "0 "; 
        } 
        cout << "\n"; 
    } 
} 
 
 
void init(){ 
    cin >> m >> t; 
    cin >> pr >> pc; 
    pr--; 
    pc--; 
    for(int i=0; i<m; i++){ 
        monster tmp; 
        cin >> tmp.r >> tmp.c >> tmp.d; 
        tmp.d--; 
        tmp.r--; 
        tmp.c--; 
        monsters.push_back(tmp); 
    } 
    return; 
} 
 
void copy_m(){ 
    int original_size = monsters.size(); 
    for(int i=0; i<original_size; i++){ 
        monster& m = monsters[i]; 
        if(m.is_egg || m.is_died || m.is_deleted) continue; 
        monster new_egg; 
        new_egg.r = m.r; 
        new_egg.c = m.c; 
        new_egg.d = m.d; 
        new_egg.is_egg = true; 
        monsters.push_back(new_egg); 
    } 
    return; 
} 
 
void move_m(){ 
    for(monster& m : monsters){ 
        if(m.is_egg || m.is_died || m.is_deleted) continue; 
        int i = m.r; 
        int j = m.c; 
        int d = m.d; 
        for(int tt=0; tt<8; tt++){ 
            int ny = i + my[d]; 
            int nx = j + mx[d]; 
            bool checker = true; 
            if(ny<0 || nx<0 || nx>=4 || ny>=4 || (ny == pr && nx == pc)){ 
                checker = false; 
            } 
 
            else if(dead[ny][nx] > 0) checker = false; 
             
            if(!checker){ 
                d = (d+1) % 8; 
                continue; 
            } 
            else{ 
                m.d = d; 
                m.r = ny; 
                m.c = nx; 
                break; 
            } 
        } 
    } 
 
    return; 
} 
 
void search_pmove(int ii, int jj, int cnt, int catched, int cost, vector<pair<int,int>> path){ 
 
    if(cnt == 3){ 
        if(catched > max_catch){ 
            max_catch = catched; 
            best_cost = cost; 
        } 
        else if(catched == max_catch){ 
            if(cost < best_cost){ 
                max_catch = catched; 
                best_cost = cost; 
            } 
        } 
        return; 
    } 
 
    for(int d=0; d<4; d++){ 
        int ny = ii + py[d]; 
        int nx = jj + px[d]; 
        if(ny<0 || nx<0 || nx>=4 || ny>=4) continue; 
        int catched_num = 0; 
 
        bool past_path = false; 
        for(pair<int,int>& p : path){ //과거에 있었으면 캐치 넘 추가 안함 
            if(p.first == ny && p.second == nx){ 
                past_path = true; 
            } 
        } 
        if(!past_path){ 
            catched_num = cnt_map[ny][nx]; 
        } 
        path.push_back({ny,nx}); 
        search_pmove(ny, nx, cnt+1, catched + catched_num, cost*10 + d, path); 
        path.pop_back(); 
    } 
 
    return; 
} 
 
 
void move_p(){ 
    max_catch = 0; 
    best_cost = 999; 
    vector<pair<int,int>> path; 
    memset(cnt_map, 0, sizeof(cnt_map)); 
 
    for(auto& m : monsters){ 
        if(!m.is_egg && !m.is_deleted && m.is_died == 0) 
            cnt_map[m.r][m.c]++; 
    } 
 
    search_pmove(pr, pc, 0, 0, 0, path); 
    for(int ptr=100; ptr>=0; ptr/=10){ 
        int this_move = best_cost / ptr; 
        pr = pr + py[this_move]; 
        pc = pc + px[this_move]; 
        for(monster& m : monsters){ 
            if(!m.is_egg && m.is_died==0 && !m.is_deleted){ 
                if(m.r == pr && m.c == pc){ 
                    m.is_deleted = true; 
                    dead[pr][pc] = 3; 
                } 
            } 
        } 
        if(ptr==1) break; 
        best_cost -= this_move * ptr; 
    } 
    return; 
} 
 
void clean_dead_body(){ 
 
     
    for(int i=0; i<4; i++){ 
        for(int j=0; j<4; j++){ 
            if(dead[i][j] > 0) 
                dead[i][j]--; 
        } 
    } 
 
    return; 
} 
 
void make_monster(){ 
    for(monster& m : monsters){ 
        if(m.is_egg){ 
            m.is_egg = false; 
        } 
    } 
    return; 
 
} 
 
int check_ret(){ 
    int ret = 0; 
    for(monster& m : monsters){ 
        if(!m.is_egg && m.is_died==0 && !m.is_deleted){ 
            ret++; 
        } 
    } 
    return ret; 
} 
 
int main(){ 
    init(); 
    for(int turn=0; turn<t; turn++){ 
        copy_m(); 
        move_m(); 
        move_p(); 
        clean_dead_body(); 
 
        make_monster(); 
    } 
 
    cout << check_ret(); 
 
 
}

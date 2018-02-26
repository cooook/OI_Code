// antbuster by Cooook.
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define LIMIT_ANT 6

int n,m,Time,d,s,r,NOW_TIME,top,Ant_Num,Information[11][11],Cake;
float Blood[33335];
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

template<typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    int d[2];
    inline int& operator [] (const int &x) {return d[x];}
    inline void In(){d[0] = read<int>();d[1] = read<int>();}
    inline bool operator == (const Point &x) const{return d[0] == x.d[0] && d[1] == x.d[1];}
}Tower[21];

struct Ant{
    Point now,last;
    int level,age,Hp,MAX_Hp;
    bool Have_Cake;
    inline void G_Cake() {
        Have_Cake = true;
        Hp += MAX_Hp >> 1;
        if (Hp > MAX_Hp) Hp = MAX_Hp;
    }
    inline bool operator < (const Ant &x) const {
        return age > x.age;
    }
}ant[8],st[300005],tmp[8];

inline void Lose() {

    printf("Game over after %d seconds\n",NOW_TIME);

    printf("%d\n",Ant_Num);

    for (int i = 1; i <= Ant_Num; i++)

        printf("%d %d %d %d %d\n",ant[i].age - 1,ant[i].level,ant[i].Hp,ant[i].now[0],ant[i].now[1]);

    // while (true);

    exit(0);
}

inline bool Judge(int x,int y) {
    for (int i = 1; i <= Ant_Num; i++) if (ant[i].now[0] == x && ant[i].now[1] == y) return true;

    for (int i = 1; i <= s; i++) if (Tower[i][0] == x && Tower[i][1] == y) return true;
    
    return false;
}

inline Ant NEW_ANT() {
    Ant NEW = st[++top];

    NEW.now[0] = NEW.now[1] = 0;

    NEW.last[0] = NEW.last[1] = -1;

    NEW.level = (top - 1) / 6 + 1;

    NEW.Hp = NEW.MAX_Hp = Blood[NEW.level];

    NEW.age = 1;

    NEW.Have_Cake = false;

    return NEW;
}

inline void Add_Ant() {
    if (Judge(0,0)) return;

    if (Ant_Num < 6) ant[++Ant_Num] = NEW_ANT(),printf("Now,Ant %d is going out,he is the %dth ant\n",Ant_Num,top);

    std::sort(&ant[1],&ant[Ant_Num+1]);
}

inline void Change_Map() {
    register int d;

    for (int i = 1; i <= Ant_Num; i++) {

        d = ant[i].Have_Cake?5:2;
   
        Information[ant[i].now[0]][ant[i].now[1]] += d;

    }
}

inline void Ant_erase(int x) {
    int size = 0;

    if (Cake == x) ant[x].Have_Cake = false;

    Cake = 0; 

    for (int i = 1; i <= Ant_Num; i++) tmp[i] = ant[i];
    
    for (int i = 1; i <= Ant_Num; i++) if (i != x) ant[++size] = tmp[i];

    for (int i = 1; i < Ant_Num; i++) if (ant[i].Have_Cake) Cake = i;

    -- Ant_Num;
}

inline bool Judge_Postion(int id,int x,int y) {
    if (x < 0 || x > n || y < 0 || y > m) return false;

    if (x == ant[id].last[0] && y == ant[id].last[1]) return false;

    if (Judge(x,y)) return false;

    return true;
}

inline void Ant_Move() {

    for (int i = 1; i <= Ant_Num; i++) {

        int max_information = 0; bool flag = false;

        for (int j = 0; j < 4; j++) {

            if (!Judge_Postion(i,ant[i].now[0] + dx[j],ant[i].now[1] + dy[j])) continue;

            flag = true;

            max_information = std::max(Information[ant[i].now[0] + dx[j]][ant[i].now[1] + dy[j]],max_information);
            
        }

        if (!flag) {

            printf("Ant %d is in need move from (%d,%d) to (%d,%d)\n",i,ant[i].last[0],ant[i].last[1],ant[i].now[0],ant[i].now[1]);


            ant[i].last[0] = ant[i].now[0];

            ant[i].last[1] = ant[i].now[1];
            
            if (!Cake && ant[i].now[0] == n && ant[i].now[1] == m) ant[i].G_Cake(),Cake = i,printf("Ant %d get the Cake.\n",i);
 
            continue;
        }

        for (int j = 0; j < 4; j++) {
            
            if (!Judge_Postion(i,ant[i].now[0] + dx[j],ant[i].now[1] + dy[j])) continue;

            if (max_information == Information[ant[i].now[0] + dx[j]][ant[i].now[1] + dy[j]]) {

                if (ant[i].age % 5 == 0) {

                    int now_pos = j == 0?3:j-1;
                    
                    while (!Judge_Postion(i,ant[i].now[0] + dx[now_pos],ant[i].now[1] + dy[now_pos]) && now_pos != j) now_pos = now_pos==0?3:now_pos - 1;
                    
                    ant[i].now[0] += dx[now_pos];
                    
                    ant[i].now[1] += dy[now_pos];

                    ant[i].last[0] = ant[i].now[0] - dx[now_pos];

                    ant[i].last[1] = ant[i].now[1] - dy[now_pos];

                    printf("Ant %d is speical move from (%d,%d) to (%d,%d)\n",i,ant[i].last[0],ant[i].last[1],ant[i].now[0],ant[i].now[1]);

                    if (ant[i].now[0] == n && ant[i].now[1] == m && !Cake) ant[i].G_Cake(),Cake = i,printf("Ant %d get the Cake.\n",i);

                }

                else {

                    printf("Max_Information = %d\n",max_information);

                    ant[i].now[0] += dx[j];

                    ant[i].now[1] += dy[j];

                    ant[i].last[0] = ant[i].now[0] - dx[j];

                    ant[i].last[1] = ant[i].now[1] - dy[j];
                    
                    printf("Ant %d move from (%d,%d) to (%d,%d)\n",i,ant[i].last[0],ant[i].last[1],ant[i].now[0],ant[i].now[1]);

                    if (ant[i].now[0] == n && ant[i].now[1] == m && !Cake) ant[i].G_Cake(),Cake = i,printf("Ant %d get the Cake.\n",i);

                }

                break;

            }
        }

    }

}

inline float Dis(int a,int b,int c,int d) {
    return sqrt((a - c) * (a - c) + (b - d) * (b - d));
}

inline float Segment_dis(int a,int b,int c) {
    
    Point A,B;
    
    A[0] = ant[a].now[0] - Tower[b][0];
    
    A[1] = ant[a].now[1] - Tower[b][1];
    
    B[0] = ant[c].now[0] - ant[a].now[0];
    
    B[1] = ant[c].now[1] - ant[a].now[1];
    
    return abs(A[0] * B[1] - A[1] * B[0]) / Dis(Tower[b][0],Tower[b][1],ant[c].now[0],ant[c].now[1]);
}

inline void __Hp(int x) {
    printf("Ant %d is attacked\n",x);

    ant[x].Hp -= d;
}

inline int Cmp(float a,float b) {
    
    if (fabs(a-b) <= 1e-6) return 0;
    
    return a < b? -1:1;
}

inline bool Judge_Seg(int x,int y,int z) {
    Point A,B;
    
    A[0] = ant[z].now[0]-Tower[x][0];
    
    A[1] = ant[z].now[1]-Tower[x][1];
    
    B[0] = ant[y].now[0]-Tower[x][0];
    
    B[1] = ant[y].now[1]-Tower[x][1];
    
    if (A[0] * B[0] + A[1] * B[1] <= 0) return false;
    
    return true;
}

inline bool Can_Kill(int x,int y,int z) {

    if (z == y) return false;

    if (Cmp(Dis(Tower[x][0],Tower[x][1],ant[y].now[0],ant[y].now[1]),
        Dis(Tower[x][0],Tower[x][1],ant[z].now[0],ant[z].now[1])) < 0 
        && Cmp(Segment_dis(y,x,z),0.5) <= 0 && Judge_Seg(x,y,z)
    ) return true;

    return false;
}

inline void Kill_Ant(int x,int y) {

    printf("Tower %d is going to attack Ant %d\n",x,y);

    __Hp(y);

    for (int i = 1; i <= Ant_Num; i++) if (Can_Kill(x,i,y)) __Hp(i),printf("Ant %d is attacked too.\n",i);
}

inline void Attack() {

    puts("---------------------attacked---------------------------");

    if (Cake) printf("Now Ant %d Carried the Cake\n",Cake);
    
    else printf("Cake is safe\n");

    for (int i = 1; i <= s; i++) {

        printf("Tower %d is thinking about to attack.\n",i);

        if (!Cake || (Dis(Tower[i][0],Tower[i][1],ant[Cake].now[0],ant[Cake].now[1]) > r && Cake)) {

            float dis = (float)200000.0,now; int attack = 0;

            for (int j = 1; j <= Ant_Num; j++)  {
            
                printf("Dis between Ant %d and Tower %d is %f\n",j,i,now = Dis(Tower[i][0],Tower[i][1],ant[j].now[0],ant[j].now[1]));
                
                if ((now = Dis(Tower[i][0],Tower[i][1],ant[j].now[0],ant[j].now[1])) < dis) dis = now,attack = j;

            }

            if (attack == 0 || dis > r) {

                printf("Tower %d cann't doing anything\n",i);

                continue;

            }

            Kill_Ant(i,attack);
            
        }

        else Kill_Ant(i,Cake);

    }

}

inline void Cake_Checker() {

    puts("--------------Something about Cake---------------");

    if (ant[Cake].Hp < 0) Cake = 0;
    
    for (int i = 1; i <= Ant_Num; i++) if (ant[i].Hp < 0) printf("Ant %d dead.\n",i),Ant_erase(i),i = 0;

    if (ant[Cake].Hp > 0 && ant[Cake].now[0] == 0 && ant[Cake].now[1] == 0) Lose(); 

    for (int i = 1; i <= Ant_Num; i++) ant[i].age ++;

    for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) if (Information[i][j]) Information[i][j] --;
    
    if (Cake) printf("Cake is carried by Ant %d.\n",Cake);
    
    else printf("Cake is safety.\n");

}

inline void Ant_Pos_Print() {

    puts("---------------something about Ant------------------------");

    for (int i = 1; i <= Ant_Num; i++)

        printf("Ans %d,Hp is %d now at (%d,%d)\n",i,ant[i].Hp,ant[i].now[0],ant[i].now[1]);
    
    if (!Ant_Num) puts("No Ant is alive now");
}

inline void Running_Game() {
    Add_Ant();

    Change_Map();

    Ant_Move();

    Attack();

    Cake_Checker();

    Ant_Pos_Print();
}

// Ant 155 is wrong 

int main () {
    freopen("antbuster_ex2.in","r",stdin);
    // freopen("antbuster_ex.out","w",stdout);
    // freopen("my.out","w",stdout);

    n = read<int>(); m = read<int>();

    s = read<int>(); d = read<int>(); r = read<int>();

    float p = 1.1;

    for (int i = 1; i <= 500; i++) {

        Blood[i] = floor(p * 4.0);

        p *= 1.1;

    }

    for (int i = 1; i <= s; i++) Tower[i].In();

    Time = read<int>(); NOW_TIME = 1;

    for (; NOW_TIME <= Time; NOW_TIME ++) {
        printf("------------------Now time is %d------------------\n",NOW_TIME);
        
        Running_Game();
    }

    puts("The game is going on");

    printf("%d\n",Ant_Num);

    for (int i = 1; i <= Ant_Num; i++)
        printf("%d %d %d %d %d\n",ant[i].age - 1,ant[i].level,ant[i].Hp,ant[i].now[0],ant[i].now[1]);
    
    return 0;
}
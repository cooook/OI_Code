// By Cooook.
#include <bits/stdc++.h>
#define MP_WIN puts("MP")
#define FP_WIN puts("FP")
#define New_Card Tot_Card[(Card_top == m)?m:++Card_top]
#define shan 'D'
#define sha 'K'
#define tao 'P'
#define juedou 'F'
#define nanman 'N'
#define wanjian 'W'
#define wuxie 'J'
#define zhuge 'Z'
int n,m,MP_id,Card_top; char Tot_Card[2005]; bool dead[20],Judge[20],leifan[20],END;


template<typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void read_char(char &ch) {
    ch = getchar();
    while (ch != 'P' && ch != 'K' && ch != 'D' 
    && ch != 'F' && ch != 'N' && ch != 'W' 
    && ch != 'J' && ch != 'Z') ch = getchar();
}

struct Pig{
    int id,cnt,Hp,Has_zhuge; char Card[2005]; bool used[2005];
    inline void in(){
        char s[10];
        scanf("%s",s + 1);
        if (s[1] == 'M') id = 1;
        else if (s[1] == 'Z') id = 2;
        else id = 3; 
        cnt = 4; Hp = 4; Has_zhuge = 0;
        for (int i = 1; i <= 4; i++) read_char(Card[i]);
    }
    inline void out(){
        printf("Hp = %d\n",Hp);
        printf("id = %d\n",id);
        printf("cnt = %d\n",cnt);
        for (int i = 1; i <= cnt; i++)
            if (!used[i])
                printf("%c ",Card[i]);
        puts(""); puts("");
    }
    inline char& operator [] (const int &a) {return Card[a];}
    inline void G_Card(int num){
        while (num --) Card[++cnt] = New_Card;
    }
    inline int Has(char ch) {for (int i = 1; i <= cnt; i++) if (!used[i] && Card[i] == ch) return i; return false;}  
}pig[20];

inline bool Game_over() {
    if (dead[MP_id]) return true;
    for (int i = 1; i <= n; i++) if (!dead[i] && pig[i].id == 3) return false;
    return true;
}

inline void Go_END() {

    if (!dead[MP_id]) MP_WIN;
    
    else FP_WIN;
    
    for (int i = 1; i <= n; i++) {
    
        if (dead[i]) printf("DEAD");
    
        else {

            bool flag = false;
    
            for (int j = 1; j <= pig[i].cnt; j++)

                if (!pig[i].used[j]) {

                    if (!flag) printf("%c",pig[i][j]);
            
                    else printf(" %c",pig[i][j]);

                    flag = true;
                
                }
    
        }

        if (i != n) puts("");
    
    }

    exit (0);
}

inline void __Hp(int who,int x) {
    pig[x].Hp --;
    
    if (pig[x].Hp == 0) {
    
        int pos = pig[x].Has(tao);
    
        if (!pos) {
    
            dead[x] = true;

            if (Game_over()) Go_END();

            if (END) return;
    
            if (pig[x].id == 3) pig[who].G_Card(3);
    
            if (pig[x].id == 2 && pig[who].id == 1) {
    
                for (int i = 1; i <= pig[who].cnt; i++) pig[who].used[i] = true;
    
                pig[who].Has_zhuge = false;
    
            }
    
        }
    
        else pig[x].used[pos] = true,pig[x].Hp ++;
    
    }
}

inline void Kill(int who,int x) {
    
    Judge[who] = true; leifan[who] = false;
    
    int pos = pig[x].Has(shan);
    
    if (pos) {
    
        pig[x].used[pos] = true;
    
        return;
    
    }
    
    __Hp(who,x);
}

inline bool need_wuxie(int x) {

    int pos = pig[x].Has(wuxie);

    if (pos) {

        pig[x].used[pos] = true;

        Judge[x] = true;

        leifan[x] = false;

        return true;

    }

    return false;

}

inline bool __wuxie(int x,bool f) {

    int i = x;

    do {

        if (((f == 0 && pig[i].id == 3) || (f == 1 && pig[i].id != 3))) {

            if (dead[i]) goto here;

            if (!need_wuxie(i)) goto here;

            if (!__wuxie(i,f ^ 1)) return true;

            return false;

        }  

        here:;

        i = i == n?1:i + 1;

    } while (i != x) ;

    return false;

}

inline bool Okforwuxie(int x,int y) {

    if (!Judge[y]) return false;
    
    if (pig[y].id == 3) return __wuxie(x,0);

    else return __wuxie(x,1);

}

inline void Wanjian(int x) {
    
    for (int i = x == n?1:x + 1; i != x; i = i == n?1:i + 1) {
    
        if (dead[i]) continue;

        if (Okforwuxie(x,i)) continue;

        register int pos = pig[i].Has(shan);
    
        if (pos) {pig[i].used[pos] = true;continue;}
    
        else {

            __Hp(x,i);

            if (END) return;
            
            if (i == MP_id) leifan[x] = true;
        }
    }
}

inline void Nanman(int x) {

    for (int i = x == n?1:x + 1; i != x; i = i == n?1:i + 1) {
    
        if (dead[i]) continue;

        if (Okforwuxie(x,i)) continue;
    
        register int pos = pig[i].Has(sha);
    
        if (pos) {pig[i].used[pos] = true;continue;}
    
        else {
    
            __Hp(x,i);

            if (END) return;

            if (i == 1) leifan[x] = true;

        }   
    }
}

inline void __Juedou(int x,int y) {

    Judge[x] = true;leifan[x] = false;
    
    if (pig[x].id == 1 && pig[y].id == 2) return __Hp(x,y),void();

    if (Okforwuxie(x,y)) return;

    int turn = 0,pos;

    while (true) {

        pos = pig[y].Has(sha);

        if (pos) pig[y].used[pos] = true;

        else return __Hp(x,y),void();

        pos = pig[x].Has(sha);

        if (pos) pig[x].used[pos] = true;

        else return __Hp(y,x),void();

    }
    
}

inline bool Juedou(int x) {
    register int kill = -1;

    if (pig[x].id == 3) kill = MP_id;

    else if (pig[x].id == 2) {
        
        for (int i = x==n?1:x+1; i != x; i = i==n?1:i+1) {
            
            if (dead[i]) continue;

            if (Judge[i] && pig[i].id == 3) {kill = i;break;}

        }

    }

    else {

        for (int i = x==n?1:x+1; i != x; i = i==n?1:i+1) {
            
            if (dead[i]) continue;

            if ((Judge[i] && pig[i].id == 3) || leifan[i]) {kill = i;break;}

        }

    }

    if (kill == -1) return false;

    __Juedou(x,kill);

    return true;
}

inline bool Running_Game(int &x){
    if (x == n + 1) x = 1;
    
    if (dead[x]) return 1;
    
    pig[x].G_Card(2); bool have_kill = 0;

    // pig[x].out();

    for (int i = 1; i <= pig[x].cnt; i++) {

        if (END) return false;
        
        if (dead[x]) return true;
        
        if (pig[x].used[i]) continue;

        //for (int j = 1; j <= n; j++) pig[j].out();
        
        if (pig[x][i] == 'P') {

            if (pig[x].Hp < 4) ++ pig[x].Hp,pig[x].used[i] = true;
        }

        if (pig[x][i] == 'K') {
        
            if (have_kill && pig[x].Has_zhuge == 0) continue;
        
            if (pig[x].id == 1) {
        
                int next = x == n? 1 : x + 1;
        
                while (dead[next]) next = next == n?1:next + 1;
        
                if (leifan[next] || (Judge[next] && pig[next].id == 3)) pig[x].used[i] = true,Kill(x,next),have_kill = true;

            }
        
            else if (pig[x].id == 2) {
        
                int next = x == n? 1 : x + 1;
        
                while (dead[next]) next = next == n?1:next + 1;
        
                if (Judge[next] && pig[next].id == 3) pig[x].used[i] = true,Kill(x,next),have_kill = true;
        
            }
        
            else {
        
                int next = x == n? 1 : x + 1;
        
                while (dead[next]) next = next == n?1:next + 1;
        
                if (Judge[next] && pig[next].id != 3) pig[x].used[i] = true,Kill(x,next),have_kill = true;
        
            }

            if (pig[x].used[i]) i = 0;

            continue;
        
        }
        
        if (pig[x][i] == zhuge) {pig[x].Has_zhuge = true,pig[x].used[i] = true,i = 0; continue;}

        if (pig[x][i] == wanjian) {pig[x].used[i] = true,Wanjian(x),i = 0; continue;}

        if (pig[x][i] == shan) continue;

        if (pig[x][i] == wuxie) continue;

        if (pig[x][i] == juedou) {

            pig[x].used[i] = true;
            
            pig[x].used[i] = Juedou(x);
            
            if (pig[x].used[i]) i = 0; 
            
            continue;
        }

        if (pig[x][i] == nanman) {pig[x].used[i] = true,Nanman(x),i = 0; continue;}
    }
    return true;
}

int main() {
    
    freopen("kopk.in","r",stdin);
    
    freopen("kopk.out","w",stdout);

    n = read<int>(); m = read<int>();
    
    for (int i = 1; i <= n; i++) {
    
        pig[i].in();
    
        if (pig[i].id == 1) MP_id = i;
    
    } Judge[MP_id] = true;
    
    for (int i = 1; i <= m; i++) read_char(Tot_Card[i]);
    
    register int now = MP_id;
    
    for (; Running_Game(now); ++now) ;

    return 0;
}

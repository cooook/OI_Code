#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#define px player[j].x
#define py player[j].y
int n;
int map[30][30];
char produced_map[20][100];
char produced_menu[30][81];
char cbool[2][10]={"No","Yes"};
int team[3];
char input[100];
int roundflag;
int flag;
int lflag;
int mmflag;
int mspeed[10];
int deathmark[10];
int livenum;
struct abcd{
    char name[10];
    int team;
    int p;
    int attack;
    int mattack;
    int maxhp;
    int hp;
    bool power;
    int poison;
    int range;
    int movespeed;
    bool d_attack;
    bool d_move;
    bool multi_recover;
    bool p_round;
    int lv;
    int x,y;
    int movechance;
}player[10];
int mark[10];
int mmark[10]; 
int nmark[10];
int lmark[10];
int mamark[20];
int pmark[10];
int srmark[10];
int tmark[10];
int profession[10];
char pname[][10]={
    "","战士","弓箭手","魔法师","骑士","巫师","牧师"
};
char pdescribe[][200]={
    "",
    "战士，近战型职业，拥有强大的体能与进攻能力\n特殊能力：攻击力+1",
    "弓箭手，远程型职业，具有极强的远程射击能力\n特殊能力：可以对角线攻击或隔一格攻击，可以斜角移动，无法近身攻击",
    "魔法师，魔法型职业，具有灵活的魔力和精神力\n特殊能力：可以进行蓄力，蓄力后可以抵消一次攻击，也可以主动施放造成两点伤害",
    "骑士，中程近战职业，具有精良的装备和优质的坐骑\n特殊能力：移动速度+1，攻击距离+1",
    "巫师，消耗型职业，具有恐怖的消耗能力\n特殊能力：攻击距离+1，近身攻击可以造成1回合毒效果，中毒的对手每回合生命-1",
    "牧师，回复型职业，具有高超的回复技巧\n特殊能力：可以回复攻击范围内的任何人的1的生命并解除毒效果，无法攻击"
};
void divide()
{
    int i,k;
    srand((unsigned)time(NULL));
    memset(team,0,sizeof(team));
    for(i=1;i<=n;i++)
    {
        if(team[1]==(n+1)/2)
        {
            k=2;
        }
        else if(team[2]==n/2)
        {
            k=1;
        }
        else 
        {
            k=rand()%2+1;
        }
        team[k]++;
        player[i].team=k;
    }
}
void wait(int t)
{
    int tt=clock(),i;
    while(clock()<tt+t)
    {
        i++;
    }
}
void inputff(int &m)
{
    int k;
    memset(input,0,sizeof(input));
    scanf("%s",input);
    k=strlen(input);
    if(k>1)
    m=-1;
    else
    m=input[0]-'0';
}
void inputf(int &m)
{
    m=getch()-'0';
}
void initialize(int t,int m)
{
    player[t].p=m;
    player[t].attack=1+(m==1);
    player[t].maxhp=10;
    player[t].lv=1;
    profession[m]=t;
}
void choose_profession()
{
    int i,j,t,x,m;
    srand((unsigned)time(NULL));
    for(i=1;i<=n;i++)
    {
        do{
            t=rand()%n+1;
        }while(mark[t]);
        mark[t]=1;
        system("cls");
        printf("请玩家%s选择职业:\n",player[t].name);
        for(j=1;j<=6;j++)
        {
            if(!profession[j])
            {
                printf("%d-%s ",j,pname[j]);
            }
        }
        printf("7-职业介绍\n");
        inputf(m);
        while(m<1||m>6||(*(profession+m)))
        {
            if(m==7)
            {
                system("cls");
                printf("请输入您想查看的职业\n");
                for(j=1;j<=6;j++)
                {
                    printf("%d-%s ",j,pname[j]);
                } 
                printf("\n");
                inputf(x);
                while(x<1||x>6)
                {
                    inputf(x);
                }
                system("cls");
                puts(pdescribe[x]);
                printf("请选择职业:\n");
                for(j=1;j<=6;j++)
                {
                    if(!profession[j])
                    {
                        printf("%d-%s ",j,pname[j]);
                    }
                }   
                printf("7-职业介绍\n");
                inputf(m);
            }
            else
            inputf(m);
        }
        initialize(t,m);
    }
}
void mapinitialize()
{
    int i,j,x,y;
    srand((unsigned)time(NULL));
    memset(map,-1,sizeof(map));
    for(i=1;i<=15;i++)
    {
        for(j=1;j<=20;j++)
        {
            map[i][j]=0;
        }
    }
    for(i=1;i<=n;i++)
    {
        do{
            x=rand()%5+6;
            y=rand()%6+8;
        }while(map[x][y]);
        map[x][y]=i;
        player[i].x=x;
        player[i].y=y;
    }
}
void psc()
{
    int i,j;
    system("cls");
    for(i=1;i<=n;i++)
    {
        printf("%s 队伍%d Lv.%d %s HP:%d/%d",player[i].name,player[i].team,player[i].lv,pname[player[i].p],player[i].hp,player[i].maxhp);
        if(player[i].p!=6)
        printf(" 攻击力：");
        else
        printf(" 回复力："); 
        printf("%d",player[i].attack);
        if(player[i].p==3)
        printf(" 魔法攻击力：%d",player[i].mattack+2);
        if(!deathmark[i])
        {
            if(player[i].power) printf(" 蓄气");
            if(player[i].poison) printf(" 毒");
        }
        else
        printf(" 死亡");
        printf("\n");
    }
    memset(produced_map,0,sizeof(produced_map));
    for(i=1;i<=15;i++)
    {
        strcat(produced_map[i],"                    ");
        for(j=1;j<=20;j++)
        {
            if(!map[i][j]) strcat(produced_map[i],"□");
            else strcat(produced_map[i],player[map[i][j]].name);
        }
    }
    for(i=1;i<=15;i++)
    puts(produced_map[i]);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}
void pmm()
{
    int i;
    memset(produced_menu,0,sizeof(produced_menu));
    system("cls");
    strcpy(produced_menu[1],"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗");
    strcpy(produced_menu[2],"╠╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╣");
    strcpy(produced_menu[3],"╠╣                                                                        ╠╣");
    strcpy(produced_menu[4],"╠╣                                                                        ╠╣");
    strcpy(produced_menu[6],"╠╣                      欢迎来到 完美世界 Ver 1.0.0!                      ╠╣");
    strcpy(produced_menu[5],"╠╣                                                                        ╠╣");
    strcpy(produced_menu[7],"╠╣                                                                        ╠╣");
    strcpy(produced_menu[8],"╠╣                                                                        ╠╣");
    strcpy(produced_menu[9],"╠╣                                                                        ╠╣");
    if(mmflag==1)
    {
        strcpy(produced_menu[10],"╠╣                           ◣                                           ╠╣");
        strcpy(produced_menu[11],"╠╣                           ◤ 新游戏                                    ╠╣");
    }
    else
    {
        strcpy(produced_menu[10],"╠╣                                                                        ╠╣");
        strcpy(produced_menu[11],"╠╣                              新游戏                                    ╠╣");
    }
    strcpy(produced_menu[12],"╠╣                                                                        ╠╣");
    if(mmflag==2)
    {
        strcpy(produced_menu[13],"╠╣                           ◣                                           ╠╣");
        strcpy(produced_menu[14],"╠╣                           ◤继续游戏                                   ╠╣");
    }
    else
    {
        strcpy(produced_menu[13],"╠╣                                                                        ╠╣");
        strcpy(produced_menu[14],"╠╣                             继续游戏                                   ╠╣");
    }
    strcpy(produced_menu[15],"╠╣                                                                        ╠╣");
    if(mmflag==3)
    {
        strcpy(produced_menu[16],"╠╣                           ◣                                           ╠╣");
        strcpy(produced_menu[17],"╠╣                           ◤游戏介绍                                   ╠╣");
    }
    else
    {
        strcpy(produced_menu[16],"╠╣                                                                        ╠╣");
        strcpy(produced_menu[17],"╠╣                             游戏介绍                                   ╠╣");
    }
    strcpy(produced_menu[18],"╠╣                                                                        ╠╣");
    if(mmflag==4)
    {
        strcpy(produced_menu[19],"╠╣                           ◣                                           ╠╣");
        strcpy(produced_menu[20],"╠╣                           ◤  退出                                     ╠╣");
    }
    else
    {
        strcpy(produced_menu[19],"╠╣                                                                        ╠╣");
        strcpy(produced_menu[20],"╠╣                               退出                                     ╠╣");
    }
    strcpy(produced_menu[21],"╠╣                                                                        ╠╣");
    strcpy(produced_menu[22],"╠╣                                                            作者:PoPoQQQ╠╣");
    strcpy(produced_menu[23],"╠╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╣");
    strcpy(produced_menu[24],"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝");
    strcpy(produced_menu[25],"操作方法： ↑↓键移动光标 Z键确定");
    for(i=1;i<=25;i++)
        printf("%s",produced_menu[i]);
}
void reset()
{
    int i;
    for(i=1;i<=n;i++)
    {
        player[i].hp=player[i].maxhp;
        player[i].poison=false;
        player[i].power=false;
        player[i].movechance=0;
    }
    mapinitialize();
    memset(deathmark,0,sizeof(deathmark));
    livenum=n;
}
void make_team()
{
    int i;
    system("cls");
    printf("系统自动组队中，请稍等……\n");
    wait(1000);
    divide();
    system("cls");
    printf("组队完毕，队伍名单:\n");
    for(i=1;i<=n;i++)
    {
        printf("%s:队伍%d\n",player[i].name,player[i].team);
    }
    printf("请按任意键继续……\n");
    getch();
}
int randomselect()
{
    srand((unsigned)time(NULL));
    int i,j,k,l;
    psc();
    printf("系统自动猜拳中，请稍候……");
    wait(1000); 
    k=rand()%(livenum-1)+1;
    memset(mark,0,sizeof(mark));
    for(i=1;i<=k;i++)
    {
        do{
            l=rand()%n+1;
        }while(mark[l]||deathmark[l]);
        mark[l]=i;
        player[l].movechance=livenum-k;
    }
    psc();
    for(i=1;i<=k;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(mark[j]==i) break;
        }
        printf("%s ",player[j].name);
    }
    printf("获得猜拳胜利！");
    getch();
    return k;
}
void deathjudge(int j)
{
    if(player[j].hp<=0)
    {
        player[j].hp=0;
        deathmark[j]=1;
        livenum--;
        team[player[j].team]--;
        player[j].power=false;
        player[j].poison=false;
        map[player[j].x][player[j].y]=0;
        psc();
        printf("玩家%s死亡！",player[j].name);
        getch();
        if(!team[player[j].team])
        flag=1;
    }
}
void damage(int j,int dam)
{
    if(player[j].power)
    {
        player[j].power=false;
        return ;
    }
    player[j].hp-=dam;
    deathjudge(j);
}
int ntable(int j)
{
    int i,tot=0;
    int x,y;
    for(i=1;i<=n;i++)
    {
        if(player[i].team!=player[j].team&&!mark[i]&&!deathmark[i])
        {
            x=abs(player[i].x-player[j].x);
            y=abs(player[i].y-player[j].y);
            switch(player[j].p)
            {
                case 1:case 3:
                {
                    if(x+y==1)
                    nmark[i]=1;
                    if(x==1&&y==1&&player[j].d_attack)
                    nmark[i]=1;
                    break;
                }
                case 2:
                {
                    if((x==0||y==0)&&x+y>1&&x+y<=player[j].range+2)
                    nmark[i]=1;
                    if(x==y&&x<=player[j].range+1)
                    nmark[i]=1;
                    break;
                }
                case 4:
                {
                    if((x==0||y==0)&&x+y<=5)
                    nmark[i]=1;
                    if(x==1&&y==1&&player[j].d_attack)
                    nmark[i]=1;
                    break;
                }
                case 5:
                {
                    if((x==0||y==0)&&x+y==2)
                    nmark[i]=1;
                    if(x<=2&&x==y&&player[j].d_attack)
                    nmark[i]=1;
                    break;
                }
            }
            tot+=nmark[i];
        }
    }
    return tot;
}
void nattack(int j)
{
    int i,k;
    memset(nmark,0,sizeof(nmark));
    if(!ntable(j))
    {
        printf("没有可攻击的对象！");
        getch();
        return ;
    }
    psc();
    printf("请选择攻击的对象：\n");
    for(i=1;i<=n;i++)
    {
        if(nmark[i])
        {
            printf("%d-%s ",i,player[i].name);
        }
    }
    printf("7-取消\n");
    inputf(k);
    while(k<0||k>7||((!(*(nmark+k)))&&k!=7))
    {
        inputf(k);
    }
    if(k==7)
    return ;
    damage(k,player[j].attack); 
    roundflag=1;
}
int mtable(int j)
{
    int i;
    int x,y;
    int tot=0;
    for(i=1;i<=n;i++)
    {
        if(player[j].team!=player[i].team&&!mark[i]&&!deathmark[i])
        {
            x=abs(player[j].x-player[i].x);
            y=abs(player[j].y-player[i].y);
            if((!(x&&y))&&(x+y)<=(player[j].range?3:2)&&(x+y)>1)
            {
                mamark[i]=1;
            }
            tot+=mamark[i];
        }
    }
    return tot;
}
void mattack(int j)
{
    int i,k;
    memset(mamark,0,sizeof(mamark));
    if(!mtable(j))
    {
        printf("没有可攻击的对象！");
        getch();
        return ;
    }
    psc(); 
    printf("请选择攻击的目标！\n");
    for(i=1;i<=n;i++)
    {
        if(mamark[i])
        {
            printf("%d-%s ",i,player[i].name);
        }
    }
    printf("7-取消\n");
    k=getch()-'0';
    while(k<=0||k>7||((!(*(mamark+k)))&&k!=7))
    {
        k=getch()-'0';
    }
    if(k==7)
    {
        return ;
    }
    damage(k,2+player[j].mattack);
    player[j].power=false;
    roundflag=1;
}
int ptable(int j)
{
    int i;
    int x,y;
    int tot=0;
    for(i=1;i<=n;i++)
    {
        if(player[j].team!=player[i].team&&!mark[i]&&!deathmark[i])
        {
            x=abs(player[j].x-player[i].x);
            y=abs(player[j].y-player[i].y);
            if(x+y==1)
            {
                pmark[i]=1;
            }
            tot+=pmark[i];
        }
    }
    return tot;
}
void pattack(int j)
{
    int i,k;
    memset(pmark,0,sizeof(pmark));
    if(!ptable(j))
    {
        printf("没有可攻击的对象！");
        getch();
        return ;
    }
    psc();
    printf("请选择攻击的目标！\n");
    for(i=1;i<=n;i++)
    {
        if(pmark[i])
        {
            printf("%d-%s ",i,player[i].name);
        }
    }
    printf("7-取消\n");
    inputf(k);
    while(k<=0||k>7||((!(*(pmark+k)))&&k!=7))
    {
        inputf(k);
    }
    if(k==7)
    {
        return ;
    }
    if(player[k].power)
    player[k].power=false;
    else
    player[k].poison=2+player[j].p_round;
    roundflag=1;
}
void recover(int j,int rec)
{
    player[j].hp+=rec;
    if(player[j].hp>player[j].maxhp)
    player[j].hp=player[j].maxhp;
    player[j].poison=0;
}
void srtable(int j)
{
    int i;
    int x,y;
    for(i=1;i<=n;i++)
    {
        if(player[j].team==player[i].team&&!deathmark[i])
        {
            x=abs(player[j].x-player[i].x);
            y=abs(player[j].y-player[i].y);
            if(x+y<=1||(x==y&&x==1&&player[j].d_attack))
            {
                srmark[i]=1;
            }
        }
    }
}
void mrecover(int j)
{
    int i;
    int x,y;
    for(i=1;i<=n;i++)
    {
        if(player[j].team==player[i].team&&!deathmark[i])
        {
            x=abs(player[j].x-player[i].x);
            y=abs(player[j].y-player[i].y);
            if(x+y<=1||(x==y&&x==1&&player[j].d_attack))
            {
                recover(i,1);
            }
        }
    }
    roundflag=1;
}
void srecover(int j)
{
    int i,k;
    memset(srmark,0,sizeof(srmark));
    srtable(j);
    psc();
    printf("请选择回复的目标！\n");
    for(i=1;i<=n;i++)
    {
        if(srmark[i])
        {
            printf("%d-%s ",i,player[i].name);
        }
    }
    printf("7-取消\n");
    inputf(k);
    while(k<=0||k>7||((!(*(srmark+k)))&&k!=7))
    {
        inputf(k);
    }
    if(k==7)
    {
        return ;
    }
    recover(k,player[j].attack);
    roundflag=1;
}
void ttable(int j)
{
    if(!map[px-1][py])
    {
        printf("1-↑ ");
        tmark[1]=1;
        mspeed[1]++;
        if((player[j].p==4||player[j].movespeed)&&!map[px-2][py])
        {
            mspeed[1]++;
            if(player[j].p==4&&player[j].movespeed&&!map[px-3][py])
            {
                mspeed[1]++;
                if(player[j].movespeed==2&&!map[px-4][py])
                mspeed[1]++;
            }
        }
    }
    if(!map[px+1][py])
    {
        printf("2-↓ ");
        tmark[2]=1;
        mspeed[2]++;
        if((player[j].p==4||player[j].movespeed)&&!map[px+2][py])
        {
            mspeed[2]++;
            if(player[j].p==4&&player[j].movespeed&&!map[px+3][py])
            {
                mspeed[2]++;
                if(player[j].movespeed==2&&!map[px+4][py])
                mspeed[2]++;
            }
        }
    }
    if(!map[px][py-1])
    {
        printf("3-← ");
        tmark[3]=1;
        mspeed[3]++;
        if((player[j].p==4||player[j].movespeed)&&!map[px][py-2])
        {
            mspeed[3]++;
            if(player[j].p==4&&player[j].movespeed&&!map[px][py-3])
            {
                mspeed[3]++;
                if(player[j].movespeed==2&&!map[px][py-4])
                mspeed[3]++;
            }
        }
    }
    if(!map[px][py+1])
    {
        printf("4-→ ");
        tmark[4]=1;
        mspeed[4]++;
        if((player[j].p==4||player[j].movespeed)&&!map[px][py+2])
        {
            mspeed[4]++;
            if(player[j].p==4&&player[j].movespeed&&!map[px][py+3])
            {
                mspeed[4]++;
                if(player[j].movespeed==2&&!map[px][py+4])
                mspeed[4]++;
            }
        }
    }
    if(player[j].p==2||player[j].d_move)
    {
        if(!map[px-1][py-1])
        {
            printf("5-↖ ");
            tmark[5]=1;
            mspeed[5]++;
            if(player[j].movespeed&&!map[px-2][py-2])
            {
                mspeed[5]++;
                if(player[j].movespeed==2&&!map[px-3][py-3])
                mspeed[5]++;
            }
        }
        if(!map[px-1][py+1])
        {
            printf("6-↗ ");
            tmark[6]=1;
            mspeed[6]++;
            if(player[j].movespeed&&!map[px-2][py+2])
            {
                mspeed[6]++;
                if(player[j].movespeed==2&&!map[px-3][py+3])
                mspeed[6]++;
            }
        }
        if(!map[px+1][py-1])
        {
            printf("7-↙ ");
            tmark[7]=1;
            mspeed[7]++;
            if(player[j].movespeed&&!map[px+2][py-2])
            {
                mspeed[7]++;
                if(player[j].movespeed==2&&!map[px+3][py-3])
                mspeed[7]++;
            }
        }
        if(!map[px+1][py+1])
        {
            printf("8-↘ ");
            tmark[8]=1;
            mspeed[8]++;
            if(player[j].movespeed&&!map[px+2][py+2])
            {
                mspeed[8]++;
                if(player[j].movespeed==2&&!map[px+3][py+3])
                mspeed[8]++;
            }
        }
    }
}
void transform(int j)
{
    int k,l;
    memset(tmark,0,sizeof(tmark));
    memset(mspeed,0,sizeof(mspeed));
    psc();
    printf("请选择你想移动的方向\n");
    ttable(j);
    printf("9-取消\n");
    k=getch()-'0';
    while(k<=0||k>9||(!(*(tmark+k))&&k!=9))
    {
        k=getch()-'0';
    }
    if(k==9)
    return ;
    if(mspeed[k]==1)
    l=1;
    else
    {
        psc();
        printf("请输入移动的步数，9-取消\n"); 
        l=getch()-'0';
        while((l<=0||l>mspeed[k])&&l!=9)
        {
            l=getch()-'0';
        }
        if(l==9)
        return ;
    }
    map[px][py]=0;
    switch(k)
    {
        case 1:px-=l;break;
        case 2:px+=l;break;
        case 3:py-=l;break;
        case 4:py+=l;break;
        case 5:px-=l;py-=l;break;
        case 6:px-=l;py+=l;break;
        case 7:px+=l;py-=l;break;
        case 8:px+=l;py+=l;break;
    }
    map[px][py]=j;
    roundflag=1;
}
void data_save()
{
    FILE* fp;
    int i;
    fp=fopen(input,"w");
    fprintf(fp,"%d\n",n);
    for(i=1;i<=n;i++)
    {
        fprintf(fp,"%s\n",player[i].name);
        fprintf(fp,"%d\n",player[i].p);
        fprintf(fp,"%d\n",player[i].attack);
        fprintf(fp,"%d\n",player[i].mattack);
        fprintf(fp,"%d\n",player[i].maxhp);
        fprintf(fp,"%d\n",player[i].range);
        fprintf(fp,"%d\n",player[i].movespeed);
        fprintf(fp,"%d\n",player[i].d_attack);
        fprintf(fp,"%d\n",player[i].d_move);
        fprintf(fp,"%d\n",player[i].multi_recover);
        fprintf(fp,"%d\n",player[i].p_round);
        fprintf(fp,"%d\n",player[i].lv);
    }
    fclose(fp);
}
void save()
{
    FILE* fp;
    int k;
    while(1)
    {
        psc();
        printf("请输入档案名称，输入\"/back\"返回：\n");
        memset(input,0,sizeof(input)); 
        scanf("%s",input);
        if(!strcmp(input,"/back"))
        return ;
        k=strlen(input);
        if(k>20)
        {
            psc();
            printf("输入名称过长！");
            getch();
            continue;
        }
        strcat(input,".wwd");
        if(fp=fopen(input,"r"))
        {
            psc();
            printf("确定要覆盖存档？Y/N");
            k=getch();
            while(k!='n'&&k!='N'&&k!='y'&&k!='Y') k=getch();
            if(k=='n'||k=='N')
            continue;
        }
        if(fp) fclose(fp);
        psc();
        printf("正在存档中，请不要关闭电源...");
        data_save();
        wait(10000);
        psc();
        printf("存档完毕！");
        getch();
        break;
    }
}
void surrender(int j)
{
    int k;
    psc();
    printf("确定要认输？Y/N\n");
    k=getch();
    while(k!='y'&&k!='Y'&&k!='n'&&k!='N')
    {
        k=getch();
    }
    if(k=='n'||k=='N') return ;
    flag=1;
    team[player[j].team]=0;
    roundflag=1;    
}
void move(int j)
{
    int k;
    while(1)
    {
        psc();
        printf("%s要做什么？剩余行动次数：%d\n",player[j].name,player[j].movechance);
        memset(mmark,0,sizeof(mmark));
        if(player[j].p!=6)
        {
             printf("1-攻击 ");
             mmark[1]=1;
        }
        else
        {
            printf("5-单体回复 ");
            mmark[5]=1;
            if(player[j].multi_recover)
            {
                mmark[6]=1;
                printf("6-群体回复 ");
            }
        }
        if(player[j].p==3)
        if(player[j].power==false)
        {
             printf("2-蓄气 ");
             mmark[2]=1;
        }
        else
        {
            printf("3-魔法攻击 ");
            mmark[3]=1;
        }
        if(player[j].p==5) 
        {
            printf("4-剧毒攻击 ");
            mmark[4]=1;
        }
        printf("7-移动 8-存档 9-放弃 0-认输\n");
        mmark[7]=1;
        mmark[8]=1; 
        mmark[9]=1;
        mmark[0]=1;
        inputf(k);
        while(k<0||k>9||(!(*(mmark+k))))
        {
            inputf(k);
        }
        roundflag=0;
        switch(k)
        {
            case 0:surrender(j);break;
            case 1:nattack(j);break;
            case 2:player[j].power=1;roundflag=1;break;
            case 3:mattack(j);break;
            case 4:pattack(j);break;
            case 5:srecover(j);break;
            case 6:mrecover(j);break;
            case 7:transform(j);break;
            case 8:save();break;
            case 9:roundflag=1;break;
        }
        if(roundflag)
        {
            return ;
        }
    }

}
void levelup(int j)
{
    int k;
    player[j].lv++;
    memset(lmark,0,sizeof(lmark));
    psc();
    printf("请选择升级项目\n");
    if((player[j].p==1&&player[j].attack<6)||(player[j].p>1&&player[j].p<7&&player[j].attack<3))
    {
        if(player[j].p!=6)
        printf("1-攻击力 ");
        else
        printf("1-回复力 ");
        lmark[1]=1;
    }
    if((player[j].p==2&&player[j].range<4)||(player[j].p==3&&!player[j].range))
    {
        if(player[j].p==2)
        printf("2-攻击距离 ");
        else
        printf("2-魔法距离 ");
        lmark[2]=1;
    }
    if(player[j].p!=2&&player[j].d_attack==false)
    {
        if(player[j].p!=6)
        printf("3-斜角攻击 ");
        else
        printf("3-斜角回复 "); 
        lmark[3]=1;
    }
    if(player[j].p==3&&player[j].mattack<2)
    {
        printf("4-魔法攻击力 ");
        lmark[4]=1;
    }
    if(player[j].p==6&&player[j].multi_recover==false)
    {
        printf("5-群体回复 ");
        lmark[5]=1;
    }
    if(player[j].p==5&&player[j].p_round<3)
    {
        printf("6-中毒回合 ");
        lmark[6]=1;
    }
    if((player[j].p==1&&!player[j].movespeed)||(player[j].p==4&&player[j].movespeed<2))
    {
        printf("7-移动距离 ");
        lmark[7]=1;
    }
    if((player[j].p==4)&&player[j].d_move==false)
    {
        printf("8-斜角移动 ");
        lmark[8]=1;
    }
    if((player[j].p==6&&player[j].maxhp<24)||(player[j].maxhp<20))
    {
        printf("9-HP ");
        lmark[9]=1; 
    }
    printf("\n"); 
    inputf(k);
    if(k<=0||k>9)
    {
        return ;
    }
    if(!lmark[k])
    {
        return ;
    }
    switch(k)
    {
        case 1:player[j].attack++;break;
        case 2:player[j].range++;break;
        case 3:player[j].d_attack=true;break;
        case 4:player[j].mattack++;break;
        case 5:player[j].multi_recover=true;break;
        case 6:player[j].p_round++;break;
        case 7:player[j].movespeed++;break;
        case 8:player[j].d_move=true;break;
        case 9:player[j].maxhp+=2;break;
    }
    lflag=1;
}
void game_start()
{
    srand((unsigned)time(NULL));
    int i,j,k,l,m;
    while(1)
    {
        make_team();
        system("cls");
        printf("随机分配位置中，请稍候……");
        wait(1000);
        reset();
        psc();
        printf("位置分配完毕，请按任意键继续……");
        getch();
        flag=0;
        while(1)
        {
            k=randomselect();
            m=livenum-k;
            for(i=1;i<=k;i++)
            {
                for(j=1;j<=n;j++)
                if(mark[j]==i) break;
                for(l=1;l<=m;l++)
                {
                    move(j);
                    player[j].movechance--;
                    if(flag)
                    break;
                }
                if(flag)
                break;
            }
            if(!flag)
            for(i=1;i<=n;i++)
            {
                if(player[i].poison)
                {
                    player[i].poison--;
                    player[i].hp--;
                    deathjudge(i);
                }
            }
            if(flag)
            {
                psc();
                l=team[1]?1:2;
                printf("队伍%d获得胜利！",l);
                getch();
                for(i=1;i<=n;i++)
                {
                    if(player[i].team==l&&player[i].lv<10)
                    {
                        lflag=0;
                        psc();
                        printf("玩家%s升级！",player[i].name);
                        getch();
                        while(1)
                        {
                            levelup(i);
                            if(lflag)
                            break; 
                        }
                    }
                }
                break;
            }
        }
    }
}
void game_intitialize()
{
    int i;
    srand((unsigned)time(NULL));
    system("cls");
    printf("请输入玩家人数：");
    while(inputff(n),(n<=1||n>6))
    {
        printf("游戏人数2~6人，请重新输入："); 
    }
    system("cls");
    printf("请输入各玩家名称(仅限一个字)\n");
    for(i=1;i<=n;i++)
    {
        printf("玩家%d：",i);
        scanf("%s",player[i].name);
        if(!player[i].name[1])
        player[i].name[1]=' ';
        player[i].name[2]=0;
    }
    system("cls");
    choose_profession();
    game_start();
}
void data_load()
{
    FILE* fp;
    int i;
    fp=fopen(input,"r");
    fscanf(fp,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(fp,"%s",&player[i].name);
        fscanf(fp,"%d",&player[i].p);
        fscanf(fp,"%d",&player[i].attack);
        fscanf(fp,"%d",&player[i].mattack);
        fscanf(fp,"%d",&player[i].maxhp);
        fscanf(fp,"%d",&player[i].range);
        fscanf(fp,"%d",&player[i].movespeed);
        fscanf(fp,"%d",&player[i].d_attack);
        fscanf(fp,"%d",&player[i].d_move);
        fscanf(fp,"%d",&player[i].multi_recover);
        fscanf(fp,"%d",&player[i].p_round);
        fscanf(fp,"%d",&player[i].lv);
    }
    fclose(fp);
}
void load()
{
    FILE* fp;
    int k,i,nn;
    struct abcd temp;
    while(1)
    {
        system("cls");
        printf("请输入档案名称，输入\"/back\"返回：\n");
        memset(input,0,sizeof(input)); 
        scanf("%s",input);
        if(!strcmp(input,"/back"))
        return ;
        k=strlen(input);
        if(k>20)
        {
            system("cls");
            printf("输入名称过长！");
            getch();
            continue;
        }
        strcat(input,".wwd");
        fp=fopen(input,"r");
        if(fp==NULL)
        {
            system("cls");
            printf("没有找到档案，请重新输入！");
            fclose(fp);
            getch();
            continue;
        }
        fscanf(fp,"%d",&nn);
        for(i=1;i<=nn;i++)
        {
            fscanf(fp,"%s",&temp.name);
            fscanf(fp,"%d",&temp.p);
            fscanf(fp,"%d",&temp.attack);
            fscanf(fp,"%d",&temp.mattack);
            fscanf(fp,"%d",&temp.maxhp);
            fscanf(fp,"%d",&temp.range);
            fscanf(fp,"%d",&temp.movespeed);
            fscanf(fp,"%d",&temp.d_attack);
            fscanf(fp,"%d",&temp.d_move);
            fscanf(fp,"%d",&temp.multi_recover);
            fscanf(fp,"%d",&temp.p_round);
            fscanf(fp,"%d",&temp.lv);
            printf("玩家%d:%s Lv.%d %s HP:%d ",i,temp.name,temp.lv,pname[temp.p],temp.maxhp);
            if(temp.p!=6)
            printf("攻击力:%d ",temp.attack);
            else
            printf("回复力:%d ",temp.attack);
            if(temp.p==3)
            printf("魔法攻击力:%d ",temp.mattack+2);
            printf("\n");
            switch(temp.p)
            {
                case 1:printf("斜角攻击:%s 移动距离:%d\n",cbool[temp.d_attack],temp.movespeed+1);break;
                case 2:printf("攻击距离:%d\n",temp.range+2);break;
                case 3:printf("斜角攻击:%s 魔法距离:%d\n",cbool[temp.d_attack],temp.range+2);break;
                case 4:printf("斜角攻击:%s 移动距离:%d 斜角移动:%s\n",cbool[temp.d_attack],temp.movespeed+2,cbool[temp.d_move]);break;
                case 5:printf("中毒回合:%d 斜角攻击:%s\n",temp.p_round+2,cbool[temp.d_attack]);break;
                case 6:printf("斜角回复:%s 群体回复:%s\n",cbool[temp.d_attack],cbool[temp.multi_recover]);break;
            }

        }
        fclose(fp);
        printf("确定要从这个档案开始游戏？Y/N");
        k=getch();
        while(k!='n'&&k!='N'&&k!='y'&&k!='Y') k=getch();
        if(k=='n'||k=='N')
        continue;
        system("cls");
        printf("正在读档中，请稍候...");
        data_load();
        wait(10000);
        system("cls");
        printf("读档完毕！");
        getch();
        game_start();
        break;
    }

}
int main()
{
    int k;
    mmflag=1;
    pmm();
    while(1)
    {

        k=getch();
        if(k==-32)
        k=getch();
        if(k==72)
        {
            mmflag=(mmflag+2)%4+1;
            pmm();
            continue;
        }
        if(k==80)
        {
            mmflag=(mmflag)%4+1;
            pmm();
            continue;
        }
        if(k==122||k==90)
        {
            switch(mmflag)
            {
                case 1:game_intitialize();break;
                case 2:load();break;
//                case 3:game_descibe();
                case 4:return 0;break;
            }
            pmm();
        }
    }

}

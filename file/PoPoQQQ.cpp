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
    "","սʿ","������","ħ��ʦ","��ʿ","��ʦ","��ʦ"
};
char pdescribe[][200]={
    "",
    "սʿ����ս��ְҵ��ӵ��ǿ����������������\n����������������+1",
    "�����֣�Զ����ְҵ�����м�ǿ��Զ���������\n�������������ԶԽ��߹������һ�񹥻�������б���ƶ����޷�������",
    "ħ��ʦ��ħ����ְҵ����������ħ���;�����\n�������������Խ�����������������Ե���һ�ι�����Ҳ��������ʩ����������˺�",
    "��ʿ���г̽�սְҵ�����о�����װ�������ʵ�����\n�����������ƶ��ٶ�+1����������+1",
    "��ʦ��������ְҵ�����пֲ�����������\n������������������+1���������������1�غ϶�Ч�����ж��Ķ���ÿ�غ�����-1",
    "��ʦ���ظ���ְҵ�����и߳��Ļظ�����\n�������������Իظ�������Χ�ڵ��κ��˵�1�������������Ч�����޷�����"
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
        printf("�����%sѡ��ְҵ:\n",player[t].name);
        for(j=1;j<=6;j++)
        {
            if(!profession[j])
            {
                printf("%d-%s ",j,pname[j]);
            }
        }
        printf("7-ְҵ����\n");
        inputf(m);
        while(m<1||m>6||(*(profession+m)))
        {
            if(m==7)
            {
                system("cls");
                printf("����������鿴��ְҵ\n");
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
                printf("��ѡ��ְҵ:\n");
                for(j=1;j<=6;j++)
                {
                    if(!profession[j])
                    {
                        printf("%d-%s ",j,pname[j]);
                    }
                }   
                printf("7-ְҵ����\n");
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
        printf("%s ����%d Lv.%d %s HP:%d/%d",player[i].name,player[i].team,player[i].lv,pname[player[i].p],player[i].hp,player[i].maxhp);
        if(player[i].p!=6)
        printf(" ��������");
        else
        printf(" �ظ�����"); 
        printf("%d",player[i].attack);
        if(player[i].p==3)
        printf(" ħ����������%d",player[i].mattack+2);
        if(!deathmark[i])
        {
            if(player[i].power) printf(" ����");
            if(player[i].poison) printf(" ��");
        }
        else
        printf(" ����");
        printf("\n");
    }
    memset(produced_map,0,sizeof(produced_map));
    for(i=1;i<=15;i++)
    {
        strcat(produced_map[i],"                    ");
        for(j=1;j<=20;j++)
        {
            if(!map[i][j]) strcat(produced_map[i],"��");
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
    strcpy(produced_menu[1],"�X�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�[");
    strcpy(produced_menu[2],"�d�p�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�p�g");
    strcpy(produced_menu[3],"�d�g                                                                        �d�g");
    strcpy(produced_menu[4],"�d�g                                                                        �d�g");
    strcpy(produced_menu[6],"�d�g                      ��ӭ���� �������� Ver 1.0.0!                      �d�g");
    strcpy(produced_menu[5],"�d�g                                                                        �d�g");
    strcpy(produced_menu[7],"�d�g                                                                        �d�g");
    strcpy(produced_menu[8],"�d�g                                                                        �d�g");
    strcpy(produced_menu[9],"�d�g                                                                        �d�g");
    if(mmflag==1)
    {
        strcpy(produced_menu[10],"�d�g                           ��                                           �d�g");
        strcpy(produced_menu[11],"�d�g                           �� ����Ϸ                                    �d�g");
    }
    else
    {
        strcpy(produced_menu[10],"�d�g                                                                        �d�g");
        strcpy(produced_menu[11],"�d�g                              ����Ϸ                                    �d�g");
    }
    strcpy(produced_menu[12],"�d�g                                                                        �d�g");
    if(mmflag==2)
    {
        strcpy(produced_menu[13],"�d�g                           ��                                           �d�g");
        strcpy(produced_menu[14],"�d�g                           ��������Ϸ                                   �d�g");
    }
    else
    {
        strcpy(produced_menu[13],"�d�g                                                                        �d�g");
        strcpy(produced_menu[14],"�d�g                             ������Ϸ                                   �d�g");
    }
    strcpy(produced_menu[15],"�d�g                                                                        �d�g");
    if(mmflag==3)
    {
        strcpy(produced_menu[16],"�d�g                           ��                                           �d�g");
        strcpy(produced_menu[17],"�d�g                           ����Ϸ����                                   �d�g");
    }
    else
    {
        strcpy(produced_menu[16],"�d�g                                                                        �d�g");
        strcpy(produced_menu[17],"�d�g                             ��Ϸ����                                   �d�g");
    }
    strcpy(produced_menu[18],"�d�g                                                                        �d�g");
    if(mmflag==4)
    {
        strcpy(produced_menu[19],"�d�g                           ��                                           �d�g");
        strcpy(produced_menu[20],"�d�g                           ��  �˳�                                     �d�g");
    }
    else
    {
        strcpy(produced_menu[19],"�d�g                                                                        �d�g");
        strcpy(produced_menu[20],"�d�g                               �˳�                                     �d�g");
    }
    strcpy(produced_menu[21],"�d�g                                                                        �d�g");
    strcpy(produced_menu[22],"�d�g                                                            ����:PoPoQQQ�d�g");
    strcpy(produced_menu[23],"�d�p�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�j�p�g");
    strcpy(produced_menu[24],"�^�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�a");
    strcpy(produced_menu[25],"���������� �������ƶ���� Z��ȷ��");
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
    printf("ϵͳ�Զ�����У����Եȡ���\n");
    wait(1000);
    divide();
    system("cls");
    printf("�����ϣ���������:\n");
    for(i=1;i<=n;i++)
    {
        printf("%s:����%d\n",player[i].name,player[i].team);
    }
    printf("�밴�������������\n");
    getch();
}
int randomselect()
{
    srand((unsigned)time(NULL));
    int i,j,k,l;
    psc();
    printf("ϵͳ�Զ���ȭ�У����Ժ򡭡�");
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
    printf("��ò�ȭʤ����");
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
        printf("���%s������",player[j].name);
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
        printf("û�пɹ����Ķ���");
        getch();
        return ;
    }
    psc();
    printf("��ѡ�񹥻��Ķ���\n");
    for(i=1;i<=n;i++)
    {
        if(nmark[i])
        {
            printf("%d-%s ",i,player[i].name);
        }
    }
    printf("7-ȡ��\n");
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
        printf("û�пɹ����Ķ���");
        getch();
        return ;
    }
    psc(); 
    printf("��ѡ�񹥻���Ŀ�꣡\n");
    for(i=1;i<=n;i++)
    {
        if(mamark[i])
        {
            printf("%d-%s ",i,player[i].name);
        }
    }
    printf("7-ȡ��\n");
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
        printf("û�пɹ����Ķ���");
        getch();
        return ;
    }
    psc();
    printf("��ѡ�񹥻���Ŀ�꣡\n");
    for(i=1;i<=n;i++)
    {
        if(pmark[i])
        {
            printf("%d-%s ",i,player[i].name);
        }
    }
    printf("7-ȡ��\n");
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
    printf("��ѡ��ظ���Ŀ�꣡\n");
    for(i=1;i<=n;i++)
    {
        if(srmark[i])
        {
            printf("%d-%s ",i,player[i].name);
        }
    }
    printf("7-ȡ��\n");
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
        printf("1-�� ");
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
        printf("2-�� ");
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
        printf("3-�� ");
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
        printf("4-�� ");
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
            printf("5-�I ");
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
            printf("6-�J ");
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
            printf("7-�L ");
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
            printf("8-�K ");
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
    printf("��ѡ�������ƶ��ķ���\n");
    ttable(j);
    printf("9-ȡ��\n");
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
        printf("�������ƶ��Ĳ�����9-ȡ��\n"); 
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
        printf("�����뵵�����ƣ�����\"/back\"���أ�\n");
        memset(input,0,sizeof(input)); 
        scanf("%s",input);
        if(!strcmp(input,"/back"))
        return ;
        k=strlen(input);
        if(k>20)
        {
            psc();
            printf("�������ƹ�����");
            getch();
            continue;
        }
        strcat(input,".wwd");
        if(fp=fopen(input,"r"))
        {
            psc();
            printf("ȷ��Ҫ���Ǵ浵��Y/N");
            k=getch();
            while(k!='n'&&k!='N'&&k!='y'&&k!='Y') k=getch();
            if(k=='n'||k=='N')
            continue;
        }
        if(fp) fclose(fp);
        psc();
        printf("���ڴ浵�У��벻Ҫ�رյ�Դ...");
        data_save();
        wait(10000);
        psc();
        printf("�浵��ϣ�");
        getch();
        break;
    }
}
void surrender(int j)
{
    int k;
    psc();
    printf("ȷ��Ҫ���䣿Y/N\n");
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
        printf("%sҪ��ʲô��ʣ���ж�������%d\n",player[j].name,player[j].movechance);
        memset(mmark,0,sizeof(mmark));
        if(player[j].p!=6)
        {
             printf("1-���� ");
             mmark[1]=1;
        }
        else
        {
            printf("5-����ظ� ");
            mmark[5]=1;
            if(player[j].multi_recover)
            {
                mmark[6]=1;
                printf("6-Ⱥ��ظ� ");
            }
        }
        if(player[j].p==3)
        if(player[j].power==false)
        {
             printf("2-���� ");
             mmark[2]=1;
        }
        else
        {
            printf("3-ħ������ ");
            mmark[3]=1;
        }
        if(player[j].p==5) 
        {
            printf("4-�綾���� ");
            mmark[4]=1;
        }
        printf("7-�ƶ� 8-�浵 9-���� 0-����\n");
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
    printf("��ѡ��������Ŀ\n");
    if((player[j].p==1&&player[j].attack<6)||(player[j].p>1&&player[j].p<7&&player[j].attack<3))
    {
        if(player[j].p!=6)
        printf("1-������ ");
        else
        printf("1-�ظ��� ");
        lmark[1]=1;
    }
    if((player[j].p==2&&player[j].range<4)||(player[j].p==3&&!player[j].range))
    {
        if(player[j].p==2)
        printf("2-�������� ");
        else
        printf("2-ħ������ ");
        lmark[2]=1;
    }
    if(player[j].p!=2&&player[j].d_attack==false)
    {
        if(player[j].p!=6)
        printf("3-б�ǹ��� ");
        else
        printf("3-б�ǻظ� "); 
        lmark[3]=1;
    }
    if(player[j].p==3&&player[j].mattack<2)
    {
        printf("4-ħ�������� ");
        lmark[4]=1;
    }
    if(player[j].p==6&&player[j].multi_recover==false)
    {
        printf("5-Ⱥ��ظ� ");
        lmark[5]=1;
    }
    if(player[j].p==5&&player[j].p_round<3)
    {
        printf("6-�ж��غ� ");
        lmark[6]=1;
    }
    if((player[j].p==1&&!player[j].movespeed)||(player[j].p==4&&player[j].movespeed<2))
    {
        printf("7-�ƶ����� ");
        lmark[7]=1;
    }
    if((player[j].p==4)&&player[j].d_move==false)
    {
        printf("8-б���ƶ� ");
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
        printf("�������λ���У����Ժ򡭡�");
        wait(1000);
        reset();
        psc();
        printf("λ�÷�����ϣ��밴�������������");
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
                printf("����%d���ʤ����",l);
                getch();
                for(i=1;i<=n;i++)
                {
                    if(player[i].team==l&&player[i].lv<10)
                    {
                        lflag=0;
                        psc();
                        printf("���%s������",player[i].name);
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
    printf("���������������");
    while(inputff(n),(n<=1||n>6))
    {
        printf("��Ϸ����2~6�ˣ����������룺"); 
    }
    system("cls");
    printf("��������������(����һ����)\n");
    for(i=1;i<=n;i++)
    {
        printf("���%d��",i);
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
        printf("�����뵵�����ƣ�����\"/back\"���أ�\n");
        memset(input,0,sizeof(input)); 
        scanf("%s",input);
        if(!strcmp(input,"/back"))
        return ;
        k=strlen(input);
        if(k>20)
        {
            system("cls");
            printf("�������ƹ�����");
            getch();
            continue;
        }
        strcat(input,".wwd");
        fp=fopen(input,"r");
        if(fp==NULL)
        {
            system("cls");
            printf("û���ҵ����������������룡");
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
            printf("���%d:%s Lv.%d %s HP:%d ",i,temp.name,temp.lv,pname[temp.p],temp.maxhp);
            if(temp.p!=6)
            printf("������:%d ",temp.attack);
            else
            printf("�ظ���:%d ",temp.attack);
            if(temp.p==3)
            printf("ħ��������:%d ",temp.mattack+2);
            printf("\n");
            switch(temp.p)
            {
                case 1:printf("б�ǹ���:%s �ƶ�����:%d\n",cbool[temp.d_attack],temp.movespeed+1);break;
                case 2:printf("��������:%d\n",temp.range+2);break;
                case 3:printf("б�ǹ���:%s ħ������:%d\n",cbool[temp.d_attack],temp.range+2);break;
                case 4:printf("б�ǹ���:%s �ƶ�����:%d б���ƶ�:%s\n",cbool[temp.d_attack],temp.movespeed+2,cbool[temp.d_move]);break;
                case 5:printf("�ж��غ�:%d б�ǹ���:%s\n",temp.p_round+2,cbool[temp.d_attack]);break;
                case 6:printf("б�ǻظ�:%s Ⱥ��ظ�:%s\n",cbool[temp.d_attack],cbool[temp.multi_recover]);break;
            }

        }
        fclose(fp);
        printf("ȷ��Ҫ�����������ʼ��Ϸ��Y/N");
        k=getch();
        while(k!='n'&&k!='N'&&k!='y'&&k!='Y') k=getch();
        if(k=='n'||k=='N')
        continue;
        system("cls");
        printf("���ڶ����У����Ժ�...");
        data_load();
        wait(10000);
        system("cls");
        printf("������ϣ�");
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

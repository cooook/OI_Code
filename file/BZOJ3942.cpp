#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#define MAXN 1000005
using namespace std;
 
 
int nxt[MAXN],top,len,s[MAXN];
char stack[MAXN];
string a,b;
 
void KMP(){
    int fix=0;
     
    for(int i=1;a[i];i++){
        while(fix && a[fix] != a[i])
            fix=nxt[fix-1];
         
        if(a[fix] == a[i])
            fix++;
             
        nxt[i]=fix;
    }
    fix=0;
    for(int i=0;b[i];i++){
        fix=s[top];
        stack[++top]=b[i];
        while(fix && a[fix] != stack[top])
            fix=nxt[fix-1];
        if(a[fix] == stack [top])
            fix++;
        s[top]=fix;
        if(fix == len){
            fix=nxt[fix-1];
            top-=len;
        }
    }
    for(int i=1;i<=top;i++)
        printf("%c",stack[i]);
}
 
int main(){
    cin>>b>>a;
    len=a.size();
    KMP();
}
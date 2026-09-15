/*
題目描述 給出一組包含 m 個不等式，有 n 個未知數的形式如：

xc1 - xc'1 <= y1 xc2 - xc'2 <= y2 ... xcm - xc'm <= ym

的不等式組，求任意一組滿足這個不等式組的解。

輸入格式 第一行為兩個正整數 n, m，代表未知數的數量和不等式的數量。 接下來 m 行，每行包含三個整數 c, c', y，代表一個不等式 xc - xc' <= y。

輸出格式 一行，n 個數，表示 x1, x2 ... xn 的一組可行解，如果有多組解，請輸出任意一組，無解請輸出 NO。
*/
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include <queue>
#include <cstring>
using namespace std;
#define N 500010
struct nice{
    int to,next,weight;
}edges[N << 1];
int n,m,t;
int head[N],indexx = 1;
void wirte(int x,int y,int z)
{
    edges[indexx].weight = z;
    edges[indexx].to = y;
    edges[indexx].next = head[x];
    head[x] = indexx++;
}

queue<int> q;

int lenght[N],check[N],check_times[N];
bool spfa(){
    memset(check, 0, sizeof(check));
    memset(check_times, 0, sizeof(check_times));
    memset(lenght,0x3f,sizeof(lenght));
    lenght[0] = 0;
    check[0] = 1;
    q.push(0);
    while(!q.empty())
    {
        int now = q.front();
        q.pop();
        check[now] = 0;
        for(int i = head[now]; i; i = edges[i].next)
        {
            int next = edges[i].to;
            if(lenght[next]>lenght[now]+edges[i].weight)
            {
                lenght[next]=lenght[now]+edges[i].weight;
                if(!check[next])
                {
                    if(++check_times[next]>=n+1) return false;
                    check[next] = 1;
                    q.push(next);
                }
            }
        }
    }
    return true;
}


int main(){
    memset(head, 0, sizeof(head));
    for(int i=0;i<(N << 1);i++) edges[i].next=0;
    indexx = 1;
    cin >> n >> m;
    for(int i = 0;i<m;i++)
    {
        int a,b,c;
        cin >> a >> b >> c;
        wirte(b, a, c);
    }
    for(int i=1;i<=n;i++)
    {
        wirte(0, i, 0);
    }
    if(!spfa())
    cout << "NO"<<endl;
    else
    {
        for(int i=1;i<=n;i++)
        {
        cout << lenght[i]<<' ';
        }
    }
    
    return 0;
}

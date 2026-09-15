#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<math.h>
#include<string.h>
using namespace std;
#define N 500010
struct nice{
    int to,next;
}edges[N << 1];
int n,m;
int head[N],indexx = 1;
void wirte(int x,int y)
{
    edges[indexx].to = y;
    edges[indexx].next = head[x];
    head[x] = indexx++;
}
int dfn[N],low[N],ans[N],num,sum = 0;
void tarjan(int now,bool root){
    int ch = 0;
    dfn[now] = low[now] = ++num;
    for(int i = head[now]; i; i = edges[i].next){
        int v = edges[i].to;
        if(!dfn[v])
        {
        tarjan(v,0);
        low[now] = min(low[v],low[now]);
        if(low[v]>=dfn[now] && !root)
        {
        ans[now] = 1;
        }
        if(root)ch++;
        }
        else low[now] = min(dfn[v],low[now]);
    }
    if(root && ch>=2)
    {
    ans[now] = 1;
    return;
    }
    return;
}

int main()
{
cin >> n >> m;
for(int i = 0;i<m;i++)
{
    int x,y;
    scanf("%d%d",&x,&y);
    wirte(x,y);
    wirte(y,x);
}
for(int i = 1;i<=n;i++)
{
    if(!dfn[i])tarjan(i,1);
}
for(int i = 1;i<=n;i++)
{
    if(ans[i])sum++;
}
cout << sum<<endl;
for(int i = 1;i<=n;i++)
{
    if(ans[i])cout << i <<' ';
}

}


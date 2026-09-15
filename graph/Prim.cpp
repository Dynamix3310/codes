#include<iostream>
#include<algorithm>
#include<stdio.h>
#include <queue>
using namespace std;
typedef long long ll;
#define N 500010
struct nice{
    int to,next,weight;
}edges[N << 1];
int n,m;
int b,cost[N];
int head[N],index = 1;
void wirte(int x,int y,int z)
{
    edges[index].weight = z;
    edges[index].to = y;
    edges[index].next = head[x];
    head[x] = index++;
    //cout << index-1 << ' ' << edges[index-1].to << ' ' << edges[index-1].next<< endl;
}

int lenght[N],check[N],ass;
bool prim(){
    ass = 0;
    for(int i = 2;i<=n;i++)lenght[i] = 0x7fffffff;
    for(int i = head[1]; i; i = edges[i].next)
    {
        lenght[edges[i].to] = min(lenght[edges[i].to],edges[i].weight);
    }
    int times = 0;
    check[1] = 1;
    while(++times<n)
    {
        int min_len = 0x7fffffff;
        int now = -1;
        for(int i = 1; i<=n; i++)
        {
            if(!check[i] && lenght[i]<min_len)
            {
                min_len = lenght[i];
                now = i;
            }
        }
        if(now == -1)return false;
        //cout << min_len << " " << now << endl;
        ass+=min_len;
        check[now] = 1;
        for(int i = head[now]; i; i = edges[i].next)
        {
            int next = edges[i].to;
            if(!check[next] && lenght[next]>edges[i].weight)
                lenght[next] = edges[i].weight;
        }
    }
    return true;
}


int main(){
cin >> n >> m;
for(int i = 0;i<m;i++)
{
    int x,y,z;
    scanf("%d%d%d",&x,&y,&z);
    wirte(x,y,z);
    wirte(y,x,z);
}
if(prim())
{
    cout << ass<<endl;
}else cout << "orz"<<endl;
    return 0;
    }


#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define N 500010
struct nice{
    int to,next;
}edges[N << 1];

int n;
int head[N],index = 1;
void wirte(int x,int y)
{
    edges[index].to = y;
    edges[index].next = head[x];
    head[x] = index++;
}
int d[N],size[N];

void dfs_size(int now){
    size[now] = 1;
    for(int i = head[now]; i; i = edges[i].next){
        int v = edges[i].to;
        if(d[v]) continue;
        d[v] = d[now]+1;
        dfs_size(v);
        size[now] += size[v];
        //cout << now<<' ' << size[now] << endl;
    }
}
int f[N];
void dfs_far(int now, int father)
{
    f[now] = f[father]+n-2*size[now];
    //cout << now<<' '<<f[father] <<' ' << n << ' ' << size[now]<<' '<<f[now]<<endl;
    for(int i = head[now]; i; i = edges[i].next){
        int v = edges[i].to;
        if(v!=father) 
            dfs_far(v,now);
    }
}



int main(){

    scanf("%d",&n);
    for(int i =0;i<n-1;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        wirte(x,y);
        wirte(y,x);
    }
    d[1] = 1;
    dfs_size(1);
    int max_size = 0,max_id;
    for(int i = 1;i<=n;i++) max_size+=d[i];
    max_size-=n;
    //cout << "DDDDDDD" << max_size << endl;
    f[1] = max_size;
    for(int i = head[1]; i; i = edges[i].next){
        int v = edges[i].to;
        dfs_far(v,1);
    }
    for(int i = 2;i<=n;i++)
    {
        if(f[i]<max_size) max_size = f[i],max_id = i;
    }
    printf("%d %d",max_id,max_size);

    return 0;
}


#include<iostream>
#include<algorithm>
#include<stdio.h>
#include <queue>
#include<string.h>
using namespace std;
typedef long long ll;
#define N 500010
struct nice{
    int to,next;
    ll weight;
}edges[N << 1];

struct NICE{
    int u,v;
    ll weight;
}edge[N << 1];
int n,m;
ll fa[N],w[N][32],ww[N][32];

bool cmp(NICE a,NICE b)
{
    return a.weight<b.weight;
}

int find(int x)
{
    while(x!=fa[x]) x = fa[x] = fa[fa[x]];
    return x;
}

int head[N],indexx = 1;
void wirte(int x,int y,ll z)
{
    edges[indexx].weight = z;
    edges[indexx].to = y;
    edges[indexx].next = head[x];
    head[x] = indexx++;
}

int times = 0;
ll ass = 0;
ll maxw = 0;
void kruskal(){
    sort(edge+1,edge+m+1,cmp);
    for(int i = 1;i<=m;i++)
    {
        int eu = find(edge[i].u),ev = find(edge[i].v);
        //cout <<find(u) << ' ' << find(v) << ' ' << endl;
        if(eu == ev)continue;
        //cout << "check"<<endl;
        ass+=edge[i].weight;
        maxw = max(maxw,edge[i].weight);
        fa[ev] = eu;
        wirte(edge[i].u,edge[i].v,edge[i].weight);
        wirte(edge[i].v,edge[i].u,edge[i].weight);
        //cout << edge[i].u << ' ' << edge[i].v << ' ' << endl;
        edge[i].u = -1;
        if(++times == n-1)break;
    }
}


int indexxx = 1;
void write(int x,int y,ll z)
{
    edge[indexxx].u = x;
    edge[indexxx].v = y;
    edge[indexxx++].weight = z;
}

int depth[N],f[N][32],check[N];
void dfs(int now,int fa){
    for(int i = 1; i <= 30; i++){
            f[now][i] = f[f[now][i-1]][i-1];
            w[now][i] = max(w[now][i-1],w[f[now][i-1]][i-1]);
            ww[now][i] = max(ww[now][i-1],ww[f[now][i-1]][i-1]);
            if(w[now][i-1] > w[f[now][i-1]][i-1])ww[now][i] = max(ww[now][i],w[f[now][i-1]][i-1]);
            else if(w[now][i-1] < w[f[now][i-1]][i-1])ww[now][i] = max(ww[now][i],w[now][i-1]);
    }
    //cout << now << endl;
    for(int i = head[now]; i; i = edges[i].next){
        int next = edges[i].to;
        if(next!=fa)
        {
            depth[next] = depth[now] + 1;
            f[next][0] = now;
            w[next][0] = edges[i].weight;
            dfs(next,now);
        }
    }
}

int lca(int x,int y)
{
    int ans = 0;
    if(depth[x] < depth[y]) swap(x, y);//x>y
    for(int i = 30; i >= 0; i--)
        if(depth[f[x][i]] >= depth[y])
        {
            x = f[x][i];
        }
    if(x == y) return x;
    for(int i = 30; i >= 0; i--)
        if(f[x][i]!= f[y][i])
        {
            x = f[x][i], y = f[y][i];
        }
    return f[x][0];
}

ll path(int x,int y,ll m)
{
    ll ans = 0;
    for(int i = 30; i >= 0; i--)
        if(depth[f[x][i]] >= depth[y])
        {
            if(m != w[x][i])ans = max(w[x][i],ans);
            else ans = max(ww[x][i],ans);
            //cout << w[x][i] << " " << ww[x][i] << endl;
            x = f[x][i];
        }
    return ans;
}

int main(){
scanf("%d%d",&n,&m);
for(int i = 1;i<=n;i++)
{
    fa[i] = i;  
}
for(int i = 1;i<=m;i++)
{
    int x,y,z;
    scanf("%d%d%d",&x,&y,&z);
    write(x,y,z);
    //cout << x << " " << y << endl;
}
kruskal();
depth[1] = 1;
f[1][0] = 1;
w[1][0] = 0;
ww[1][0] = INT64_MIN;
dfs(1,0);

ll ans = INT64_MAX;
for(int i = 1;i<=m;i++)
{
    if(edge[i].u == -1)continue;
    int LCA = lca(edge[i].u,edge[i].v);
    int maxu = path(edge[i].u,LCA,edge[i].weight);
    int maxv = path(edge[i].v,LCA,edge[i].weight);
    //cout << edge[i].u << " " << edge[i].v << " " <<LCA << ' ' << maxu << ' ' << maxv <<' '<< edge[i].weight << endl;
    ans = min(ans,ass - max(maxu,maxv) + edge[i].weight);
}
cout << ans;
return 0;
}       


Given a directed graph with&nbsp;N&nbsp; vertices and&nbsp;M&nbsp; edges. i\-th edge is&nbsp; (ai,bi).

Calculate the dominator tree of this graph whose root is&nbsp;S.

```cpp=
#include<iostream>
#include<algorithm>
#include<vector>
#include<stdio.h>
using namespace std;
typedef long long ll;
#define N 200005
int n,m,s,dfn[N],tot,End[N];
struct nice{
    int from,to,flag;
}edges[N];

struct DomTree{
    vector<int> g[N],tree[N],rg[N],bucket[N];
    int sdom[N],fa[N],dom[N],idom[N],lable[N];
    int arr[N],rev[N],T = 0;
    void add(int u,int v){
        g[u].push_back(v);
    }
    void init(int n){
        for(int i = 0;i<=n;i++){
            tree[i].clear();g[i].clear();rg[i].clear();bucket[i].clear();
            sdom[i] = 0;fa[i] = 0;dom[i] = 0;idom[i] = 0;lable[i] = 0;
            arr[i] = 0;rev[i] = 0;
        }
        T = 0;
    }
    int Find(int u,int x= 0){
        if(u == idom[u])return x?-1:u;
        int v = Find(idom[u],x+1);
        if(v<0)return u;
        if(sdom[lable[idom[u]]]<sdom[lable[u]])
            lable[u] = lable[idom[u]];
        idom[u] = v;
        return x?v:lable[u];
    }
    void Union(int u,int v){
        idom[v] = u;
    }
    void dfs0(int u){
        T++;arr[u] = T;rev[T] = u;
        lable[T] = T;sdom[T] = T;idom[T] = T;
        for(int i=0;i<g[u].size();i++){
            int w = g[u][i];
            if(!arr[w])dfs0(w),fa[arr[w]] = arr[u];
            rg[arr[w]].push_back(arr[u]);
        }
    }
    void build(int s){
        dfs0(s);
        for(int i=T;i>=1;i--){
            for(int j = 0;j<rg[i].size();j++){
            sdom[i] = min(sdom[i],sdom[Find(rg[i][j])]);
            }
            if(i>1)bucket[sdom[i]].push_back(i);   
            for(int j = 0;j<bucket[i].size();j++){
                int w = bucket[i][j];
                int v = Find(w);
                if(sdom[v] == sdom[w])dom[w]=sdom[w];
                else dom[w] = v;
            }
            if(i>1)Union(fa[i],i);
        }
        for(int i = 2;i<=T;i++){
            if(dom[i]!=sdom[i]){
                dom[i]=dom[dom[i]];
            }
            tree[rev[i]].push_back(rev[dom[i]]);
            tree[rev[dom[i]]].push_back(rev[i]);
        }
    }
};
DomTree DT;
int main(){
    cin >> n >> m >> s;
    DT.init(n);
    for(int i = 1;i<=m;i++){
        int x,y;
        cin >> x >> y;
        edges[i] = nice{x,y,0};
        DT.add(x,y);
    }
    DT.build(s);
    vector<int> p(N,-1);
    p[s] = s;
    for(int i = 2;i<=DT.T;i++)
    {
        int u = DT.rev[i];
        int v = DT.rev[DT.dom[i]];
        p[u] = v;
    }
    for(int i = 0;i<n;i++){
        cout << p[i]<<(i==n-1?"":" ");
    }
    cout << endl;
    return 0;
}

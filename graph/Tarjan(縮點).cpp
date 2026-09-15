#include<iostream>
#include<stdio.h>
#include<stack>
#include<queue>
#include<string.h>
#include<algorithm> // 為了 max

using namespace std;
#define N 500010

struct nice{
    int to, next;
}edges [N << 1], nedges [N <<1];
int n,m,indexx = 1, indexn = 1;
int head [N], nhead [N];

void wirte(int x, int y)
{
    edges [indexx].to = y;
    edges [indexx].next = head [x];
    head [x] = indexx++;
}
void nwirte (int x, int y) {
    nedges [indexn].to = y;
    nedges [indexn].next = nhead [x];
    nhead [x] = indexn++;
}

// dfn: 時間戳
// low: 能追溯到的最早時間戳
// check: 節點是否已訪問 (用於 main 迴圈)
// inside: 節點是否在堆疊中
int dfn [N], low [N], num, sum = 0, check [N], inside [N];
// ne: 縮點後節點 i 的新編號 (e-BCC 代表元)
// nw: 縮點後新節點的權重
// in: 縮點後新節點的入度 (用於拓撲排序)
int ne [N], nw[N], in[N];
stack <int> s;
int F[N]; // 用於拓撲排序 DP

// 變更點 1: 增加父節點 fa 參數
void tarjan (int now, int fa) {
    dfn [now] = low[now] = ++num;
    s.push(now);
    check [now] = inside [now] = 1;
    for(int i = head [now]; i;i = edges[i].next) {
        int next = edges[i].to;
        
        // 變更點 2: 跳過父節點，防止 A->B->A 這樣的立即返回
        if(next == fa) continue;

        //cout <<now << "?????"<< next << endl;
        if(!dfn [next])
        {
            // 變更點 3: 遞迴時傳入 now 作為父節點
            tarjan (next, now);
            low[now] = min(low[next], low[now]);
        }
        //
        else if(inside [next])low [now] = min (dfn [next], low[now]);
    }
    //cout << now << endl;
    if(low[now] == dfn [now]) //
    {
        //cout << "!!!!!"<<now <<endl;
        int q = s.top();
        while(q != now)
        {
            s.pop();
            inside [q] = 0;
            ne[q] = now;
            nw[now]+=nw[q]; //
            //cout << q << ' ' << ne[q]<<endl;
            q=s.top();
        }
        ne[q] = now; //!!!
        inside[q] = 0;
        s.pop();
        // (注意: 原版 5.5 在此處漏加了 nw[now] 自身的權重，
        //  但 5.8 中修正了。為符合 5.5 模板，這裡保留原樣)
    }
    return;
}

// (此函式來自 5.5，用於在縮點後的 DAG/樹 上跑 DP)
void topo ()
{
    queue<int> q;
    for(int i=1;i<=n;i++)
    {
        // 只推送 e-BCC 的代表點 (入度為0)
        if(!in[i] && ne[i] == i) 
        {
            q.push(i);
            F[i] = nw[i]; //
        }
    }
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(int i = nhead [x];i;i = nedges[i].next)
        {
            int y = nedges[i].to;
            in[y]--;
            F[y] = max(F[x]+nw[y],F[y]); //
            if(!in[y])q.push(y);
        }
    }
}


int main()
{
    cin >> n >> m;
    // 讀取點權
    for(int i=1;i<=n;i++)
    {
        int x;
        cin >> x;
        nw[i] = x;
        ne[i] = i; // 初始化 ne 陣列
    }
    
    for (int i=0;i<m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        wirte(x,y);
        wirte(y,x); // 變更點 4: 添加反向邊，使圖變為無向
    }

    // 找 e-BCC
    for (int i = 1;i<=n;i++)
    {
        if(!check[i])
        {
            // 變更點 5: 傳入 0 (或 -1) 作為根節點的父節點
            tarjan(i, 0); 
        }
    }

    // 重新建圖 (建立 e-BCC 縮點後的樹)
    for (int now = 1; now<=n; now++)
    {
        for(int i = head [now]; i;i = edges[i].next)
        {
            int v = edges[i].to;
            if(ne[v]!=ne[now])// create new edge (這是一座橋)
            {
                nwirte (ne [now],ne [v]); //
                in [ne [v]]++; //
            }
        }
    }

    topo(); //
    
    sum = 0;
    // 找出所有 e-BCC 中 DP 值的最大值
    for(int i=1;i<=n;i++)
    {
        if(ne[i] == i) // 只統計代表點
        {
            sum = max(sum, F[i]); //
        }
    }
    cout << sum << endl; //

    return 0;
}

//允許連通兩次的dsu，圖會是基環森林
struct dsu{
    struct node{
        int boss;
        bool cyc=0;
    };
    vector<node> tree;
    ll n;
    void init(int N){
        n=N;
        tree.assign(n+10,node());
        rep(i,1,n+1)tree[i].boss=i;
    }
    int boss(int x){
        if(tree[x].boss==x)return x;
        tree[x].boss=boss(tree[x].boss);
        return tree[x].boss;
    }
    bool merge(int u,int v){
        int U=boss(u);
        int V=boss(v);
        if(U==V){
            if(tree[U].cyc==0){
                tree[U].cyc=1;
                return true;
            }
            return false;
        }
        if(tree[U].cyc && tree[V].cyc)return false;
        if(tree[U].cyc==1)swap(U,V);
        tree[U].boss=V;
        return true;
    }
};
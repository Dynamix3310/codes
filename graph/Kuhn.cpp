struct kuhn{
    vector<vll> graph;
    ll n,m;
    vector<bool> visited;
    vector<bool> tag;
    vll mat;
    int ans=0;
    void init(int N,int M){
        n=N;
        m=M;
        graph.assign(n,vll());
        mat.assign(m,-1);
        tag.assign(n,0);
        ans=0;
    }
    void add_edge(int u,int v){
        graph[u].pb(v);
    }
    bool dfs(int x){
        for(auto u:graph[x]){
            if(visited[u])continue;
            visited[u]=1;                
            if(mat[u]==-1 || dfs(mat[u])){
                mat[u]=x;
                tag[x]=true;
                return true;
            }
        }
        return false;
    }
    void build(){
        rep(i,0,n){
            for(auto u:graph[i]){
                if(mat[u]==-1){
                    mat[u]=i;
                    ans++;
                    tag[i]=1;
                    break;
                }
            }
        }
        rep(i,0,n){
            visited.assign(m,0);
            if(!tag[i] && dfs(i)){
                ans++;
            }
        }
    }
};
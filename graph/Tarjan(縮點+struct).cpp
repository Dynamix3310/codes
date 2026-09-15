struct TarjanSCC{
    int n,timer,scc_cnt;
    vll dfn,low,scc_id,inside;
    vector<vll> scc_nodes;
    vector<vll> SCC;
    stack<int> st;

    TarjanSCC(int _n):n(_n), timer(0),scc_cnt(0),
        dfn(_n,0),low(_n,0),scc_id(_n,0),inside(_n,0),scc_nodes(1){}

    void dfs(int u,const vector<vll> &graph){
        dfn[u] = low[u] = ++timer;
        st.push(u);
        inside[u] = 1;

        for(int v:graph[u]){
            if(!dfn[v]){
                dfs(v,graph);
                low[u]=min(low[u],low[v]);
            }else if(inside[v]){
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(low[u]==dfn[u]){
            scc_cnt++;
            scc_nodes.push_back({});
            while(true){
                int v=st.top(); st.pop();
                inside[v] = 0;
                scc_id[v] = scc_cnt;
                scc_nodes.back().push_back(v);
                if(u==v)break;
            }
        }
        
    }
    void build(vector<vll> &graph){
        SCC.assign(scc_cnt+1,{});
        rep(i,0,n){
            if(scc_id[i]==0)continue;
            for(auto u:graph[i]){
                if(scc_id[u]==0)continue;
                if(scc_id[i]==scc_id[u])continue;
                SCC[scc_id[i]].pb(scc_id[u]);
            }
        }
    }
};
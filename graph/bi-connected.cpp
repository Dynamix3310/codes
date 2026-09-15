void dfs(int x,int pr){
    dfn[x]=low[x]=++cnt;
    st.pb(x);
    for(auto u:graph[x]){
        if(u==pr)continue;
        if(!dfn[u]){
            dfs(u,x);
            low[x]=min(low[x],low[u]);
            if(low[u]>=dfn[x]){
                ans.pb(vll());
                int start;
                do{
                    start=st.back();
                    st.pop_back();
                    ans.back().pb(start);
                    visited[start]=1;
                }while(start!=u);
                // st.pop_back();
                visited[x]=1;
                ans.back().pb(x);
            }
        }else{
            low[x]=min(low[x],dfn[u]);
        }
    }
}
struct suffix_array{
    vector<int> lcp,rank,sa;
    string s;
    int n;
    void init(string S){
        s=S;
        n=s.size()+1;
        lcp = rank = sa = vector<int>(n,0);
        for(int i=0;i<n;i++)sa[i]=i;
        sort(sa.begin(),sa.end(),[&](int u,int v){return s[u]<s[v];});
        rank[sa[0]]=0;
        for(int i=1;i<n;i++){
            rank[sa[i]]=rank[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
        }
    }
    vector<int> nrank,psa,cnt;
    void build(){
        for(int k=1;k<=n;k<<=1){
            nrank = psa = cnt = vector<int>(n,0);
            for(int i=0;i<n;i++){
                cnt[rank[i]]++;
            }
            for(int i=1;i<n;i++){
                cnt[i]+=cnt[i-1];
            }
            for(int i=0;i<n;i++){
                psa[i] = (sa[i]-k+n)%n;
            }
            for(int i=n-1;i>=0;i--){
                sa[--cnt[rank[psa[i]]]]=psa[i];
            }
            pair<int,int> prv=make_pair(rank[sa[0]],rank[(sa[0]+k)%n]);
            nrank[sa[0]]=0;
            for(int i=1;i<n;i++){
                pair<int,int> nxt=make_pair(rank[sa[i]],rank[(sa[i]+k)%n]);
                nrank[sa[i]]=nrank[sa[i-1]]+(prv!=nxt);
                prv=nxt;
            }
            swap(rank,nrank);
        }
        for(int i=0;i<n-1;i++){
            if(i){
                lcp[rank[i]] = lcp[rank[i-1]] - (lcp[rank[i-1]]!=0);
            }
            while(s[i+lcp[rank[i]]] == s[sa[rank[i]-1]+lcp[rank[i]]]
            && i+lcp[rank[i]]<n-1
            && sa[rank[i]-1]+lcp[rank[i]]<n-1){
                lcp[rank[i]]++;
            }
        }
    }
};

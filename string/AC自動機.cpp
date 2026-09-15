struct AC_auto{
    struct node{
        int lf,next[26];//fail link,'next' use for trie
        node(int value){memset(next,value,sizeof(next));};
    };
    vector<node> trie;
    vector<int> exist;
    vector<int> bfs;
    AC_auto():trie(1,-1){}
    int insert(string &s,int l){
        int p=0;
        for(int i=0;i<l;i++){
            int c=(s[i]-'a');
            if(trie[p].next[c]==-1){
                trie[p].next[c]=trie.size();
                trie.push_back(-1);
                exist.push_back(0);
            }
            p=trie[p].next[c];
        }
        exist[p]++;
        return p;
    }
    void build(){
        trie[0].lf=trie.size();
        trie.push_back(0);
        bfs.push_back(0);
        for(int i=0;i<bfs.size();i++){
            int now=bfs[i];
            int Pre=trie[now].lf;
            for(int k=0;k<26;k++){
                int &next=trie[now].next[k];
                int Pre_next=trie[Pre].next[k];
                if(next==-1)next=Pre_next;
                else trie[next].lf=Pre_next,bfs.push_back(next);
            }
        }
        return;
    }
};

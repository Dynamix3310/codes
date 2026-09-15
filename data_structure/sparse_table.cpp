struct sparse_table{
    vector<vector<long long int> > table;
    int n;
    void init(int N,vector<long long int> &a){
        n=N;
        int k=__lg(n)+1;
        table = vector<vector<long long int> >(k+1,vector<long long int>(n,0));
        table[0]=a;
        for(int j=1;j<=k;j++){
            for(int i=0;i<n;i++){
                table[j][i]=min(table[j-1][i],table[j-1][min(n-1,i+(1<<(j-1)))]);
            }
        }
    }
    long long int query(int l,int r){
        int j=__lg(r-l+1);
        return min(table[j][l],table[j][r-(1<<j)+1]);
    }
};

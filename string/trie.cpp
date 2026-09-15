long long int dp[5050];
bitset<1000010> stop;
int trie[1000010][26];
int cnt=0;
void insert(string s){
    int node=0;
    for(int i=0;i<s.size();i++){
        if(trie[node][s[i]-'a']==0)trie[node][s[i]-'a']=++cnt;
        node=trie[node][s[i]-'a'];
    }
    stop[node]=1;
}
string s;
long long int search(int x){
    int node=0;
    long long int ans=0;
    for(int i=x;i<s.size();i++){
        if(trie[node][s[i]-'a']==0)return ans;
        node=trie[node][s[i]-'a'];
        if(stop[node])(ans+=dp[i+1])%=MOD;
    }
    return ans;
}

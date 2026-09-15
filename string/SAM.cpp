#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
 
struct SuffixAutomaton {
  enum { sigma = 26, alpha = 'a' };
  vector<array<int, sigma>> ch;
  vi link, len, cnt;
  vector<long long int> dp;
  //vector<long long int> dp_size;
  vi in;
  vector<vector<int> > graph;
  vector<bool> visited;
  int last;
  int new_node() {
    ch.emplace_back();
    fill(all(ch.back()), -1);
    link.push_back(-1);
    len.push_back(0);
    cnt.push_back(0);
    return sz(ch) - 1;
  } 
  void insert(char c) {
    //cur is id
    int cur = new_node();
    len[cur] = len[last] + 1;
    cnt[cur] = 1;
    int p = last;
    //link all the edge that needs to link to cur
    while (p != -1 and ch[p][c - alpha] == -1) {
      ch[p][c - alpha] = cur;
      p = link[p];
    }
    if (p == -1) link[cur] = 0;
    else {
      int q = ch[p][c - alpha];
      if (len[p] + 1 == len[q])
        link[cur] = q;
      else {
        int clone = new_node();
        len[clone] = len[p] + 1;
        ch[clone] = ch[q];
        link[clone] = link[q];
        while (p != -1 and ch[p][c - alpha] == q) {
          ch[p][c - alpha] = clone;
          p = link[p];
        }
        link[q] = link[cur] = clone;
      }
    }
    last = cur;
  }
  void gen_graph(int x){
    //cerr<<x<<" ";
    if(visited[x])return;
    visited[x]=1;
    for(int i=0;i<26;i++){
        if(ch[x][i]==-1)continue;
        graph[ch[x][i]].push_back(x);
        in[x]++;
        gen_graph(ch[x][i]);
    }
    return;
  }
  SuffixAutomaton(const string &T) : last(0) {
    new_node();
    for (char c : T) insert(c);
    vi ind(sz(ch), 0);
    for (int i: link) if (i != -1) ind[i] += 1;
    queue<int> q;
    rep (i, 0, sz(ch)) if (ind[i] == 0) q.push(i);
    //dp區，離線維護
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (link[u] == -1) continue;
      cnt[link[u]] += cnt[u];
      ind[link[u]] -= 1;
      if (ind[link[u]] == 0)
        q.push(link[u]);
    }
    //dp區結束
    dp.resize(ch.size(),0);
    //dp_size.resize(ch.size(),0);
    in.resize(ch.size(),0);
    graph.resize(ch.size(),vector<int>(0));
    visited.resize(ch.size(),0);
    gen_graph(0);
    //cerr<<"\n";
  }
  void to_one(){
    for(int i=0;i<cnt.size();i++){
      cnt[i]=(cnt[i]!=0);
    }
    return;
  }
  //使用dp查詢答案
  int query(const string &P) {
    int u = 0;
    for (char c : P) {
      if (ch[u][c - alpha] == -1) return 0;
      u = ch[u][c - alpha];
    }
    return cnt[u];
  }
  long long int DAG_dp(){
    queue<int> q;
    for(int i=0;i<ch.size();i++){
        if(in[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int now=q.front();
        //cerr<<now<<'\n';
        dp[now]+=cnt[now];
        q.pop();
        for(auto u:graph[now]){
            in[u]--;
            dp[u]+=dp[now];
            //dp_size[u]+=dp[now]+dp_size[now];
            if(in[u]==0)q.push(u);
        }
    }
    //cerr<<dp_size[0];
    return dp[0];
  }
  void dfs_for_ans(int x,vector<char> &ans,long long int &k){
    if(k<0)return;
    else if(k==0){
      for(int i=0;i<ans.size();i++){
        cout<<ans[i];
      }
      return;
    }
    for(int i=0;i<26;i++){
      if(ch[x][i]==-1)continue;
      if(k<=0)break;
      if(dp[ch[x][i]]<k){
        k-=dp[ch[x][i]];
        continue;
      }
      ans.push_back((char)('a'+i));
      if(k-cnt[ch[x][i]]<=0)k=0;
      else k-=cnt[ch[x][i]];
      dfs_for_ans(ch[x][i],ans,k);
      ans.pop_back();
    }
    return;
  }
  void dfs(int x,vector<char> &ans){
    for(auto u:ans){
      cerr<<u;
    }
    cerr<<" "<<dp[x];
 
    cerr<<"\n";
    for(int i=0;i<26;i++){
      if(ch[x][i]==-1)continue;
      ans.push_back((char)('a'+i));
      dfs(ch[x][i],ans);
      ans.pop_back();
    }
  }
};

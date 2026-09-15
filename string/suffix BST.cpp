struct SuffixBST {
  const double alpha = 0.75;
  struct Node {
    int siz, lc, rc;
    double tag;
  };
  string s;
  int root, ptr;
  vector<Node> nd;
  vector<int> buf;
  bool cmp(int u, int v) {
    if (s[u] != s[v]) return s[u] < s[v];
    return nd[u + 1].tag < nd[v + 1].tag;
  }
  int siz(int u) { return u == -1 ? 0 : nd[u].siz; }
  void pull(int u) { nd[u].siz = siz(nd[u].lc) + 1 + siz(nd[u].rc); }
  bool balanced(int u) { return alpha * nd[u].siz > max(siz(nd[u].lc), siz(nd[u].rc)); }
  void flatten(int u) {
    if (u == -1) return;
    flatten(nd[u].lc); buf.push_back(u); flatten(nd[u].rc);
  }
  void build(int &u, int l, int r, double lb, double rb) {
    int m = (l + r) / 2;
    double mb = (lb + rb) / 2;
    u = buf[m];
    nd[u].tag = mb;
    if (l < m) build(nd[u].lc, l, m, lb, mb);
    else nd[u].lc = -1;
    if (m + 1 < r) build(nd[u].rc, m + 1, r, mb, rb);
    else nd[u].rc = -1;
    pull(u);
  }
  void rebuild(int &u, double lb, double rb) {
    if (u == -1) return;
    buf.clear();
    flatten(u);
    build(u, 0, buf.size(), lb, rb);
  }
  void insert(int &u, int i, double lb, double rb) {
    if (u == -1) {
      u = i;
      nd[u].siz = 1;
      nd[u].lc = nd[u].rc = -1;
      nd[u].tag = (lb + rb) / 2;
      return;
    }
    if (cmp(i, u)) insert(nd[u].lc, i, lb, nd[u].tag);
    else insert(nd[u].rc, i, nd[u].tag, rb);
    pull(u);
    if (not balanced(u)) rebuild(u, lb, rb);
  }
  void remove(int &u, int i, double lb, double rb) {
    if (u == -1) return;
    if (u == i) {
      if (nd[u].lc == -1) rebuild(u = nd[u].rc, lb, rb);
      else if (nd[u].rc == -1) rebuild(u = nd[u].lc, lb, rb);
      else {
        int v = nd[u].lc;
        while (nd[v].rc != -1) v = nd[v].rc;
        remove(nd[u].lc, v, lb, nd[u].tag);
        nd[v].lc = nd[u].lc;
        nd[v].rc = nd[u].rc;
        nd[v].tag = (lb + rb) / 2;
        u = v;
      }
    } else {
      if (cmp(i, u)) remove(nd[u].lc, i, lb, nd[u].tag);
      else remove(nd[u].rc, i, nd[u].tag, rb);
    }
    if (u == -1) return;
    pull(u);
    if (not balanced(u)) rebuild(u, lb, rb);
  }
  bool cmp_string(const string &t, int u) {
    for(int i=0;i<min((int)t.size(),(int)s.size()-u)+1;i++){
      if (t[i] != s[u + i])
        return t[i] < s[u + i];
    }
    return false;
  }
  int query(int u, const string &s) {
    if (u == -1) return 0;
    if (cmp_string(s, u))
      return query(nd[u].lc, s);
    return siz(nd[u].lc) + 1 + query(nd[u].rc, s);
  }
  SuffixBST(int n) : s(n, 0), root(-1), ptr(n), nd(n + 1) { }
  void push(char c) {
    s[--ptr] = c;
    insert(root, ptr, 0, 1);
  }
  void pop() {
    remove(root, ptr, 0, 1);
    if(ptr==s.size())return;
    s[ptr++] = char(0);
  }
  int get_rank(const string &s) { return query(root, s); }
  vector<int> sa() {
    buf.clear();
    flatten(root);
    return buf;
  }
};

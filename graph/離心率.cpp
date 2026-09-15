/*给定一棵带边权无根树，在其直径上求出一段长度不超过s的路径F，使得离路径距离最远的点到路径的距离最短。
 * pres[i] (Prefix Sum): 儲存的是，直徑上第 i 個點 (dia[i]) 距離直徑起點 (dia[1]) 的長度。

posts[i] (Postfix Sum / Suffix Sum): 儲存的是，直徑上第 i 個點 (dia[i]) 距離直徑終點 (dia[cnt]) 的長度。
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
struct edge {
  int v, w;
  edge(int v = 0, int w = 0) {
    this->v = v;
    this->w = w;
  }
};
const int maxn = 300000 + 5;
vector<edge> e[maxn];
int dep[maxn], f[maxn], c;
int dia[maxn], cnt, pres[maxn], posts[maxn];
bool vis[maxn];
int n, s;

void dfs(int u, int fa) {
  f[u] = fa;
  for (auto ed : e[u]) {
    if (ed.v == fa || vis[ed.v]) continue;
    dep[ed.v] = dep[u] + ed.w;
    if (dep[ed.v] > dep[c]) c = ed.v;
    dfs(ed.v, u);
  }
}

void get_diameter() {
  dfs(1, 0);
  dep[c] = 0;
  dfs(c, 0);
  for (int u = c; u; u = f[u]) {
    dia[++cnt] = u;
    pres[cnt] = dep[u];
  }
  reverse(dia + 1, dia + cnt + 1);
  reverse(pres + 1, pres + cnt + 1);
  for (int i = cnt; i > 0; i--) posts[i] = pres[cnt] - pres[i];
}

int maxd[maxn];
bool check(int ecc) {
  int l = 1, r = cnt;
  while (l < cnt && pres[l + 1] <= ecc) l++;
  while (r > l && posts[r - 1] <= ecc) r--;
  if (pres[r] - pres[l] > s) return false;
  int d = 0;
  for (int i = l + 1; i < r; i++) d = max(d, maxd[i]);
  return d <= ecc;
}

void solve() {
  for (int i = 1; i <= cnt; i++) vis[dia[i]] = true;
  // 計算直徑上每個點，不經過直徑其他點所能到達的最遠距離
  for (int i = 1; i <= cnt; i++) {
    dep[dia[i]] = 0, c = 0;
    dfs(dia[i], 0);
    maxd[i] = dep[c];
  }
  int l = 0, r = 1 << 30, ans = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid))
      ans = mid, r = mid - 1;
    else
      l = mid + 1;
  }
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> s;
  for (int i = 1; i < n; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
  }
  get_diameter();
  solve();
  return 0;
}

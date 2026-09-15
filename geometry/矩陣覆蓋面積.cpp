#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 根據競賽需求調整最大矩形數量 (N)
// 矩形數為 N，則事件數為 2N，Y 座標數為 2N
const int MAXN = 200005; 

struct Event {
    double x;
    double y1, y2;
    int type;
    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return type > other.type; // 習慣上先處理入邊 (+1)
    }
} events[MAXN * 2];

// Y 座標離散化陣列
double ys[MAXN * 2];

// 線段樹節點陣列（4倍空間）
struct Node {
    int cnt;
    double len;
} tree[MAXN * 8];

// 更新節點覆蓋長度
inline void push_up(int node, int l, int r) {
    if (tree[node].cnt > 0) {
        tree[node].len = ys[r + 1] - ys[l];
    } else if (l == r) {
        tree[node].len = 0;
    } else {
        tree[node].len = tree[node << 1].len + tree[node << 1 | 1].len;
    }
}

// 區間修改：ql, qr 為離散化後的 Y 區間索引
void update(int node, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        tree[node].cnt += val;
        push_up(node, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) update(node << 1, l, mid, ql, qr, val);
    if (qr > mid)  update(node << 1 | 1, mid + 1, r, ql, qr, val);
    push_up(node, l, r);
}

void solve() {
    int n;
    cin >> n;

    int ev_cnt = 0, y_cnt = 0;
    for (int i = 0; i < n; ++i) {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        events[ev_cnt++] = {x1, y1, y2, 1};
        events[ev_cnt++] = {x2, y1, y2, -1};
        ys[y_cnt++] = y1;
        ys[y_cnt++] = y2;
    }

    // 1. Y 座標離散化 (排序 + 去重)
    sort(ys, ys + y_cnt);
    y_cnt = unique(ys, ys + y_cnt) - ys;

    // 2. 掃描線事件排序
    sort(events, events + ev_cnt);

    // 3. 初始化線段樹（多筆測資重置）
    // 區間總數為 y_cnt - 1，線段樹維護索引 0 到 y_cnt - 2
    int max_node = y_cnt * 4;
    for (int i = 0; i <= max_node; ++i) {
        tree[i].cnt = 0;
        tree[i].len = 0.0;
    }

    double total_area = 0.0;

    // 4. 執行掃描線
    for (int i = 0; i < ev_cnt; ++i) {
        if (i > 0) {
            total_area += (events[i].x - events[i - 1].x) * tree[1].len;
        }

        // 二分搜尋找到離散化後的索引位置
        int ql = lower_bound(ys, ys + y_cnt, events[i].y1) - ys;
        int qr = lower_bound(ys, ys + y_cnt, events[i].y2) - ys - 1;

        if (ql <= qr) {
            update(1, 0, y_cnt - 2, ql, qr, events[i].type);
        }
    }

    printf("%.2f\n", total_area);
}

int main() {
    // 競賽 I/O 優化
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}
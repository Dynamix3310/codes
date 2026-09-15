#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <tuple>

using namespace std;

// 二維點/向量的結構體 (與之前相同)
template <typename T> struct P {
    T x, y;
    P(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(const P &p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(const P &p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator-(P p) const { return {x - p.x, y - p.y}; }
    // 注意：這個問題只需要用到減法，其他運算子可以省略
    T dist2() const { return x * x + y * y; }
};
using pt = P<double>; // 為了方便，我們使用 double

// 外積函式 (與之前相同)
double cross(pt a, pt b) { return a.x * b.y - a.y * b.x; }
double cross(pt a, pt b, pt o) { return cross(a - o, b - o); }

// 凸包演算法 (與之前相同)
vector<pt> convex_hull(vector<pt> p) {
    sort(p.begin(), p.end());
    if (p.size() <= 1) return p;
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    vector<pt> h(n + 1);
    int t = 0;
    for (int _ = 2, s = 0; _--; s = --t, reverse(p.begin(), p.end()))
        for(pt i : p){
            while(t > s + 1 && cross(i, h[t-1], h[t-2]) >= 0)
                t--;
            h[t++] = i;
    }
    h.resize(t - (t > 1 && h[t-1] == h[0])); // 移除重複的起始點
    return h;
}

/**
 * @brief 使用旋轉卡尺計算凸包的直徑 (最遠點對的距離)
 * @param hull 已經計算好的凸包頂點 (需按逆時針順序)
 * @return 凸包的直徑長度
 */
double rotating_calipers_diameter(const vector<pt>& hull) {
    int n = hull.size();
    if (n < 2) return 0.0;
    if (n == 2) return sqrt((hull[0] - hull[1]).dist2());

    int j = 1; // 第二個卡尺的頂點索引
    double max_dist_sq = 0.0; // 儲存最大距離的平方，避免頻繁開根號

    // 尋找與 p[0]-p[1] 這條邊對應的最遠頂點 j
    // 也就是尋找使三角形 p[0]p[1]p[j] 面積最大的 j
    // 這等價於讓 cross(p[1]-p[0], p[j]-p[0]) 最大
    for (int k = 2; k < n; ++k) {
        if (cross(hull[1] - hull[0], hull[k] - hull[0]) > cross(hull[1] - hull[0], hull[j] - hull[0])) {
            j = k;
        }
    }

    // 主迴圈：讓第一個卡尺 i 掃過凸包的每一條邊
    for (int i = 0; i < n; ++i) {
        // 第二個卡尺 j 持續前進，直到找到與邊 i-(i+1) 對應的最遠點
        // 判斷條件：比較邊 i-(i+1) 和邊 j-(j+1) 的「角度」
        // cross > 0 代表 edge_j 的角度比較小，j 應該繼續前進
        // cross(v1, v2) > 0  => v2 is counter-clockwise from v1
        while (cross(hull[(i + 1) % n] - hull[i], hull[(j + 1) % n] - hull[j]) > 0) {
            max_dist_sq = max(max_dist_sq, (hull[i] - hull[j]).dist2());
            j = (j + 1) % n;
        }
        
        // 更新最大距離 (比較 i 和 j, 以及 i+1 和 j 之間的距離)
        // 因為此時 j 是與邊 i-(i+1) 的對蹠點
        max_dist_sq = max(max_dist_sq, (hull[i] - hull[j]).dist2());
        max_dist_sq = max(max_dist_sq, (hull[(i + 1) % n] - hull[j]).dist2());
    }

    return sqrt(max_dist_sq); // 最後再開一次根號得到答案
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cout << "請輸入點的數量: ";
    cin >> n;

    vector<pt> p(n);
    cout << "請輸入 " << n << " 個點的座標 (x y):" << aendl;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    vector<pt> hull = convex_hull(p);
    
    cout << "\n凸包上的頂點有 " << hull.size() << " 個。" << endl;

    double diameter = rotating_calipers_diameter(hull);

    cout << fixed << setprecision(10);
    cout << "凸包的直徑 (最遠點對距離) 為: " << diameter << endl;

    return 0;
}

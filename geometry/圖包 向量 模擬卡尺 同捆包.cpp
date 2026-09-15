// 引入常用的 C++ 函式庫，bits/stdc++.h 是一個非標準但方便的標頭檔
//#include <bits/stdc++.h> 
#include<iostream> // 用於輸入輸出
#include<vector>   // 使用 std::vector 容器
#include<iomanip> // 用於格式化輸出，如 setprecision
#include<cmath>     // 使用 sqrt 等數學函數
#include<algorithm> // 使用 sort, reverse, min 等演算法
#include<numeric>   // 使用 accumulate
#include<tuple>     // 使用 std::tie 進行字典序比較

using namespace std;

// 模板化的二維點/向量結構體，可適用於不同數值型別 (如 int, double)
template <typename T> struct P {
    T x, y; // 點的 x 和 y 座標

    // 建構子，預設為原點 (0, 0)
    P(T x = 0, T y = 0) : x(x), y(y) {}

    // --- 運算子重載 ---

    // 小於運算子，用於排序。使用 std::tie 進行字典序比較 (先比 x，若 x 相同再比 y)
    bool operator<(const P &p) const { return tie(x, y) < tie(p.x, p.y); }
    // 等於運算子
    bool operator==(const P &p) const { return tie(x, y) == tie(p.x, p.y); }
    // 負號運算子 (向量反向)
    P operator-() const { return {-x, -y}; }
    // 加法運算子 (向量相加)
    P operator+(P p) const { return {x + p.x, y + p.y}; }
    // 減法運算子 (向量相減)
    P operator-(P p) const { return {x - p.x, y - p.y}; }
    // 純量乘法 (向量縮放)
    P operator*(T d) const { return {x * d, y * d}; }
    // 純量除法 (向量縮放)
    P operator/(T d) const { return {x / d, y / d}; }

    // --- 幾何方法 ---

    // 計算到原點距離的平方，可避免開根號，用於比較距離大小
    T dist2() const { return x * x + y * y; }
    // 計算到原點的距離 (向量長度)
    double len() const { return sqrt(dist2()); }
    // 計算單位向量
    P unit() const { return *this / len(); }

    // --- 友元函式 (friend functions) ---

    // 計算兩向量的內積 (dot product)
    friend T dot(P a, P b) { return a.x * b.x + a.y * b.y; }
    // 計算兩向量的外積 (cross product)。結果的正負號代表 b 在 a 的逆時針/順時針方向
    friend T cross(P a, P b) { return a.x * b.y - a.y * b.x; }
    // 計算以 o 為原點時，向量 oa 和 ob 的外積。用於判斷轉向
    friend T cross(P a, P b, P o) { return cross(a - o, b - o); }
};
// 為 P<double> 型別定義一個簡潔的別名 pt
using pt = P<double>;

/**
 * @brief 計算點集的凸包 (Convex Hull)
 * @param p 點集 vector
 * @return 凸包上的點集 (逆時針排序)
 * 使用 Andrew's Monotone Chain Algorithm
 */
vector<pt> convex_hull(vector<pt> p) {
    // 1. 將所有點進行字典序排序
    sort(p.begin(),p.end());
    if(p[0]==p.back()) return {p[0]}; // 如果所有點都相同

    int n = p.size();
    vector<pt> h(n + 1); // 用來儲存凸包頂點的陣列
    int t = 0; // 目前凸包頂點的數量

    // 這個迴圈跑兩次，一次建立下凸包，一次建立上凸包
    // 第一次: 正常順序遍歷
    // 第二次: reverse 點集後，再次遍歷
    for (int _ = 2, s = 0; _--; s = --t, reverse(p.begin(), p.end()))
        for(pt i : p){
            // 核心步驟：檢查新加入的點 i 是否造成「非左轉」
            // cross(i, h[t-1], h[t-2]) >= 0 代表 i 相對於 h[t-2]->h[t-1] 這條線是直走或右轉
            // 如果是，代表 h[t-1] 這個點是凹進去的，需要從凸包中移除
            while(t > s + 1 && cross(i, h[t-1], h[t-2]) >= 0)
                t--;
            h[t++] = i; // 將當前點加入凸包
    }

    h.resize(t); // 調整 vector 大小以符合實際凸包頂點數
    return h;
}

/**
 * @brief 三分搜尋 (Ternary Search)
 * @param p1, p2 兩點的初始位置
 * @param v1, v2 兩點的移動方向向量 (單位向量)
 * @param len 移動的總距離/時間
 * @return 兩點在移動過程中的最小距離
 * 用於求解單峰函數的極值問題
 */
double find_dist(pt p1, pt p2, pt v1, pt v2, double len){
    // 定義一個 lambda 函數，計算在移動 g_len 距離後，兩點間的距離
    auto find_len = [&](double g_len) {
        // p1 + v1 * g_len: p1 沿 v1 方向移動 g_len 後的位置
        return ((p1 + v1 * g_len) - (p2 + v2 * g_len)).len();
    };

    double l = 0, r = len; // 設定搜尋區間 [0, len]
    // 迭代固定次數 (例如 150 次) 以達到足夠的精度
    for(int i=0; i<=150; i++){
        double m1 = l + (r - l) / 3; // 左三等分點
        double m2 = r - (r - l) / 3; // 右三等分點
        // 比較兩個三等分點的函數值，縮小搜尋區間
        if(find_len(m1) < find_len(m2)){
            r = m2; // 最小值在 [l, m2] 區間
        }else{
            l = m1; // 最小值在 [m1, r] 區間
        }
    }
    // 返回最終區間中點的函數值作為近似最小值
    return find_len((l + r) / 2);
}

int main() {
    // 加速 C++ IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pt> p(n);
    // C++17 結構化綁定 (Structured Binding)，方便地讀取 x, y 座標
    for (auto &[x, y] : p)
        cin >> x >> y;

    // 1. 計算點集的凸包
    p = convex_hull(p);
    n = p.size(); // 更新 n 為凸包的頂點數

    // 2. 計算凸包總周長
    double total = 0;
    for (int i = 0; i < n; i++)
        total += (p[(i + 1) % n] - p[i]).len();

    // 3. 初始化兩個對蹠點 p1, p2
    auto p1 = p[0], p2 = p[0];
    int cur1 = 0, cur2 = 0; // p1 和 p2 所在的頂點索引
    double acc = 0; // 累積周長

    // 找到與 p1 周長距離為 total/2 的初始點 p2
    while (true) {
        auto edge_len = (p[(cur2 + 1) % n] - p[cur2]).len(); // 當前邊的長度
        if (acc + edge_len <= total / 2) {
            // 如果加上整條邊還不到一半周長，就直接跳到下個頂點
            acc += edge_len;
            cur2 = (cur2 + 1) % n;
            p2 = p[cur2];
        } else {
            // 如果目標點在這條邊上，計算確切位置
            auto rem_len = total / 2 - acc; // 剩下需要走的距離
            // p2 移動到邊上的對應位置
            p2 = p2 + (p[(cur2 + 1) % n] - p[cur2]) * (rem_len / edge_len);
            break;
        }
    }

    // 4. 旋轉卡尺 (Rotating Calipers) 模擬
    auto ans = (p1 - p2).len(); // 初始答案為第一對對蹠點的距離

    // 讓 p1, p2 沿著凸包邊界同步移動，遍歷所有對蹠點對
    // 迴圈次數設為 2n 足以確保遍歷完整個凸包
    for (int i = 1; i <= (n << 1); i++) {
        // p1 到下一個頂點的距離
        auto rem_len_1 = (p[(cur1 + 1) % n] - p1).len();
        // p2 到下一個頂點的距離
        auto rem_len_2 = (p[(cur2 + 1) % n] - p2).len();
        // 找出兩者中較小的距離，作為本次移動的距離
        auto rem = min(rem_len_1, rem_len_2);

        // 在這段長度為 rem 的移動過程中，用三分搜尋找最小距離並更新答案
        ans = min(ans, find_dist(p1, p2, (p[(cur1 + 1) % n] - p1).unit(),
                                 (p[(cur2 + 1) % n] - p2).unit(), rem));

        // 更新 p1 和 p2 的位置
        if (abs(rem_len_1 - rem_len_2) <= 1e-9) { // 兩點同時到達頂點
            cur1 = (cur1 + 1) % n;
            p1 = p[cur1];
            cur2 = (cur2 + 1) % n;
            p2 = p[cur2];
        } else if (rem_len_1 < rem_len_2) { // p1 先到達頂點
            cur1 = (cur1 + 1) % n;
            p1 = p[cur1];
            p2 = p2 + (p[(cur2 + 1) % n] - p2).unit() * rem; // p2 在邊上移動相同距離
        } else { // p2 先到達頂點
            cur2 = (cur2 + 1) % n;
            p2 = p[cur2];
            p1 = p1 + (p[(cur1 + 1) % n] - p1).unit() * rem; // p1 在邊上移動相同距離
        }
    }

    // 輸出最終答案，設定高精度
    cout << fixed << setprecision(15) << ans << '\n';
}

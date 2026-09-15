#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> // For std::swap
#include <iomanip>   // For std::setprecision
#include <random>    // For std::shuffle (modern C++)
#include <chrono>    // For std::shuffle seed

// --- 常數定義 ---
const int N = 100005;     // 最大點數
const double EPS = 1e-9;  // 浮點數誤差範圍

// --- 輔助函數：判斷是否為零 ---
bool iszero(double d) {
    return std::fabs(d) < EPS;
}

// --- 結構：Pt (點/向量) ---
struct Pt {
    double x, y;

    // 運算子重載
    Pt operator+(const Pt& b) const { return {x + b.x, y + b.y}; }
    Pt operator-(const Pt& b) const { return {x - b.x, y - b.y}; }
    Pt operator*(double s) const { return {x * s, y * s}; }
    Pt operator/(double s) const { return {x / s, y / s}; }
    double operator*(const Pt& b) const { return x * b.x + y * b.y; } // 內積 (Dot product)
    double operator^(const Pt& b) const { return x * b.y - y * b.x; } // 外積 (Cross product)
};

// --- Pt 的輔助函數 ---
double norm2(const Pt& p) { return p.x * p.x + p.y * p.y; } // 向量長度的平方
double norm(const Pt& p) { return std::sqrt(norm2(p)); }    // 向量長度

// --- 結構：Circle (圓) ---
struct Circle {
    Pt o; // 圓心
    double r; // 半徑

    // 判斷點 p 是否在圓內（或圓周上）
    bool inside(const Pt& p) const {
        // 使用 norm2 避免 sqrt 的浮點數誤差，並加入 EPS
        return norm2(p - o) <= r * r + EPS;
    }
};

// --- 全局變數 ---
int n;
Pt p[N];

// --- 您提供的 circumcircle 函數 (計算三點外接圓) ---
// (此函數功能正確，無需修改)
const Circle circumcircle(Pt a, Pt b, Pt c) {
    Circle cir;
    double fa, fb, fc, fd, fe, ff, dx, dy, dd;
    
    // 處理三點共線的特殊情況
    if (iszero((b - a) ^ (c - a))) {
        if (((b - a) * (c - a)) <= 0)
            return Circle((b + c) / 2, norm(b - c) / 2);
        if (((c - b) * (a - b)) <= 0)
            return Circle((c + a) / 2, norm(c - a) / 2);
        if (((a - c) * (b - c)) <= 0)
            return Circle((a + b) / 2, norm(a - b) / 2);
    } 
    // 一般情況：解線性方程組 (Ax=B, Cy=D)
    else {
        fa = 2 * (a.x - b.x);
        fb = 2 * (a.y - b.y);
        fc = norm2(a) - norm2(b);
        fd = 2 * (a.x - c.x);
        fe = 2 * (a.y - c.y);
        ff = norm2(a) - norm2(c);
        dx = fc * fe - ff * fb;
        dy = fa * ff - fd * fc;
        dd = fa * fe - fd * fb;
        cir.o = Pt(dx / dd, dy / dd);
        cir.r = norm(a - cir.o);
        return cir;
    }
    // 理論上不會執行到這裡，但為 C++ 編譯器添加一個返回值
    return Circle{{0,0}, 0}; 
}

// --- 修正後的 mec 函數 (Welzl 演算法核心) ---
/**
 * @param fixed 已確定在圓周上的點的數量 (儲存在 p[0]...p[fixed-1])
 * @param num 總共考慮的點的數量 (p[0]...p[num-1])
 */
inline Circle mec(int fixed, int num) {
    Circle cir;
    
    // --- 修正：根據 'fixed' 數量初始化 'cir' ---
    // fixed=3: 基礎情況，由3個點決定圓
    if (fixed == 3) {
        return circumcircle(p[0], p[1], p[2]);
    }
    // fixed=0: 尚未有固定點，從 p[0] 開始
    else if (fixed == 0) {
        // 假設 num >= 1 (由 min_radius 保證)
        cir = Circle{p[0], 0}; // 圓心=p[0], 半徑=0
    }
    // fixed=1: 1個固定點 p[0]
    else if (fixed == 1) {
        cir = Circle{p[0], 0}; // 圓心=p[0], 半徑=0
    }
    // fixed=2: 2個固定點 p[0], p[1]
    else if (fixed == 2) {
        cir = Circle{(p[0] + p[1]) / 2, norm(p[0] - p[1]) / 2}; // 圓心=中點, 半徑=距離一半
    }
    // --- 修正結束 ---

    // 迭代檢查剩餘的點 p[fixed] ... p[num-1]
    for (int i = fixed; i < num; i++) {
        if (cir.inside(p[i])) continue; // 如果點在圓內，繼續

        // 如果 p[i] 在圓外，它必須是新圓的邊界點
        // 將 p[i] 交換到 'fixed' 的位置，將其加入固定點集合
        std::swap(p[i], p[fixed]);

        // 遞歸調用
        // 新的固定點集合 R' = {p[0]...p[fixed]}
        // 新的檢查點集合 P' = {p[fixed+1]...p[i]} (即原始的 p[fixed]...p[i-1])
        cir = mec(fixed + 1, i + 1);
    }
    return cir;
}

// --- 打亂點的順序 (隨機增量演算法的關鍵) ---
inline void scramble() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(p, p + n, std::default_random_engine(seed));
}

// --- 您提供的 min_radius 函數 (入口) ---
// (修正：移除了多餘的 n=1, n=2 檢查，因為修正後的 mec 可以處理)
inline double min_radius() {
    if (n <= 0) return 0.0; // 處理空集合

    scramble(); // 必須先打亂

    // mec(0, n) 會正確處理 n=1 和 n=2 的情況
    // n=1: mec(0, 1) -> cir={p[0], 0} -> r=0
    // n=2: mec(0, 2) -> ... -> mec(2, 2) -> cir=Circle(p[0], p[1]) -> r=norm/2
    return mec(0, n).r;
}

// --- 主函數：讀取輸入並執行 ---
int main() {
    // 優化 C++ I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // 設置輸出精度
    std::cout << std::fixed << std::setprecision(6);

    while (std::cin >> n && n) {
        for (int i = 0; i < n; ++i) {
            std::cin >> p[i].x >> p[i].y;
        }

        if (n == 0) {
            std::cout << "0.000000 0.000000 0.000000\n";
            continue;
        }

        // 隨機化
        scramble();

        // 獲取最小覆蓋圓
        Circle result = mec(0, n);

        // 輸出：圓心 X, 圓心 Y, 半徑 R
        std::cout << result.o.x << " " << result.o.y << " " << result.r << "\n";
    }

    return 0;
}
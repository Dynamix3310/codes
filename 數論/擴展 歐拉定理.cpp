#include<bits/stdc++.h>

using namespace std;

int a, m, phi = 1;
int bm, flag;

// 快速冪 (a^b % m)
int qPow(int b, int e) {
    int res = 1;
    while (e) {
        if (e & 1) res = (long long)res * b % m;
        b = (long long)b * b % m;
        e >>= 1;
    }
    return res;
}

int main() {
    cin >> a >> m;
    a %= m;
    
    // 計算歐拉函數 φ(m)
    int mm = m;
    for (int i = 2; i * i <= mm; ++i) {
        if (mm % i == 0) {
            phi *= i - 1;
            mm /= i;
            while (mm % i == 0) {
                phi *= i;
                mm /= i;
            }
        }
    }
    if (mm > 1) phi *= mm - 1;

    // 讀取大數 b
    string b;
    cin >> b;
    
    // 將 b 取模 phi
    for (char ch : b) {
        bm = bm * 10 + (ch - '0');
        if (bm >= phi) {
            flag = 1;
            bm %= phi;
        }
    }
    if (bm >= phi) {
        flag = 1;
        bm %= phi;
    }
    
    if (flag) bm += phi;

    // 計算 a^b mod m
    cout << qPow(a, bm) << endl;
    return 0;
}


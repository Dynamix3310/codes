#include <bits/stdc++.h>
using namespace std;
// 1e15 version, which mean, you can sum up a number within 1e15
// ===== 兩個 NTT-friendly 質數 =====
const long long MOD1 = 998244353;      // 119 * 2^23 + 1, g = 3
const long long MOD2 = 1224736769;     // 73  * 2^24 + 1, g = 3
const long long G = 3;

// =================== 模運算 ===================
long long modpow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b) {
        if (b & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return res;
}

// =================== NTT ===================
void NTT(vector<long long>& a, bool invert, long long MOD) {
    int n = a.size();
    vector<int> rev(n);
    int k = __lg(n);
    for (int i = 1; i < n; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int i = 0; i < n; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);

    for (int len = 2; len <= n; len <<= 1) {
        long long wlen = modpow(G, (MOD - 1) / len, MOD);
        if (invert) wlen = modpow(wlen, MOD - 2, MOD);
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i + j];
                long long v = (__int128)a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = (__int128)w * wlen % MOD;
            }
        }
    }

    if (invert) {
        long long inv_n = modpow(n, MOD - 2, MOD);
        for (auto& x : a) x = (__int128)x * inv_n % MOD;
    }
}

// =================== 單模卷積 ===================
vector<long long> convolution_mod(vector<long long> A, vector<long long> B, long long MOD) {
    int n = 1;
    long long tt = A.size() + B.size() - 1;
    while (n < tt) n <<= 1;
    A.resize(n);
    B.resize(n);
    NTT(A, false, MOD);
    NTT(B, false, MOD);
    for (int i = 0; i < n; i++)
        A[i] = (__int128)A[i] * B[i] % MOD;
    NTT(A, true, MOD);
    A.resize(tt);
    return A;
}

// =================== 兩模 CRT 合併 ===================
// 回傳結果在 [0, MOD1*MOD2)
vector<long long> convolution(vector<long long> A, vector<long long> B) {
    auto A1 = convolution_mod(A, B, MOD1);
    auto A2 = convolution_mod(A, B, MOD2);
    int n = A1.size();
    vector<long long> res(n);

    // 預先算 inv(MOD1) mod MOD2
    static const long long inv_m1_mod_m2 = modpow(MOD1, MOD2 - 2, MOD2);

    for (int i = 0; i < n; i++) {
        long long a1 = A1[i], a2 = A2[i];
        long long t = ( (__int128)(a2 - a1 + MOD2) * inv_m1_mod_m2 ) % MOD2;
        __int128 x = (__int128)t * MOD1 + a1; // 真正的整數結果
        res[i] = (long long)x; // 在這裡的值已經支援 >1e15
    }
    return res;
}

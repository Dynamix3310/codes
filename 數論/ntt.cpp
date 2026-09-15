#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;  
const int G = 3;

long long int modpow(long long int a,long long int b) {
    long long int res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void NTT(vector<long long int>& a, bool invert) {
    int n = a.size();

    vector<int> rev(n);
    int k = __lg(n);
    for (int i = 1; i < n; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int i = 0; i < n; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);

    for (int len = 2; len <= n; len <<= 1) {
        long long int wlen = modpow(G, (MOD - 1) / len);
        if (invert) wlen = modpow(wlen, MOD - 2);
        for (int i = 0; i < n; i += len) {
            long long int w = 1;
            for (int j = 0; j < len / 2; j++) {
                long long int u = a[i + j];
                long long int v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }

    if (invert) {
        long long int inv_n = modpow(n, MOD - 2);
        for (auto& x : a) x = x * inv_n % MOD;
    }
}

vector<long long int> convolution(vector<long long int> A, vector<long long int> B) {
    int n = 1;
    long long int tt=A.size();
    while (n < A.size() + B.size() - 1) n <<= 1;

    A.resize(n);
    B.resize(n);

    NTT(A, false);
    NTT(B, false);
    for (int i = 0; i < n; i++)
        A[i] = A[i] * B[i] % MOD;
    NTT(A, true);

    A.resize(tt);
    return A;
}
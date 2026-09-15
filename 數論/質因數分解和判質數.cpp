#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lb;

ll gcd(ll x, ll y) {
    while (y) {
        ll z = x % y;
        x = y;
        y = z;
    }
    return x;
}

inline ll ksc(ull x, ull y, ll p) {
    return (x * y - (ull)((lb)x / p * y) * p + p) % p;
}

inline ll ksm(ll x, ll y, ll p) {
    ll res = 1;
    while (y) {
        if (y & 1) res = ksc(res, x, p);
        x = ksc(x, x, p);
        y >>= 1;
    }
    return res;
}

// Miller–Rabin 單次測試
inline bool mr(ll a, ll p) {
    if (ksm(a, p - 1, p) != 1) return 0;
    ll d = p - 1, x;
    while (!(d & 1)) {
        d >>= 1;
        x = ksm(a, d, p);
        if (x != 1 && x != p - 1) return 0;
        if (x == p - 1) return 1;
    }
    return 1;
}

// 判質數
bool Prime(ll n) {
    if (n < 2) return false;
    static const ll small_primes[] = {2LL,3LL,5LL,7LL,11LL,13LL,17LL,19LL,23LL,29LL,31LL,37LL};
    for (ll p : small_primes) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    // 7-base set proven to work for n < 2^64
    static const ll test_bases[] = {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL};
    for (ll a : test_bases) {
        if (!mr(a, n)) return false;
    }
    return true;
}
// Pollard's Rho 求非平凡因數
ll rho(ll p) {
    if (p % 2 == 0) return 2;
    ll x, y, c, d = 1;
    x = y = rand() % (p - 1) + 1;
    c = rand() % (p - 1) + 1;
    while (d == 1) {
        x = (ksc(x, x, p) + c) % p;
        y = (ksc(y, y, p) + c) % p;
        y = (ksc(y, y, p) + c) % p;
        d = gcd(abs(x - y), p);
    }
    return d == p ? rho(p) : d;
}

// 收集質因數
void factorize(ll n, vector<ll> &factors) {
    if (n == 1) return;
    if (Prime(n)) {
        factors.push_back(n);
        return;
    }
    ll d = rho(n);
    factorize(d, factors);
    factorize(n / d, factors);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    srand(time(0));
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> factors;
        factorize(n, factors);
        sort(factors.begin(), factors.end());
        for (size_t i = 0; i < factors.size(); ++i) {
            if (i) cout << " × ";
            cout << factors[i];
        }
        cout << "\n";
        cout<<Prime(n)<<"\n";
    }
    return 0;
}

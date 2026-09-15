#include <bits/stdc++.h>
using namespace std;

inline void normalize(string &s) {
    size_t i = 0, n = s.size();
    while (i + 1 < n && s[i] == '0') ++i;
    if (i) s.erase(0, i);
}

inline int compare_str(const string &a, const string &b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    return (a < b) ? -1 : (a > b) ? 1 : 0;
}


string subtract_str(string a, const string &b) {
    int n = a.size(), m = b.size(), carry = 0;
    for (int i = 0; i < n; ++i) {
        int ai = a[n-1-i] - '0';
        int bi = (i < m ? b[m-1-i] - '0' : 0);
        int diff = ai - bi - carry;
        carry = diff < 0;
        if (carry) diff += 10;
        a[n-1-i] = char(diff + '0');
    }
    normalize(a);
    return a;
}


string divide2(const string &s) {
    int n = s.size();
    string res;
    res.reserve(n);
    int carry = 0;
    for (int i = 0; i < n; ++i) {
        int v = carry * 10 + (s[i] - '0');
        res.push_back(char((v >> 1) + '0'));
        carry = v & 1;
    }
    normalize(res);
    return res;
}


string multiply2(const string &s) {
    int n = s.size(), carry = 0;
    string res;
    res.reserve(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        int v = (s[i] - '0') * 2 + carry;
        carry = v / 10;
        res.push_back(char((v % 10) + '0')); 
    }
    if (carry) res.push_back(char(carry + '0'));
    reverse(res.begin(), res.end());
    normalize(res);
    return res;
}

inline bool is_even(const string &s) {
    return ((s.back() - '0') & 1) == 0;
}

string binary_gcd(string a, string b) {
    normalize(a);
    normalize(b);
    if (a == "0") return b;
    if (b == "0") return a;

    int shift = 0;
    while (is_even(a) && is_even(b)) {
        a = divide2(a);
        b = divide2(b);
        ++shift;
    }
    while (is_even(a)) a = divide2(a);

    while (b != "0") {
        while (is_even(b)) b = divide2(b);
        if (compare_str(a, b) > 0) swap(a, b);
        b = subtract_str(b, a);
    }
    for (int i = 0; i < shift; ++i) a = multiply2(a);
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    if (cin >> a >> b) {
        cout << binary_gcd(a, b);
    }
    return 0;
}

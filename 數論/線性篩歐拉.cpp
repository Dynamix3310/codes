#include <vector>
using namespace std;

const int MAXN = 1000005;
int phi[MAXN];
int primes[MAXN];
bool is_prime[MAXN];
int cnt = 0;

void get_phi() {
    fill(is_prime + 2, is_prime + MAXN, true);
    phi[1] = 1;
    
    for (int i = 2; i < MAXN; ++i) {
        if (is_prime[i]) {
            primes[cnt++] = i;
            phi[i] = i - 1; // 質數的歐拉函數為自身減 1
        }
        for (int j = 0; j < cnt && i * primes[j] < MAXN; ++j) {
            int p = primes[j];
            is_prime[i * p] = false;
            
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break; // 確保每個合數只被最小質因數篩掉，維持線性複雜度
            } else {
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
}

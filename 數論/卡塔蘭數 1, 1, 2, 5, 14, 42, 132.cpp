#include <bits/stdc++.h>

using namespace std;

# define FOR(i, a, b) for(int i = a; i <= b; i++)
# define _FOR(i, a, b) for(int i = a; i >= b; i--)

const int NR = 100000;

int n;
long long catalan[NR + 10];

int main()
{
	scanf("%d", &n);
	catalan[0] = catalan[1] = 1;
	FOR(i, 2, n)
		FOR(j, 0, i - 1)
			catalan[i] += catalan[j] * catalan[i - j - 1];
	printf("%lld\n", catalan[n]);
	return 0;
}



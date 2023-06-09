#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using ll = long long;

int dp[1500001];

int main() {
	ll N;
	scanf("%lld", &N);
	
	dp[1] = 1;
	dp[2] = 1;
	for (int i = 3; i <= 1500000 - 1; ++i)
		dp[i] = (dp[i - 1] + dp[i - 2])%1000000;

	printf("%d", dp[N % 1500000]);
	return 0;
}
#define CRT_SECURE_NO_WARNINGS
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
using namespace std;
using ll = long long;

ll A, B;

ll gcd(ll a, ll b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

// 최소 공배수
ll lcm(ll a, ll b) {
	return a * b / gcd(a, b);
}

void solve() {
	ll res = lcm(A, B);

	cout << res << '\n';
}

int main() {
	fastIO;
	cin >> A >> B;
	solve();

	return 0;
}
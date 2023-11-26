#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

#define MXN 500000

int N, M;
int arr[MXN];
unordered_map<int, int> um;

void input() {
	cin >> N;
	for (int i = 0; i < N; ++i) { 
		cin >> arr[i];
		int num = arr[i];
		um[num]++;
	}
	cin >> M;
}

void solve() {
	sort(arr, arr + N);
	int ans = 0;
	for (int i = 0; i < M; ++i) {
		int tgt = -1;
		ans = 0;
		cin >> tgt;
		if (um.find(tgt) != um.end()) {
			cout << um[tgt] << ' ';
		}
		else {
			cout << 0 << ' ';
		}
	}
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}
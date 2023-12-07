#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;

int N;

void solve() {
	cin >> N;
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		if (num > 0) {
			pq.push(num);
		}
		else if (num == 0) {
			if (!pq.empty()) {
				cout << pq.top() << '\n';
				pq.pop();
			}
			else {
				cout << "0\n";
			}
		}
	}
}

int main() {
	fastIO;
	solve();
	return 0;
}
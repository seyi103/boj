#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <algorithm>
using namespace std;

#define MXN 100000

int N, M;
int arr[MXN];

void input() {
	cin >> N;
	for (int i = 0; i < N; ++i) { cin >> arr[i];}
	cin >> M;
}

void solve() {
	sort(arr, arr + N);
	bool flag = 0;
	for (int i = 0; i < M; ++i) {
		int tgt = -1;
		flag = 0;
		cin >> tgt;
		int left = 0, right = N - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (arr[mid] == tgt) {
				flag = 1;
				break;
			}
			else if(tgt < arr[mid]) {
				right = mid - 1;
			}
			else if (tgt > arr[mid]) {
				left = mid + 1;
			}
		}
		cout << flag << '\n';
	}
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}
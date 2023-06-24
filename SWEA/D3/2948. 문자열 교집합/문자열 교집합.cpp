#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
	fastIO;
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		int N, M;
		unordered_map<string, int> um;
		int cnt = 0;
		string str;
		// input + solve
		cin >> N >> M;
		for (int i = 0; i < N; i++) {
			cin >> str;
			um[str] = 1;
		}
		for (int i = 0; i < M; i++) {
			cin >> str;
			if (um.find(str) != um.end())
				um[str]++, cnt++;
			else
				um[str] = 1;
		}
		// output
		cout << '#' << tc << ' ' << cnt << '\n';
	}
	return 0;
}
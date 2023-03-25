#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int N;
string MAP[51];
int visited[51][51];
int ans;

void check() {
	// 가로 카운트
	for (int i = 0; i < N; i++) {
		int cnt = 1;
		for (int j = 0; j < N; j++) {
			char now = MAP[i][j];
			char next = MAP[i][j + 1];
			if (now == next) 
				cnt++;
			else {
				ans = max(ans, cnt);
				cnt = 1;
			}
		}
	}

	// 세로 카운트
	for (int j = 0; j < N; j++) {
		int cnt = 1;
		for (int i = 0; i < N; i++) {
			char now = MAP[i][j];
			char next = MAP[i+1][j];
			if (now == next) 
				cnt++;
			else {
				ans = max(ans, cnt);
				cnt = 1;
			}
		}
	}
}

int main() {
	fastIO;

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> MAP[i];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++) {
			if (ans == N)
				break;
			if (MAP[i][j] != MAP[i][j + 1]) {
				swap(MAP[i][j], MAP[i][j + 1]);
				check();
				swap(MAP[i][j], MAP[i][j + 1]);
			}
			if (MAP[j][i] != MAP[j + 1][i]) {
				swap(MAP[j][i], MAP[j + 1][i]);
				check();
				swap(MAP[j][i], MAP[j + 1][i]);
			}
		}
		if (ans == N)
			break;
	}
	cout << ans;
	return 0;
}
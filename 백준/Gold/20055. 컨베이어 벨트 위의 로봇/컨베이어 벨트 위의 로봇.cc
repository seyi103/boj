#define _CRT_SECURE_NO_WARNINGS
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;

int N, K;
int belt[201];
int robot[201];
int bcnt;
int flag;

void input() {
	cin >> N >> K;
	for (int i = 0; i < 2 * N; i++) {
		cin >> belt[i];
	}
}

void rotate(int& s, int& e) {
	// 벨트 회전
	if (s <= 0)
		s = 2 * N - 1;
	else
		s--;
	if (e <= 0)
		e = 2 * N - 1;
	else
		e--;
	
	if (robot[e])
		robot[e] = 0;
}

void MOVE(int s, int e) {
	int idx = e;
	for (int i = 0; i < N - 1; i++) {
		int next = idx;
		if (!idx)
			idx = 2 * N - 1;
		else
			idx--;

		if (!robot[next] && robot[idx] && belt[next] > 0) {
			belt[next]--;
			if (belt[next] <= 0) {
				bcnt++;
				if (bcnt >= K) {
					flag = 1;
					break;
				}
			}
			robot[next] = 1;
			robot[idx] = 0;
		}
	}
	robot[e] = 0;
}

void MAKE(int s) {
	if (belt[s]) {
		belt[s]--;
		
		if (belt[s] <= 0) {
			bcnt++;
			if (bcnt >= K) {
				flag = 1;
			}
		}
		robot[s] = 1;
	}
}

void solve() {
	int sidx = 0; // 로봇이 올라가는 index
	int didx = N - 1; // 하차하는 index
	int ord = 1;

	while (true)
	{
		rotate(sidx, didx);
		MOVE(sidx, didx);
		int de = 1;
		MAKE(sidx);
		if (flag)
			break;
		ord++;
	}
	cout << ord << '\n';
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}
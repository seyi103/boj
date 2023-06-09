#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct Node {
	int y, x;
};

int R, C, N;
int MAP[201][201];

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

void input() {
	cin >> R >> C >> N;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			char tmp;
			cin >> tmp;
			if (tmp == '.') MAP[i][j] = 0;
			else MAP[i][j] = 3;
		}
	}
}

void print() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (MAP[i][j])
				cout << 'O';
			else
				cout << '.';
		}
		cout << '\n';
	}
}

void putBoom(int t) {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (MAP[i][j]) continue;
			MAP[i][j] = t + 3;
		}
	}
}

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= R || x >= C;
}

void boom(int t) {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (MAP[i][j] == t) {
				MAP[i][j] = 0;
				for (int d = 0; d < 4; d++) {
					int ny = i + ydir[d];
					int nx = j + xdir[d];

					if (outRange(ny, nx)) continue;
					if (MAP[ny][nx] == t) continue;
					MAP[ny][nx] = 0;
				}
			}
		}
	}
}

void solve() {
	for (int i = 2; i <= N; i++) {
		if (i % 2 == 0) 
			putBoom(i);
		
		else 
			boom(i);
		
	}
	print();
}

int main() {
	fastIO;
	// input
	input();
	// solve
	solve();

	return 0;
}
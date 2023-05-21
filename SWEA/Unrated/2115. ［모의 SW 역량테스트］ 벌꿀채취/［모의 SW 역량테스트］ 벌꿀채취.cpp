#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Honey {
	int y, sx, ex;
	int cost;
};

int N, M, C;
int MAP[11][11];
vector<Honey> h;
int tmp;

void init() {
	memset(MAP, 0, sizeof(MAP));
	h.clear();
}

void input() {
	cin >> N >> M >> C;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}
}

void dfs(int y, int x, int dx, int sum, int now) {
	// 가지치기
	if (now > C)
		return;

	// 재귀 구성
	if (x == dx) {
		if (tmp < sum)
			tmp = sum;
		return;
	}
	// 재취한다
	dfs(y, x + 1, dx, sum + MAP[y][x] * MAP[y][x], now + MAP[y][x]);
	// 안한다
	dfs(y, x + 1, dx, sum, now);
}

int solve() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= N - M; j++) {
			tmp = 0;
			dfs(i, j, j + M, 0, 0);
			h.push_back({ i, j, j + M - 1, tmp });
		}
	}

	int res = -21e8;
	int ed = h.size();
	for (int i = 0; i < ed; i++) {
		for (int j = i + 1; j < ed; j++) {
			Honey A = h[i], B = h[j];
			if (A.y == B.y && (A.ex <= B.sx || A.sx <= B.ex))
				continue;
			int sum = A.cost + B.cost;
			if (sum > res)
				res = sum;
		}
	}
	return res;
}

int main() {
	fastIO;
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		init();
		// input
		input();
		// solve
		int ans = solve();
		// output
		cout << '#' << tc << ' ' << ans << '\n';
	}

	return 0;
}
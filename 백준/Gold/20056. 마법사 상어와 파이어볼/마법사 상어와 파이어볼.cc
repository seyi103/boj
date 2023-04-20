#define _CRT_SECURE_NO_WARNINGS
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Fire {
	int m;
	int s;
	int d;
};

int ydir[] = { -1,-1,0,1,1,1,0,-1 };
int xdir[] = { 0,1,1,1,0,-1,-1,-1 };

int N, M, K;
vector<Fire> MAP[100][100];
vector<Fire> COPY[100][100];

void input() {
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		int y, x, m, s, d;
		cin >> y >> x >> m >> s >> d;
		MAP[y - 1][x - 1].push_back({m, s, d});
	}
}

void MOVE() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!MAP[i][j].size())
				continue;

			for (int s = 0; s < MAP[i][j].size(); s++) {
				Fire now = MAP[i][j][s];
				int ny = i + ydir[now.d] * now.s;
				int nx = j + xdir[now.d] * now.s;

				ny = (ny + 1000*N) % N;
				nx = (nx + 1000*N) % N;

				COPY[ny][nx].push_back(now);
			}
		}
	}
}

void fusion() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (COPY[i][j].size() >= 2) {
				int m_sum = 0, s_sum = 0, dir[2] = { 0, };
				int cnt = COPY[i][j].size();

				for (int t = 0; t < cnt; t++) {
					Fire now = COPY[i][j][t];

					m_sum += now.m;
					s_sum += now.s;
					dir[now.d % 2]++;
				}

				int m = m_sum / 5;
				int s = s_sum / cnt;
				COPY[i][j].clear();

				if (m == 0)
					continue;
				if (dir[0] == cnt || dir[1] == cnt) {
					for (int d = 0; d < 4; d++) {
						COPY[i][j].push_back({ m, s, d * 2 });
					}
				}
				else {
					for (int d = 0; d < 4; d++) {
						COPY[i][j].push_back({ m, s, d * 2 + 1 });
					}
				}
			}
		}
	}
	memset(MAP, 0, sizeof(MAP));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < COPY[i][j].size(); k++) {
				Fire now = COPY[i][j][k];
				MAP[i][j].push_back(now);
			}
		}
	}
}

int getSum() {
	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!MAP[i][j].size())
				continue;
			for (int s = 0; s < MAP[i][j].size(); s++)
				sum += MAP[i][j][s].m;
		}
	}
	return sum;
}

void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			COPY[i][j].clear();
	}
}

void solve() {
	int res = 0;
	for (int k = 0; k < K; k++) {
		init();
		// 이동
		MOVE();
		// 융합
		fusion();
		int tmp = getSum();
		int de = 1;
	}
	res = getSum();
	cout << res << '\n';
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}
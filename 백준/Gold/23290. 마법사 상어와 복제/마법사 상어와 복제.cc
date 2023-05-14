#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int y, x;
};

struct Fish {
	int y, x;
	int dir;
};

int S, M;
vector<Fish> MAP[4][4]; // 물고기가 있는 칸
int sMAP[4][4]; // 상어, 물고기 냄새 정보
int flag;

int fydir[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int fxdir[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };

int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,-1,0,1 };

int sy, sx;
int path[3], tmppath[3];
int MAX;
int chDir[8] = { 7,0,1,2,3,4,5,6 };

void input() {
	cin >> M >> S;
	for (int i = 0; i < M; i++) {
		int y, x, d;
		cin >> y >> x >> d;
		y--, x--, d--;
		Fish now = { y, x, d };
		MAP[y][x].push_back(now);
	}
	cin >> sy >> sx;
	sy--, sx--;
}

void cpyMap(vector<Fish> A[][4], vector<Fish> B[][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			A[i][j] = B[i][j];
		}
	}
}

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= 4 || x >= 4;
}

bool check(int y, int x) {
	return !outRange(y, x) && (y != sy || x != sx) && !sMAP[y][x];
}

void fmove() {
	vector<Fish> tmp[4][4];
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < MAP[i][j].size(); k++) {
				int y = MAP[i][j][k].y;
				int x = MAP[i][j][k].x;
				int dir = MAP[i][j][k].dir;

				int ny = y, nx = x;
				int flag = 0;

				for (int d = 0; d < 8; d++) {
					ny = y + fydir[dir];
					nx = x + fxdir[dir];

					if (check(ny, nx)) {
						flag = 1;
						break;
					}

					dir = chDir[dir];
				}
				if (flag) {
					Fish now = { ny, nx, dir };
					tmp[ny][nx].push_back(now);
				}
				else {
					Fish now = { y, x, dir };
					tmp[y][x].push_back(now);
				}
			}
		}
	}

	cpyMap(MAP, tmp);
}

void smove(int time) {
	vector<Fish> tmp[4][4];
	cpyMap(tmp, MAP);

	int y = sy, x = sx;

	for (int i = 0; i < 3; i++) {
		int dir = path[i];
		int ny = y + ydir[dir];
		int nx = x + xdir[dir];
		if (tmp[ny][nx].size() != 0) {
			sMAP[ny][nx] = time;
			tmp[ny][nx].clear();
		}
		
		y = ny;
		x = nx;
		sy = y;
		sx = x;
	}
	cpyMap(MAP, tmp);
}

int simul() {
	int visited[4][4] = { 0, };
	int y = sy, x = sx;
	int eat = 0;

	for (int i = 0; i < 3; i++) {
		int dir = tmppath[i];
		int ny = y + ydir[dir];
		int nx = x + xdir[dir];

		if (outRange(ny, nx))
			return -1;
		if (visited[ny][nx])
			continue;

		visited[ny][nx] = 1;
		eat += MAP[ny][nx].size();
		y = ny, x = nx;
	}
	return eat;
}

void dfs(int now) {
	if (now == 3) {
		int tmp = simul();
		if (tmp > MAX) {
			for (int i = 0; i < 3; i++) {
				path[i] = tmppath[i];
			}
			MAX = tmp;
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		tmppath[now] = i;
		dfs(now + 1);
	}
}

void shark(int time) {
	MAX = -1;
	dfs(0);
	smove(time);
}

void checkSmell(int time) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (sMAP[i][j] + 2 <= time)
				sMAP[i][j] = 0;
		}
	}
}

void addFish(vector<Fish> COPY[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < COPY[i][j].size(); k++) {
				Fish now = COPY[i][j][k];
				MAP[i][j].push_back(now);
			}
		}
	}
}

int getAns() {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int now = MAP[i][j].size();
			if (!now) continue;
			sum += now;
		}
	}
	return sum;
}

void solve() {
	for (int i = 1; i <= S; i++) {
		// #1. 물고기 복사
		vector<Fish> COPY[4][4]; 
		cpyMap(COPY, MAP);
		// #2. 물고기 이동
		fmove();
		// #3. 상어 이동
		shark(i);
		// #4. 냄새 bye
		checkSmell(i);
		// #5. 1에 복사한 물고기 생김
		addFish(COPY);
	}
	int res = getAns();

	cout << res << '\n';
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}
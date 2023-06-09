#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;

#define MXN 21

int ydir[] = { -1,0,1,0 };
int xdir[] = { 0,1,0,-1 };

struct Node {
	int y, x;
};

struct Dice {
	int y, x;
	int dir;
	int top, bottom, up, down, right, left;

	Dice() {
		y = 0, x = 0;
		top = 1, bottom = 6, up = 5, down = 2, left = 4, right = 3;
		dir = 1;
	}
	void changeDice() {
		int t_tmp, b_tmp, u_tmp, d_tmp, r_tmp, l_tmp;
		// 상
		if (dir == 0) {
			t_tmp = top, b_tmp = bottom;
			top = up, bottom = down;
			up = b_tmp, down = t_tmp;
		}
		// 우
		else if (dir == 1) {
			t_tmp = top, b_tmp = bottom;
			top = left, bottom = right;
			left = b_tmp, right = t_tmp;
		}
		// 하
		else if (dir == 2) {
			t_tmp = top, b_tmp = bottom;
			top = down, bottom = up;
			up = t_tmp, down = b_tmp;
		}
		// 좌
		else {
			t_tmp = top, b_tmp = bottom;
			top = right, bottom = left;
			left = t_tmp, right = b_tmp;
		}
	}
};


int N, M, K;
int MAP[MXN][MXN];

Dice dice;

void input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> MAP[i][j];
}

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= M;
}

int bfs(int y, int x) {
	int num = MAP[y][x];
	queue<Node> q;
	q.push({ y, x });

	int visited[MXN][MXN] = { 0, };
	visited[y][x] = 1;

	int area = 1;

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (outRange(ny, nx)) continue;
			if (MAP[ny][nx] != num) continue;
			if (visited[ny][nx]) continue;

			area++;
			visited[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}
	return area;
}

void roll() {
	int ndir = dice.dir;
	int ny = dice.y + ydir[ndir];
	int nx = dice.x + xdir[ndir];

	while (outRange(ny, nx)) {
		ndir ^= 2;

		ny = dice.y + ydir[ndir];
		nx = dice.x + xdir[ndir];
	}
	dice.y = ny, dice.x = nx, dice.dir = ndir;
	dice.changeDice();
}

void getDir() {
	int A = dice.bottom;
	int B = MAP[dice.y][dice.x];
	if (A > B) dice.dir = (dice.dir + 1) % 4;
	else if (A < B) {
		dice.dir--;
		if (dice.dir < 0) dice.dir = 3;
	}
}

void solve() {
	int score = 0;
	for (int k = 1; k <= K; k++) {
		if (k == 7) 
			int de = 1;
		// #1. 주사위가 이동방향으로 굴러감
		roll();		
		// #2. 도착칸의 점수 획득
		int cnt = bfs(dice.y, dice.x);
		int num = MAP[dice.y][dice.x];
		score += (cnt * num);
		// #3. 이동방향 결정
		getDir();
	}
	cout << score << '\n';
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}
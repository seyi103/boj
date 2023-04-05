#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

struct Node {
	int y, x;
	int time;
};

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int N;
int MAP[21][21];
int sy, sx;
int dy, dx;
int ans = 21e8;

void init() {
	memset(MAP, 0, sizeof(MAP));
	ans = 21e8;
}

void input() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			scanf("%d", &MAP[i][j]);
		}
	scanf("%d %d", &sy, &sx);
	scanf("%d %d", &dy, &dx);
}

void bfs(int y, int x) {
	queue<Node> q;
	q.push({ y, x, 0 });

	int visited[21][21] = { 0, };
	visited[y][x] = 1;

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();
		if (now.y == dy && now.x == dx)
			if (ans > now.time) ans = now.time;
		visited[now.y][now.x] = 1;
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N)
				continue;
			if (MAP[ny][nx] == 1)
				continue;
			if (visited[ny][nx])
				continue;
			int ntime = now.time;
			if (MAP[ny][nx] == 2 && (ntime - 2) % 3 != 0) {
				// 소용돌이를 기다린다
				while ((ntime - 2) % 3 != 0)
					ntime++;
			}
			q.push({ ny, nx, ntime + 1 });
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		// reset
		init();

		// input
		input();
		// solve
		bfs(sy, sx);
		// output
		if (ans == 21e8)
			ans = -1;
		printf("#%d %d\n", tc, ans);
	}

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <stdio.h>
using namespace std;

struct Node {
	int y, x;
	int dust;
};

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int N, M, T;
int MAP[2][51][51];

int uy, ux; // 공기 청정기위 위쪽 좌표
int dy, dx; // 아래쪽 좌표
int cnt;

void spread(int cur) {
	int next = (cur + 1) % 2;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			if (MAP[cur][i][j] == -1)
				MAP[next][i][j] = -1;
			else
				MAP[next][i][j] = 0;
		}

	for (int i = -0; i < N; i++)
		for (int j = 0; j < M; j++) {
			int tmp = MAP[cur][i][j] / 5;
			int store = 0;
			// 4방향 확산
			for (int d = 0; d < 4; d++) {
				int ny = i + ydir[d];
				int nx = j + xdir[d];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M)
					continue;
				if (MAP[cur][ny][nx] == -1)
					continue;

				MAP[next][ny][nx] += tmp;
				store += tmp;
			}
			if (MAP[next][i][j] != -1)
				MAP[next][i][j] += MAP[cur][i][j] - store;
		}
}

void move(int cur) {
	// 위 -> 아래
	for (int i = uy - 1; i > 0; i--)
		MAP[cur][i][0] = MAP[cur][i - 1][0];
	// 오른쪽 -> 왼쪽
	for (int j = 0; j < M - 1; j++)
		MAP[cur][0][j] = MAP[cur][0][j + 1];
	// 아래 -> 위
	for (int i = 0; i < uy; i++)
		MAP[cur][i][M - 1] = MAP[cur][i + 1][M - 1];
	// 왼쪽 -> 오른쪽
	for (int j = M - 1; j > 0; j--)
		MAP[cur][uy][j] = MAP[cur][uy][j - 1];

	MAP[cur][uy][1] = 0;

	// 아래 -> 위
	for (int i = dy + 1; i < N; i++)
		MAP[cur][i][0] = MAP[cur][i + 1][0];
	// 오른쪽 -> 왼
	for (int j = 0; j < M - 1; j++)
		MAP[cur][N - 1][j] = MAP[cur][N - 1][j + 1];
	// 위 -> 아래
	for (int i = N - 1; i > dy; i--)
		MAP[cur][i][M - 1] = MAP[cur][i - 1][M - 1];
	// 왼쪽 -> 오른쪽
	for (int j = M - 1; j > 1; j--)
		MAP[cur][dy][j] = MAP[cur][dy][j - 1];

	MAP[cur][dy][1] = 0;
}

void solve() {
	int cur = 0;
	for (int t = 0; t < T; t++) {
		// 현재 맵에 미세먼지를 확신 시키자
		spread(cur);
		// 확산시킨 맵을 다음맵으로 옮기자!
		cur = (cur + 1) % 2;
		move(cur);
	}
	int cnt = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			if (MAP[cur][i][j] != -1) {
				cnt += MAP[cur][i][j];
			}
		}

	printf("%d\n", cnt);
}

int main() {
	uy = -1;
	scanf("%d %d %d", &N, &M, &T);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			scanf("%d", &MAP[0][i][j]);
			if (MAP[0][i][j] == -1) {
				if (uy == -1)
					uy = i, ux = j;
				else
					dy = i, dx = j;
			}
		}
	solve();
	return 0;
}
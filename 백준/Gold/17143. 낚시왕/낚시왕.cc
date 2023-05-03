#define _CRT_SECURE_NO_WARNINGS

//#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

#include <iostream>
#include <vector>

using namespace std;

struct Shark {

	int y, x;	int s, dir;

	int SIZE;

};

vector<int> MAP[101][101];

int R, C, M;

// 상하우좌

int ydir[] = { -1,1,0,0 };

int xdir[] = { 0,0,1,-1 };

Shark shark[10001];

int res;

void input() {

    scanf("%d %d %d", &R, &C, &M);
	for (int i = 1; i <= M; i++) {
		int y, x, s, d, SIZE;
        scanf("%d %d %d %d %d", &y, &x, &s,&d, &SIZE);
		y--, x--, d--;

		shark[i] = { y, x, s, d, SIZE };

	}

}

bool outRange(int y, int x) {

	return y < 0 || x < 0 || y >= R || x >= C;

}

void sMOVE() {

	// 이동 맵 초기화

	for (int i = 1; i <= M; i++) {

		Shark now = shark[i];

		if (now.SIZE == -1)

			continue;

		MAP[now.y][now.x].clear();

	}

	for (int i = 1; i <= M; i++) {

		Shark now = shark[i];

		// 죽은 상어면 continue

		if (now.SIZE == -1)

			continue;
int ed = now.s;
        int dir = now.dir;
        if(dir == 0|| dir == 1){
            ed=ed%((R-1)*2);
            }
        else
            ed = ed % ((C-1)*2);
		for (int s = 0; s < ed; s++) {

			now.y += ydir[dir];

			now.x += xdir[dir];

			if (outRange(now.y, now.x)) {

				now.y -= ydir[dir];

				now.x -= xdir[dir];

				if (dir % 2 == 0) dir += 1;

				else dir -= 1;

				now.y += ydir[dir];

				now.x += xdir[dir];

				shark[i].dir = dir;

			}

		}

		MAP[now.y][now.x].push_back(i);
now.dir = dir;
		shark[i] = now;

	}

}

void eatShark() {

	for (int i = 1; i <= M; i++) {

		Shark now = shark[i];

		if (now.SIZE == -1)

			continue;

		int y = now.y;

		int x = now.x;

		if (MAP[y][x].size() > 1) {

			int sMAX = 0, mxNum = 0;

			Shark tmp;

			for (int j = 0; j < MAP[y][x].size(); j++) {

				int num = MAP[y][x][j];

				if (shark[num].SIZE > sMAX) {

					sMAX = shark[num].SIZE;

					tmp = shark[num];

					mxNum = num;

				}

				shark[num].SIZE = -1;

			}

			shark[mxNum].SIZE = sMAX;

		}

	}

}

int getShark(int x) {

	int MINY = 200, num = 0;

	int s = 0;

	for (int i = 1; i <= M; i++) {

		Shark now = shark[i];

		if (now.SIZE == -1)

			continue;

		if (now.x != x)

			continue;

		if (now.y < MINY) {

			MINY = now.y;

			num = i;

			s = now.SIZE;

		}

	}

	if(num == 0)

		return 0;

	shark[num].SIZE = -1;

	return s;

}

void solve() {

	for (int pos = 0; pos < C; pos++) {

		// 상어 잡기

		res += getShark(pos);

		// 상어 이동

		sMOVE();

		// 상어끼리 잡아먹는다

		eatShark();

	}

    printf("%d\n", res);
}

int main() {
	//freopen("input.txt", "r", stdin);

	input();

	solve();

	return 0;

}
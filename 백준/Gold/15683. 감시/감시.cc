#include <stdio.h>
#include <vector>

using namespace std;

int N, M;
int MAT[9][9];

vector <pair<int, int>> vec;

int dr[] = { -1,0,1,0 };
int dc[] = { 0,-1,0,1 };

int ans;

void monitoring(int r, int c, int d, int org, int chg) { // 감시 지역 마킹
	while (true) {
		r = r + dr[d]; c = c + dc[d];
		if (r < 0 || r >= N || c < 0 || c >= M || MAT[r][c] == 6) {
			break;
		}
		if (MAT[r][c] == org) {
			MAT[r][c] = chg;
		}
	}
}

void opt(int r, int c, int d, int org, int chg) { // CCTV가 감시할 지역 마킹
	if (MAT[r][c] == 1) { // 1번 CCTV인 경우
		monitoring(r, c, d, org, chg);
	}
	else if (MAT[r][c] == 2) { // 2번 CCTV인 경우
		monitoring(r, c, d, org, chg);
		monitoring(r, c, (d + 2) % 4, org, chg);
	}
	else if (MAT[r][c] == 3) { // 3번 CCTV인 경우
		monitoring(r, c, d, org, chg);
		monitoring(r, c, (d + 1) % 4, org, chg);
	}
	else if (MAT[r][c] == 4) { // 4번 CCTV인 경우
		monitoring(r, c, d, org, chg);
		monitoring(r, c, (d + 1) % 4, org, chg);
		monitoring(r, c, (d + 3) % 4, org, chg);
	}
}

void dfs(int num){ //감시 지역 탐색!
	if (num == vec.size()) {
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (MAT[i][j] == 0) {
					cnt++;
				}
			}
		}
		if (ans > cnt) {
			ans = cnt;
		}
	}
	else {
		int r = vec[num].first; int c = vec[num].second;
		for (int i = 0; i < 4; i++) {
			opt(r, c, i, 0, -(num + 1)); // n 번째 CCTV가 감시할 지역을 -(n+1)로 마킹
			dfs(num + 1);
			opt(r, c, i, -(num + 1), 0); //원상복귀
		}
		//dfs(num + 1);
		
	}
}

int main() {
	scanf("%d %d", &N, &M);
	vec.clear();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &MAT[i][j]);
			if (MAT[i][j] >= 1 && MAT[i][j] <= 5) {
				vec.push_back(make_pair(i, j)); // CCTV 위치 저장
			}
		}
	}
	int num_cctv = vec.size();
	for (int i = num_cctv - 1; i >= 0; i--) { //5번 타입 CCTV 유무 확인
		int x = vec[i].first; int y = vec[i].second;
		if (MAT[x][y] == 5) { //5번 타입의 CCTV 라면 감시지역을 -10으로 체크 
			for (int n = 0; n < 4; n++) {
				monitoring(x, y, n, 0, -10);
			}
			vec.erase(vec.begin() + i); //5번 타입 CCTV 위치 삭제
		}
	}
	ans = 64;
	dfs(0); // 감시지역 탐색
	printf("%d", ans);
}
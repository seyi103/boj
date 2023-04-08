#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int K;
int magnet[4][8];
int rcnt[4];
int dir[4];

void rotate() {
    for (int i = 0; i < 4; i++) {
        if (dir[i] != 0) {
            if (dir[i] == 1) {
                rcnt[i]--;
            }
            else {
                rcnt[i]++;
            }
        }
    }
}

// n번 자석으로 d 방향으로 돌릴때 다른 자석은 어떤 방향으로 돌아야하는가?
void calcDir(int n, int d) {
    memset(dir, 0, sizeof(dir));
    dir[n] = d;
    // n 기준 왼쪽 확인
    for (int i = n - 1; i >= 0; i--) {
        int idx1 = 2 + rcnt[i], idx2 = 6 + rcnt[i + 1];
        if (idx1 < 0) idx1 = (idx1 + 160) % 8;
        if (idx2 < 0) idx2 = (idx2 + 160) % 8;
        if (magnet[i][idx1 % 8] != magnet[i + 1][idx2 % 8]) {
            dir[i] = -dir[i + 1];
        }
    }

    // n 기준 오른쪽 확인
    for (int i = n + 1; i < 4; i++) {
        int idx1 = 2 + rcnt[i - 1], idx2 = 6 + rcnt[i];
        if (idx1 < 0) idx1 = (idx1 + 160) % 8;
        if (idx2 < 0) idx2 = (idx2 + 160) % 8;
        if (magnet[i - 1][idx1 % 8] != magnet[i][idx2 % 8])
            dir[i] = -dir[i - 1];
    }
    rotate();
}

void input() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            char ch;
            cin >> ch;
            magnet[i][j] = ch - '0';
        }
    }
    cin >> K;
    for (int i = 0; i < K; i++) {
        int num, dir;
        cin >> num >> dir;
        calcDir(num - 1, dir);
    }
}

int solve() {
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        int idx = rcnt[i];
        if (idx < 0) idx = (idx + 160) % 8;
        int num = magnet[i][idx % 8];
        if (num == 1) {
            sum += (1 << i);
        }
    }
    return sum;
}

int main() {
	// input
	input();
	// solve
	int ans = solve();
	// output
	cout << ans << '\n'; 

    return 0;
}
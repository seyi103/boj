#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
int X;
int MAP[2][101][101];

void input() {
    cin >> N >> X;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> MAP[0][i][j];
            MAP[1][j][i] = MAP[0][i][j];
        }
    }
}

int solve() {
    int res = 0;

    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < N; i++) {
            int cnt = 1;
            int flag = 1;
            for (int j = 1; flag && j < N; j++) {
                int diff = MAP[k][i][j] - MAP[k][i][j - 1];

                if (abs(diff) > 1)
                    flag = 0;
                // 같은 높이면 길이 추가
                else if (diff == 0)
                    cnt++;
                // 내리막이면
                else if (diff == -1) {
                    if (cnt < 0) flag = 0;
                    cnt = -X + 1;
                }
                // 오르막이면 X만큼이 확보되어 있어야 한다.
                else if (diff == 1) {
                    if (cnt < X) flag = 0;
                    cnt = 1;
                }
            }
            if (!flag || cnt < 0)
                continue;
            res++;
        }
    }

    return res;
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
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

struct Honey {
    int cost;
    int y;
    int sx;
    int ex;
};

int N, M; // 맵크기, 선택가능한 개수
int MAP[11][11];
int C; // 채취 가능한 최대 양
int tmp;
vector<Honey> h; // 채취 가능한 최대 꿀양들을 담아 놓을 vector

void INIT() {
    memset(MAP, 0, sizeof(MAP));
    h.clear();
}

void input() {
    cin >> N >> M >> C;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> MAP[i][j];
}

void dfs(int y, int sx, int ex, int sum, int now) {
    // 채취하려는 합이 C보다 크면 못함
    if (now > C)
        return;

    if (sx == ex) {
        tmp = max(tmp, sum);
        return;
    }

    // 꿀을 채취
    dfs(y, sx + 1, ex, sum + MAP[y][sx] * MAP[y][sx], now + MAP[y][sx]);
    // 채취하지 않음
    dfs(y, sx + 1, ex, sum, now);
}

void getHoney() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N - M; j++) {
            tmp = 0;
            dfs(i, j, j + M, 0, 0);
            h.push_back({ tmp, i, j, j + M - 1 });
        }
    }
}

void findMax(int& res) {
    for (int i = 0; i < h.size(); i++) {
        for (int j = i + 1; j < h.size(); j++) {
            Honey A = h[i], B = h[j];
            if (A.y == B.y && (A.ex <= B.sx || A.sx <= B.ex))
                continue;
            res = max(res, A.cost + B.cost);
        }
    }
}

int solve() {
    int res = 0;
    getHoney();
    findMax(res);
    return res;
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        // reset
        INIT();
        // input
        input();
        // solve
        int ans = solve();
        // output
        cout << '#' << tc << ' ' << ans << '\n';
    }
    return 0;
}
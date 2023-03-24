#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <bits/stdc++.h>
using namespace std;

int ydir[] = { -2,-2,-1,-1,1,1,2,2 };
int xdir[] = { -1,1,-2,2,-2,2,-1,1 };

struct Node {
    int y, x;
};

int N;
int visited[305][305];
int dy, dx;

int bfs(int y, int x) {
    if (y == dy && x == dx)
        return 0;

    queue<Node> q;
    q.push({ y, x });

    visited[y][x] = 1;

    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 8; i++) {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                continue;

            if (visited[ny][nx])
                continue;

            if (ny == dy && nx == dx)
                return visited[now.y][now.x];

            visited[ny][nx] = visited[now.y][now.x] + 1;
            q.push({ ny, nx });
        }
    }
}

int main() {
    fastIO;
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        // reset
        memset(visited, 0, sizeof(visited));
        int sy, sx;
        
        // input
        cin >> N;
        cin >> sy >> sx;
        cin >> dy >> dx;
        // solve
        int ans = bfs(sy, sx);
        // output
        cout << ans << '\n';
    }


    return 0;
}
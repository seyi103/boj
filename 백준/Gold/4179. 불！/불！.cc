#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

struct Node {
    int y, x;
};

int N, M;
int visited[1100][1100];
int visited_j[1100][1100];
char MAP[1100][1100];
int sy, sx, fy, fx;
queue<Node> qf;

int bfs(int y, int x) {
    int de = 1;

    queue<Node> q;
    q.push({ y, x });

    visited_j[y][x] = 1;

    while (!q.empty())
    {
        if (!qf.empty()) {
            int cursize = qf.size();
            for (int c = 0; c < cursize; c++) {
                Node now = qf.front();
                qf.pop();

                for (int i = 0; i < 4; i++) {
                    int ny = now.y + ydir[i];
                    int nx = now.x + xdir[i];

                    if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                        continue;

                    // 이미 불이 있는 곳이면 
                    if (visited[ny][nx])
                        continue;
                    // 벽이면 통과 못함!
                    if (MAP[ny][nx] == '#')
                        continue;

                    visited[ny][nx] = visited[now.y][now.x] + 1;
                    qf.push({ ny, nx });
                }
            }
        }
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
                return visited_j[now.y][now.x];
            }
            if (visited_j[ny][nx])
                continue;
            if (MAP[ny][nx] == '#')
                continue;
            if(visited[ny][nx] <= visited_j[now.y][now.x] + 1)
            if (visited[ny][nx])
                continue;

            visited_j[ny][nx] = visited_j[now.y][now.x] + 1;
            q.push({ ny, nx });
        }
         /*cout << '\n';
         for (int i = 0; i < N; i++) {
             for (int j = 0; j < M; j++)
                 cout << visited[i][j] << ' ';
             cout << '\n';
         }
         cout << '\n';
         for (int i = 0; i < N; i++) {
             for (int j = 0; j < M; j++)
                 cout << visited_j[i][j] << ' ';
             cout << '\n';
         }*/
    }
    return -1;
}

int main() {
    fastIO;
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == 'J')
                sy = i, sx = j;
            else if (MAP[i][j] == 'F') {
                qf.push({ i, j });
                visited[i][j] = 1;
            }
        }
    int ans = bfs(sy, sx);
    if (ans == -1)
        cout << "IMPOSSIBLE";
    else cout << ans;
    return 0;
}
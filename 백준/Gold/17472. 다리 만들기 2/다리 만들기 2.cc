#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int y, x;
};

struct Edge {
    int a, b;
    int cost;

    bool operator < (Edge next) const {
        return cost < next.cost;
    }
};

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int N, M;
int MAP[15][15];
int visited[15][15];
int node;
vector<Edge> v;
int parent[7];

int Find(int now) {
    if (now == parent[now])
        return now;
    return parent[now] = Find(parent[now]);
}

void Union(int A, int B) {
    int pa = Find(A);
    int pb = Find(B);

    if (pa == pb)
        return;

    parent[pb] = pa;
}

int kruskal() {
    sort(v.begin(), v.end());
    int sum = 0;
    int cnt = 0;

    for (int i = 0; i < v.size(); i++) {
        Edge now = v[i];

        if (now.cost < 2)
            continue;

        if (Find(now.a) == Find(now.b))
            continue;

        //cout << now.a << ' ' << now.b << ' ' << now.cost << '\n';
        sum += now.cost;
        cnt++;
        Union(now.a, now.b);
    }
    if (cnt != node - 1)
        return -1;
    return sum;
}
// 섬에 번호를 붙이자
void bfs_num(int y, int x, int n) {
    queue<Node> q;
    q.push({ y, x });

    visited[y][x] = 1;
    MAP[y][x] = n;
    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                continue;
            if (visited[ny][nx])
                continue;
            if (MAP[ny][nx] == 0)
                continue;

            MAP[ny][nx] = n;
            visited[ny][nx] = 1;
            q.push({ ny, nx });
        }
    }
}
// 거리 구하기
void getDist(int y, int x, int n) {
    for (int i = 0; i < 4; i++) {
        int ny = y;
        int nx = x;
        int dist = 0;

        while (true)
        {
            ny += ydir[i];
            nx += xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M || MAP[ny][nx] == n)
                break;
            if (MAP[ny][nx]) {
                v.push_back({ n, MAP[ny][nx], dist });
                break;
            }
            dist++;
        }
    }

}

int main() {
    fastIO;
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> MAP[i][j];

    int num = 1;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            if (MAP[i][j] && !visited[i][j]) {
                // 이걸로 섬을 찾고 섬에 번호를 붙여준다
                bfs_num(i, j, num);
                num++;
            }
        }
    node = num - 1;
    for (int i = 1; i <= 6; i++)
        parent[i] = i;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            // 섬간 거리를 구해서 담아주자
            if (MAP[i][j])
                getDist(i, j, MAP[i][j]);
    // 이제 MST로 연결
    int ans = kruskal();
    cout << ans;
    return 0;
}

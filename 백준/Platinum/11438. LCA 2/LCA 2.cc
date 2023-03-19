#include <bits/stdc++.h>
#define FASTIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
using pii = pair<int, int>;

vector<int> g[101010];
int top[101010], parent[101010], sz[101010], dep[101010];
int n, m;

void dfs1(int x, int p=-1) {
    int mx=-1, midx=0;
    sz[x] = 1;
    for (int i=0; i<g[x].size(); ++i) {
        int nxt = g[x][i];
        if (nxt == p) continue;
        dep[nxt] = dep[x] + 1;
        parent[nxt] = x;
        dfs1(nxt, x);
        sz[x] += sz[nxt];
        if (mx < sz[nxt]) tie(mx, midx) = pii(sz[nxt], i);
    }
    if (!g[x].empty()) swap(g[x][midx], g[x][0]);
}

void dfs2(int x, int p=-1) {
    for (int i=0; i<g[x].size(); ++i) {
        int nxt = g[x][i];
        if (nxt == p) continue;
        top[nxt] = i ? nxt : top[x];
        dfs2(nxt, x);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = parent[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    return u;
}


int main() {
    FASTIO
    cin >> n;
    for (int i=0; i<n-1; ++i) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }

}   
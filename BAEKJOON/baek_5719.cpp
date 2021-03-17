#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
int n, m, x, y, z, s, e;
int a[502][502];
int dp[502];
void dijkstra() {
    memset(dp, -1, sizeof(dp));
    priority_queue<pair<int, int>> pq;
    pq.push({ 0,s });
    while (pq.size()) {
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();
        if (dp[here] != -1)continue;
        dp[here] = cost;
        for (int i = 0; i < n; i++) {
            if (a[here][i] == -1)continue;
            if (dp[i] != -1)continue;
            pq.push({ -cost - a[here][i],i });
        }
    }
}
void eraseEdge() {
    queue<int> qu;
    qu.push(e);
    while (qu.size()) {
        int cx = qu.front();
        qu.pop();
        for (int i = 0; i < n; i++) {
            if (dp[cx] == dp[i] + a[i][cx] && a[i][cx] != -1) {
                a[i][cx] = -1;
                qu.push(i);
            }
        }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    while (n != 0 && m != 0) {
        scanf("%d%d", &s, &e);
        memset(a, -1, sizeof(a));
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &x, &y, &z);
            a[x][y] = z;
        }
        dijkstra();
        eraseEdge();
        dijkstra();
        printf("%d\n", dp[e]);
        scanf("%d%d", &n, &m);
    }
    return 0;
}
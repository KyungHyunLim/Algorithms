#define MIN(A,B) A<B?A:B;

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string.h>
using namespace std;

bool issnake[101] = { false, };
int snake[101][1];
bool isladder[101] = { false, };
int ladder[101][1];
int answer = 1e9;
int dist[101];

void move() {
    queue<int> q;
    q.push(1);
    dist[1] = 0;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 6; i > 0; i--) {
            int next_cur = now + i;
            if (next_cur > 100) continue;
            if (isladder[next_cur]) {
                next_cur = ladder[next_cur][0];
            }
            else if (issnake[next_cur]) {
                next_cur = snake[next_cur][0];
            }
            if (dist[next_cur] == -1) {
                dist[next_cur] = dist[now] + 1;
                q.push(next_cur);
            }
        }
    }
}

int main() {

    int N, M;
    cin >> N >> M;

    memset(dist, -1, sizeof(dist));

    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        isladder[x] = true;
        ladder[x][0] = y;
    }

    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        issnake[x] = true;
        snake[x][0] = y;
    }

    move();
    cout << dist[100];

    return 0;
}
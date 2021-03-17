#define _CRT_SECURE_NO_WARNINGS
#define MIN(A,B) A<B?A:B;

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string.h>
using namespace std;

int visited[1001][1001][11] = { 0, };
bool map[1001][1001] = { false, };
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };
int N, M, K;

struct POINT {
    int x;
    int y;
    int c;
};


void move() {
    queue<POINT> q;
    q.push({ 1,1,0 });
    visited[1][1][0] = 1;

    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int c = q.front().c;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
            if (visited[nx][ny][c] == 0 && map[nx][ny] == 0) {
                q.push({ nx,ny,c });
                visited[nx][ny][c] = visited[x][y][c] + 1;
            }
            else if (map[nx][ny] == 1 && visited[nx][ny][c + 1] == 0 && c < K) {
                visited[nx][ny][c + 1] = visited[x][y][c] + 1;
                q.push({ nx,ny,c + 1 });
            }
        }
    }
}

int main() {

    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%1d", &map[i][j]);
        }
    }

    move();

    int answer = 1e9;
    int sum = 0;
    for (int i = 0; i < 11; i++) {
        if(visited[N][M][i] != 0) answer = MIN(answer, visited[N][M][i]);
        sum += visited[N][M][i];
    }
    if (sum == 0 && answer == 1e9) {
        cout << -1;
    }
    else {
        cout << answer;
    }
    return 0;
}
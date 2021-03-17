#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <queue>
#include <string.h>

using namespace std;

char map[100][100];
bool visited[100][100];
int N;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

void solution(int x, int y, char c, int mode) {
    queue<pair<int, int>> q;
    q.push(make_pair(x, y));

    while (!q.empty()) {
        int now_x = q.front().first;
        int now_y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int next_x = now_x + dx[i];
            int next_y = now_y + dy[i];
            if (next_x >= 0 && next_x < N && next_y >= 0 && next_y < N) {
                if (!visited[next_x][next_y]) {
                    //색맹이면
                    if (!mode) {
                        // 현재 색이 R 또는 G이고 B만 현재 검사중인걸로 변경
                        if ((c == 'R' || c == 'G') && map[next_x][next_y] != 'B') {
                            map[next_x][next_y] = c;
                        }
                        if (map[next_x][next_y] == c) {
                            visited[next_x][next_y] = true;
                            q.push(make_pair(next_x, next_y));
                        }
                    }
                    //색맹이 아니면
                    else {
                        if (map[next_x][next_y] == c) {
                            visited[next_x][next_y] = true;
                            q.push(make_pair(next_x, next_y));
                        }
                    }
                }
            }
        }
    }
}


int main() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }

    int answer = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j]) {
                answer++;
                solution(i, j, map[i][j], 1);
            }
        }
    }
    cout << answer << " ";

    memset(visited, false, sizeof(visited));
    answer = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j]) {
                answer++;
                solution(i, j, map[i][j], 0);
            }
        }
    }
    cout << answer << " ";

    return 0;
}
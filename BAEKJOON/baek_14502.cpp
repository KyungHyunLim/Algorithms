#define MAX(A,B) A>B?A:B;

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

int N, M;
int answer;
int v_conut;
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
int map[9][9];
int virus[11][2];

void copy(int(*a)[9], int(*b)[9]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            a[i][j] = b[i][j];
        }
    }
}

void go() {
    int copy_map[9][9];
    copy(copy_map, map);

    queue<pair<int,int>> q;
    for (int i = 0; i < v_conut; i++) {
        q.push(make_pair(virus[i][0], virus[i][1]));
    }

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (0 <= nx && nx < N && 0 <= ny && ny < M) {
                if (copy_map[nx][ny] == 0) {
                    copy_map[nx][ny] = 2;
                    q.push(make_pair(nx, ny));
                }
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (copy_map[i][j] == 0) cnt++;
        }
    }

    answer = MAX(cnt, answer);
}

void create_wall(int cnt) {
    if (cnt == 3) {
        go();
        return;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 0) {
                map[i][j] = 1;
                create_wall(cnt + 1);
                map[i][j] = 0;
            }
        }
    }
}

int main() {
   
    cin >> N >> M;

    int idx = 0;
    v_conut = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] == 2) {
                virus[idx][0] = i;
                virus[idx++][1] = j;
                v_conut++;
            }
        }
    }

    answer = 0;
    create_wall(0);
    cout << answer << endl;

    return 0;
}
#define MIN(A,B) A>B?B:A
#define MAX(A,B) A<B?B:A

#include<iostream>
#include<vector>
#include<string.h>
#include<queue>

using namespace std;

int N, K, L;
int map[101][101][2];
int d_change[10001];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };



int solve(int s_x, int s_y, int t_x, int t_y, int s_d) {
    int time = 0;
    while (true) {
        time++;

        //방향변경
        if (d_change[time]) {
            s_d = d_change[time] == 'L' ? (s_d + 3) % 4 : (s_d + 1) % 4;
        }

        int nx = s_x + dx[s_d];
        int ny = s_y + dy[s_d];

        //갈수 없는 곳
        if (nx < 1 || nx >= N-1 || ny < 1 || ny >= N-1) return time;
        //자기몸
        if (map[nx][ny][0] == 3) return time;
        //사과 있으면
        else if (map[nx][ny][0] == 2) {
            //머리 처리
            map[nx][ny][0] = 3;
            map[nx][ny][1] = s_d;
            s_x = nx;
            s_y = ny;
        }
        //사과가 없으면
        else {
            //머리 처리
            map[nx][ny][0] = 3;
            map[nx][ny][1] = s_d;
            s_x = nx;
            s_y = ny;

            //꼬리 처리
            map[t_x][t_y][0] = 0;
            t_x = t_x + dx[map[t_x][t_y][1]];
            t_y = t_y + dy[map[t_x][t_y][1]];
        }
    }
    return -1;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(i==0 || j==0 || i==N-1 || j==N-1)
                map[i][j][0] = 1;
        }
    }

    cin >> K;
    for (int i = 0; i < K; i++) {
        int x, y;
        cin >> x >> y;
        map[x][y][0] = 2;
    }

    cin >> L;
    for (int i = 0; i < L; i++) {
        int x;
        char y;
        cin >> x >> y;
        d_change[x] = y;
    }

    map[1][1][0] = 3;

    int answer = solve(1, 1, 1, 1, 1);

    cout << answer << endl;

    return 0;
}
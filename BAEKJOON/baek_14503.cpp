#define MIN(A,B) A>B?B:A
#define MAX(A,B) A<B?B:A

#include<iostream>
#include<vector>
#include<string.h>
#include<queue>

using namespace std;

int N, M;
int ro_x, ro_y, ro_d;
int map[51][51];
int check[51][51];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int solve(int s_x, int s_y, int s_d) {
    int ans = 0;
    while (true) {
        if (!check[s_x][s_y]) {
            ans++;
            check[s_x][s_y] = true;
        }

        bool back = false;
        for (int i = 0; i < 4; i++) {
            s_d = (s_d + 3) % 4;
            int n_x = s_x + dx[s_d];
            int n_y = s_y + dy[s_d];

            if (n_x < 0 || n_x >= N || n_y < 0 || n_y >= M) continue;
            if (map[n_x][n_y] || check[n_x][n_y]) continue;

            back = true;
            s_x = n_x;
            s_y = n_y;
            break;
        }

        if (!back) {
            s_x = s_x + dx[(s_d + 2) % 4];
            s_y = s_y + dy[(s_d + 2) % 4];

            if (s_x < 0 || s_x >= N || s_y < 0 || s_y >= M || map[s_x][s_y]) return ans;
        }
    }
    return -1;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    cin >> ro_x >> ro_y >> ro_d;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }

    int answer = solve(ro_x, ro_y, ro_d);
   
    cout << answer << endl;

    return 0;
}

/*
#include <iostream>

using namespace std;

#define MAX_SIZE 51

// 바라보는 방향(북, 동, 남, 서)
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

// 바라보는 방향에 따른 후진 (남, 서, 북, 동)
int back_dx[4] = { 1,0,-1,0 };
int back_dy[4] = { 0,-1,0,1 };

int ans; // 로봇청소기가 청소하는 칸의 개수
int map[MAX_SIZE][MAX_SIZE];
int n, m; // 영역의 크기
int r, c, d; // 로봇청소기의 좌표(r,c), 바라보는 방향(d) : 북(0), 동(1), 남(2), 서(3)


void Dfs(int x, int y, int direction)
{
    // 벽이면 끝
    if (map[x][y] == 1) return;

    // 빈 칸이면 청소한다.
    if (map[x][y] == 0)
    {
        map[x][y] = 2;
        ans++;
    }

    // 네 방향 검사
    for (int k = 0; k < 4; k++)
    {
        // 북(0) -> 서(3), 동(1) -> 북(0), 남(2) -> 동(1), 서(3) -> 남(2)
        int next_direction = direction-1 < 0 ? 3 : direction-1;
        int next_x = x + dx[next_direction], next_y = y + dy[next_direction];

        // 빈 칸이면 청소
        if (map[next_x][next_y] == 0)
        {
            Dfs(next_x, next_y, next_direction);
            // 다음 칸으로 넘어간 경우에 더 이상 나머지 방향을 검사하지 않는다.
            return;
        }
        // 청소했거나 벽이면 방향만 바꿔준다.
        else
        {
            direction = next_direction;
        }
    }
    // 검사 끝

    // 네 방향 모두 청소했거나 벽이면 방향을 유지한채로 후진한다.
    int next_x = x + back_dx[direction], next_y = y + back_dy[direction];

    Dfs(next_x, next_y, direction);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    cin >> r >> c >> d;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> map[i][j];

    Dfs(r, c, d);

    cout << ans << "\n";

    return 0;
}
*/
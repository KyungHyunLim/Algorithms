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

// �ٶ󺸴� ����(��, ��, ��, ��)
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

// �ٶ󺸴� ���⿡ ���� ���� (��, ��, ��, ��)
int back_dx[4] = { 1,0,-1,0 };
int back_dy[4] = { 0,-1,0,1 };

int ans; // �κ�û�ұⰡ û���ϴ� ĭ�� ����
int map[MAX_SIZE][MAX_SIZE];
int n, m; // ������ ũ��
int r, c, d; // �κ�û�ұ��� ��ǥ(r,c), �ٶ󺸴� ����(d) : ��(0), ��(1), ��(2), ��(3)


void Dfs(int x, int y, int direction)
{
    // ���̸� ��
    if (map[x][y] == 1) return;

    // �� ĭ�̸� û���Ѵ�.
    if (map[x][y] == 0)
    {
        map[x][y] = 2;
        ans++;
    }

    // �� ���� �˻�
    for (int k = 0; k < 4; k++)
    {
        // ��(0) -> ��(3), ��(1) -> ��(0), ��(2) -> ��(1), ��(3) -> ��(2)
        int next_direction = direction-1 < 0 ? 3 : direction-1;
        int next_x = x + dx[next_direction], next_y = y + dy[next_direction];

        // �� ĭ�̸� û��
        if (map[next_x][next_y] == 0)
        {
            Dfs(next_x, next_y, next_direction);
            // ���� ĭ���� �Ѿ ��쿡 �� �̻� ������ ������ �˻����� �ʴ´�.
            return;
        }
        // û���߰ų� ���̸� ���⸸ �ٲ��ش�.
        else
        {
            direction = next_direction;
        }
    }
    // �˻� ��

    // �� ���� ��� û���߰ų� ���̸� ������ ������ä�� �����Ѵ�.
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
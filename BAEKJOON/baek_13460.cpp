#define MIN(A,B) A>B?B:A
#define pi pair<int, int>

#include<iostream>
#include<vector>
#include<string.h>
#include<queue>

using namespace std;

int N, M;
int map[10][10];
int rsx, rsy, bsx, bsy, hx, hy;

int dx[4] = { 1, -1 ,0 ,0 };
int dy[4] = { 0, 0, 1, -1 };

void solve() {
    queue<pair<pair<pi, pi>, int>> q;
    pi red = make_pair(rsx, rsy);
    pi blue = make_pair(bsx, bsy);
    q.push(make_pair(make_pair(red, blue), 0));

    while (!q.empty()) {
        int red_x = q.front().first.first.first;
        int red_y = q.front().first.first.second;
        int blue_x = q.front().first.second.first;
        int blue_y = q.front().first.second.second;
        int count = q.front().second;

        if (map[red_x][red_y] == 3) {
            cout << count;
            return;
        }

        if (count >= 10) {
            cout << -1;
            return;
        }

        for (int i = 0; i < 4; i++) {
            int red_next_x = red_x + dx[i];
            int red_next_y = red_y + dy[i];
            int blue_next_x = blue_x + dx[i];
            int blue_next_y = blue_y + dy[i];

            //벽이면
            if (!map[red_next_x][red_next_y]) {
                red_next_x = red_x;
                red_next_y = red_y;
            }
            if (!map[blue_next_x][blue_next_y]) {
                blue_next_x = blue_x;
                blue_next_y = blue_y;
            }

            //구슬은 겹칠 수 없음(?) 한칸에 꽉차니까.
            if ((red_next_x == blue_next_x && red_next_x == blue_next_y)) continue;

            //파란 구슬이 구멍이면 X
            if (map[blue_next_x][blue_next_y] == 3) continue;

            pi new_red = make_pair(red_next_x, red_next_y);
            pi new_blue = make_pair(blue_next_x, blue_next_y);

            q.push(make_pair(make_pair(new_red, new_blue), count + 1));
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char temp;
            cin >> temp;
            if (temp == '#') map[i][j] = 0;
            else if (temp == '.') map[i][j] = 0;
            else if (temp == 'R') {
                map[i][j] = 2;
                rsx = i;
                rsy = j;
            }
            else if (temp == 'B') {
                map[i][j] = 2;
                bsx = i;
                bsy = j;
            }
            else {
                map[i][j] = 3;
                hx = i;
                hy = j;
            }
        }
    }

    solve();
    

    return 0;
}

#define MIN(A,B) A<B?A:B;

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string.h>
using namespace std;

bool visited[201][201] = {false,};
int map[201][201] = { -1, };
int dx[6] = {-2, -2, 0, 0, 2, 2};
int dy[6] = {-1, 1, -2, 2, -1, 1};
int N;

int move(int r1, int r2, int c1, int c2) {
    queue<pair<int,int>> q;
    q.push(make_pair(r1,c1));
    map[r1][c1] = 0;
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        visited[x][y] = true;
        
        for (int i = 5; i >= 0; i--) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N || visited[nx][ny]) continue;
            
            map[nx][ny] = map[x][y] + 1;
            visited[nx][ny] = true;
            q.push(make_pair(nx, ny));
            
            if (nx == r2 && ny == c2) 
                return map[nx][ny];
        }
    }
    return -1;
}

int main() {
 
    cin >> N;

    int r1, r2, c1, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    memset(map, -1, sizeof(map));

    int answer = move(r1, r2, c1, c2);
    cout << answer;

    return 0;
}
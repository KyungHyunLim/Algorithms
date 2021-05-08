/*
경주로 건설

각 칸마다 최소 비용 메모제이션 필요 dp + bfs

*/
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { -1,1,0,0 };
int answer;
int N;

// 설치정보 저장을 위한 구조체
struct info {
    int x, y;
    int d;
    int cost;
    info(int x, int y, int d, int cost) : x(x), y(y), d(d), cost(cost) {};
};

void bfs(vector<vector<int>>& board) {
    queue<info> q;
  // 초기 설치 (0,0) , 방향: -1(어떤방향일지 모르기때문), 비용: 0
    q.push(info(0, 0, -1, 0));
  // 시작위치는 벽으로 표시
    board[0][0] = 1;
    while (!q.empty()) {
      // 현재 설치 정보
        int cur_x = q.front().x;
        int cur_y = q.front().y;
        int cur_d = q.front().d;
        int cur_cost = q.front().cost;
        q.pop();
      // 목표 지점 도달시 최소값 갱신
        if (cur_x == N - 1 && cur_y == N - 1) {
            answer = min(answer, cur_cost);
            continue;
        }
      // 4방위 탐색
        for (int i = 0; i < 4; i++) {
            int nx = cur_x + dx[i];
            int ny = cur_y + dy[i];
            int n_cost = 0;
          // 맵을 벗어나면 안됨
            if (nx < 0 || nx >= N || ny < 0 || ny >= N || board[nx][ny] == 1) continue;
          // 처음 도로를 설치하거나 이전 방향과 같으면 직선 도로만 설치
            if (cur_d == -1 || i == cur_d) n_cost = cur_cost + 100;
          // 방향이 다르면 코너와 직선 도로 설치
            else n_cost = cur_cost + 600;
          // 처음 접근하거나 설치 비용이 이전 보다 작으면 갱신
            if (board[nx][ny] == 0 || board[nx][ny] >= n_cost) {
                board[nx][ny] = n_cost;
                q.push(info(nx, ny, i, n_cost));
            }
        }
    }
}

int solution(vector<vector<int>> board) {
    answer = 987654321;

    N = board.size();

    bfs(board);
    return answer;
}

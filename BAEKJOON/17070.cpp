/*
파이프 옮기기1

0. 
  - 이동할 상태 별 확인해야하는 빈칸위치 정의
  - 상태별 선택 가능 상태정보 정의
1. dfs를 이용한 완전 탐색(back-tracking)
  1.1 현재위치, 현재 상태에 대한 다음 위치, 다음 가능한 상태들 탐색 
  1.2 맵밖, 주요위치에 빈칸이 아니거나, 중복방문 일시 continue;
  1.3 N,N 도착시 ans++

*/
#include<iostream>
#include<vector>
#include<string>
using namespace std;

// 0: 가로, 1: 세로, 2: 대각선
// 이동할 상태 별 확인해야하는 빈칸위치
vector<int> dx[3] = {
	{0},	// 가로일때
	{0}, // 세로일때
	{0, -1}// 대각선 일때
};
vector<int> dy[3] = {
	{0}, // 가로일때
	{0}, // 세로일때
	{-1, 0}// 대각선 일때
};
// 상태별 선택 가능 상태
vector<int> choice[3] = {
	{0, 2},
	{1, 2},
	{0, 1, 2}
};

int ddx[3] = {0, 1, 1};
int ddy[3] = {1, 0, 1};

// 방정보
int map[17][17];
int visited[17][17];
// 방크기 NxN
int N;
// 경로 개수
int ans;

void dfs(int x, int y, int state){//, string s) {
	if (x == N && y == N) {
		// 디버깅용
		//cout << s << endl;
		ans++;
		return;
	}
	else {
		for (int i = 0; i < choice[state].size(); i++) {
			int new_state = choice[state][i];
			int nx = x + ddx[new_state];
			int ny = y + ddy[new_state];
			// 이동하는 곳이 맵밖이면 안됨
			if (nx <= 0 || nx > N || ny <= 0 || ny > N) continue;
			// 이동하는 곳이 재방문 이면 안됨
			if (visited[nx][ny]) continue;
			// 이동 하는 곳이 벽이면 안됨
			if (map[nx][ny]) continue;
			// 이동하려는 곳 새로운 상태에 따른 빈칸 검사
			int flag = true;
			for (int j = 0; j < dx[new_state].size(); j++) {
				int temp_x = nx + dx[new_state][j];
				int temp_y = ny + dy[new_state][j];
				// 맵밖으로 나갈 수 없음	
				if (nx <= 0 || nx > N || ny <= 0 || ny > N) {
					flag = false;
					break;
				}
				// 빈칸이어야 하는 곳에 벽이 있으면 안됨
				if (map[temp_x][temp_y] == 1) {
					flag = false;
					break;
				}
			}
			if (!flag) continue;

			visited[nx][ny] = true;
			dfs(nx, ny, new_state);//, s +"(" + to_string(nx) + "," + to_string(ny) + ") ");
			visited[nx][ny] = false;
		}
	}
}

int main() {
	cin >> N;

	// 맵정보입력
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	// 시작 위치 표시
	visited[1][1] = true;
	visited[1][2] = true;

	ans = 0;
	// 탐색 시작 위치 및 상태
	dfs(1, 2, 0);// , "(1,2), ");
	
	cout << ans << endl;

	return 0;
}

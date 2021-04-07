/*
미세먼지 안녕!

1. 확산
 1.1 공식에 따라 additive 배열에 저장한 값 더하고 빼기
2. 순환
 2.1 1칸 씩 이동
 2.2 각 맵끝(순환 모서리), 공기청정기 위치 주의
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

// R, C 맵크기
// 반복횟수(시간)
// dust: 미세먼지량
// additive: 추가 미세먼지량 및 확산 방향 수
// cleaner_x, cleaner_y: 공기청정기 아래쪽 좌표
int R, C, T;
int dust[51][51];
int additive[51][51][2];
int cleaner_x, cleaner_y;

// 방향 오 위 왼 아
// 시계방향 전환 => (dir + 1) % 4
// 반시계방향 전환 => (dir + 3) % 4
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

void spread() {
	// 확산량 계산
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (dust[i][j] != 0) {
				for (int k = 0; k < 4; k++) {
					int nx = i + dx[k];
					int ny = j + dy[k];
					if (nx < 0 || nx >= R || ny < 0 || ny >= C || dust[nx][ny] == -1) continue;
					additive[nx][ny][0] += dust[i][j] / 5;
					additive[i][j][1]++;
				}
			}
		}
	}
	// 미세먼지 업데이트
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			// 기존량 + 더해주어야할양 - 확산되어 없어진 량
			if (j == 0 && (i == cleaner_x || i == cleaner_x - 1)) continue;
			dust[i][j] = dust[i][j] + additive[i][j][0] - ((dust[i][j] / 5) * additive[i][j][1]);
		}
	}
}

void cleaning() {
	// 윗 순환
	// 공기청정기 위에서 시작
	int x = cleaner_x - 2;
	int y = cleaner_y;
	int dir = 1; // 위 방향 시작(역방향 계산)
	while (true) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		dust[x][y] = dust[nx][ny];

		// 다음이 공기청정기 위치면 0 대입 후 순환 종료
		if (dust[nx][ny] == -1) {
			dust[x][y] = 0;
			break;
		}

		// 방향 전환 지점 (각 순환 모서리)
		if ((nx == 0 && ny == 0) || (nx == 0 && ny == C - 1) || (nx == cleaner_x-1 && ny == C-1)) {
			dir = (dir + 3) % 4;
		}

		x = nx;
		y = ny;
	}

	x = cleaner_x + 1;
	y = cleaner_y;
	dir = 3;
	while (true) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		dust[x][y] = dust[nx][ny];

		// 다음이 공기청정기 위치면 0 대입 후 순환 종료
		if (dust[nx][ny] == -1) {
			dust[x][y] = 0;
			break;
		}

		// 방향 전환 지점 (각 순환 모서리)
		if ((nx == R-1 && ny == 0) || (nx == R-1 && ny == C - 1) || (nx == cleaner_x && ny == C - 1)) {
			dir = (dir + 1) % 4;
		}

		x = nx;
		y = ny;
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(); cout.tie(NULL);

	cin >> R >> C >> T;
	// 현재 미세먼지 정보 입력
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> dust[i][j];
			if (dust[i][j] == -1) {
				cleaner_x = i;
				cleaner_y = j;
			}
		}
	}

	// T초 만큼 반복
	for (int i = 0; i < T; i++) {
		// 추가 정보 초기화
		memset(additive, 0, sizeof(additive));
		// 미세먼지 확산
		spread();
		// 공기청정
		cleaning();
	}

	int ans = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (dust[i][j] > 0) {
				ans += dust[i][j];
			}
		}
	}
	
	cout << ans << endl;

	return 0;
}

/*
낚시왕

1. 상어 구조체 (s, d, z)
2. 플레이어 이동
3. 상어 이동
 3-1. 중복 이동 회피 (speed =% rot) => 시간초과 핵심
 3-2. 임시 현황 배열에 이동 후, 상어의 크기가 클때만 업데이티 => 큰 상어만 남음
4. 플레이어 이동 공간이 없을 때까지 반복
*/

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// R, C: 맵크기
// M: 상어 수
int R, C, M;

// 상어 정보
struct shark {
	int s; // 속력
	int d; // 방향
	int z; // 크기
	shark(int _s, int _d, int _z) : s(_s), d(_d), z(_z) {};
	shark() : s(0), d(0), z(0) {};
};

// 상어 현황
shark map[101][101];

// 이동
// 1: 위, 2: 아, 3: 오, 4: 왼
// 방향전환
// 1 -> 2, 2 -> 1 / d % 2 == 0 => 1, d % 2 == 1 => 2
// 3 -> 4, 4 -> 3 / 동일
int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> R >> C >> M;

	// 상어 정보 입력
	for (int i = 0; i < M; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		map[r][c] = shark(s, d, z);
	}

	// 플레이어 이동할 수 있는 만큼 반복
	// 오른쪽으로 1칸씩 이동 ((0,1) -> (0,2) -> ... -> (0,C))
	int ans = 0;
	for (int i = 1; i <= C; i++) {
		// 가장 가까운 상어 get
		for (int j = 1; j <= R; j++) {
			// 상어가 존재하면
			if (map[j][i].z != 0) {
				// 상어 크기를 ans에 더해주고
				ans += map[j][i].z;
				// 상어 제거 후
				map[j][i].z = 0;
				// 탈출
				break;
			}
		}

		// 상어 이동
		shark temp_map[101][101];
		for (int k = 1; k <= C; k++) {
			for (int j = 1; j <= R; j++) {
				// 상어가 존재하면
				if (map[j][k].z != 0) {
					int x = j;
					int y = k;
					int dir = map[j][k].d;
					int speed = map[j][k].s;
					int size = map[j][k].z;

					//printf("시작 상어 : %d %d 방향: %d 속력: %d  크기: %d\n", x, y, dir, speed, size);
					// 이동
					if (dir == 1 || dir == 2) { // 위, 아래 방향
						int rot = (R - 1) * 2;
            // 중복 이동 회피
						if (speed >= rot) speed = speed % rot;
            
            // 실제 이동
						for (int z = 0; z < speed; z++) {
							int nx = x + dx[dir];
							int ny = y + dy[dir];
              // 맵밖 벗어나면 방향전환
							if (nx < 1) {
								dir = 2;
								nx = nx + 2;
							}
							if (nx > R) {
								dir = 1;
								nx = nx - 2;
							}
							x = nx;
							y = ny;
						}
					}
					else { // 왼, 오 방향
						int rot = (C - 1) * 2;
            // 중복 이동 회피
						if (speed >= rot) speed = speed % rot;
            
            // 실제 이동
						for (int z = 0; z < speed; z++) {
							int nx = x + dx[dir];
							int ny = y + dy[dir];
              // 맵밖 벗어나면 방향전환
							if (ny < 1) {
								dir = 3;
								ny = ny + 2;
							}
							if (ny > C) {
								dir = 4;
								ny = ny - 2;
							}
							x = nx;
							y = ny;
						}
					}

					// 이동한 상어가 더큰 경우 이동 정보 반영
					if (size > temp_map[x][y].z) {
						temp_map[x][y].z = size;
						temp_map[x][y].s = map[j][k].s;
						temp_map[x][y].d = dir;
					}
				}
			}
		}

		// 이동 정보 업데이트
		swap(map, temp_map);
	}

	cout << ans << endl;

	return 0;
}
/* 
주어진 만큼 다 이동하면 시간 초과.
// 이동
					while (speed > 0) {
						x = x + dx[dir];
						y = y + dy[dir];

						// 맵 벗어나면 방향 전환
						if (x <= 0 || x > R || y <= 0 || y > C) {
							//printf("방향 전환: %d -> ", dir);
							x = x - dx[dir];
							y = y - dy[dir];
							if (dir == 1) dir = 2;
							else if (dir == 2) dir = 1;
							else if (dir == 3) dir = 4;
							else if (dir == 4) dir = 3;
							//printf("%d\n", dir);
						}
						else {
							speed--;
							//printf("이동 : %d %d\n", x, y);
						}
					}

					// 이동한 상어가 더큰 경우 이동 정보 반영
					if (size > temp_map[x][y].z) {
						temp_map[x][y].z = size;
						temp_map[x][y].s = map[j][k].s;
						temp_map[x][y].d = dir;
					}
					//printf("\n");
				}
*/

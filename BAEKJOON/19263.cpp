/*
청소년 상어

* 조건 구현이 까다로운 문제

0. 
물고기 -> 번호, 방향, 위치
상어 -> 방향, 위치
맵 -> 물고기 번호 or 상어표시

0. 최대값 
1. 맵상태 저장 -> Origin -> A
2. 물고기 이동 -> 맵상태 A
3. 상어 밥 선택
  3-1. A -> B
  3-2. 재귀 호출
  3-3. B -> A
4. 맵상태 복구 -> A -> Origin

*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
using namespace std;

// 물고기 정보 - [번호][방향, x, y]
int fish[17][3];
// 상어 정보 - [방향, x, y]
int shark[3];
// 맵 정보 - [물고기 번호]
int map[4][4];
// 최대합
int ans;

// 0: 위 1: 왼위 2: 왼 3: 왼아 4: 아 5: 오아 6: 오 7: 오위
// 반시계 45도 회전 => (dir + 1) % 8;
int dx[8] = {-1, -1, 0, +1, +1, +1, 0, -1};
int dy[8] = {0, -1, -1, -1, 0, +1, +1, +1};

// 맵 및 물고기 상태 백업용 함수
void copy(int a[][4], int b[][4], int c[][3], int d[][3]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			a[i][j] = b[i][j];
		}
	}

	for (int i = 1; i <= 16; i++) {
		c[i][0] = d[i][0];
		c[i][1] = d[i][1];
		c[i][2] = d[i][2];
	}
}

// 디버깅용
/*
void Print() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if(map[i][j] != -1)
				cout << map[i][j] << "(" << fish[map[i][j]][0] << ")\t";
			else
				cout << map[i][j] << "(" << shark[0] << ")\t";
		}
		cout << endl;
	}
	cout << endl;
}
*/

// 상어 이동방향으로 먹을 물고기 있는지 확인
bool istherefish() {
	int d = shark[0];
	int x = shark[1];
	int y = shark[2];
	while (true) {
		x = x + dx[d];
		y = y + dy[d];
		if (x < 0 || x >= 4 || y < 0 || y >= 4) break;
		if (map[x][y] != 0) return true;
	}
	return false;
}

// 상어가 섭취 가능한 물고기 리스트 생성
vector<int> Listing() {
	vector<int> temp;
	int d = shark[0];
	int x = shark[1];
	int y = shark[2];
	while (true) {
		x = x + dx[d];
		y = y + dy[d];
		if (x < 0 || x >= 4 || y < 0 || y >= 4) break;
		if (map[x][y] != 0) {
			temp.push_back(map[x][y]);
		}
	}
	return temp;
}

// 물고기 이동 및 상어의 물고기 선택방법 완전탐색
void solve(int sum) {
	int c_map[4][4];
	int c_fish[17][3];
	ans = ans < sum ? sum : ans;
	copy(c_map, map, c_fish, fish);
	// 물고기 이동
	for (int i = 1; i <= 16; i++) {
		// 없어진 물고기 or 상어 넘기기
		if (fish[i][1] == -1) continue;
		int d = fish[i][0];
		int x = fish[i][1];
		int y = fish[i][2];
		int nx, ny, nd;
		// 갈수 있는 곳 탐색
		for (int j = 0; j < 8; j++) {
			// 45도 반시계 방햐으로 회전
			nd = (d + j) % 8;
			nx = x + dx[nd];
			ny = y + dy[nd];
			// 물고기 밖으로 못나감
			if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
			// 상어 있는 곳은 못감
			if (map[nx][ny] == -1) continue;
			// 다른 물고기가 있는 경우
			if (map[nx][ny] != 0) {
				// 찾으면 좌표 넣어 주고 빠져 나오기
					// map[x][y] <-> map[nx][ny] 물고기 번호 swap
				int temp = map[nx][ny];
				// 맵에서 번호 swap
				map[x][y] = map[nx][ny];
				map[nx][ny] = i;
				// 물고기 배열에서 각 좌표 swap
				fish[i][1] = nx;
				fish[i][2] = ny;
				fish[temp][1] = x;
				fish[temp][2] = y;
				// 이동한 물고기는 새로운 방향 설정 해주기
				fish[i][0] = nd;
			}
			// 빈칸인 경우
			else {
				map[x][y] = 0;
				map[nx][ny] = i;
				fish[i][0] = nd;
				fish[i][1] = nx;
				fish[i][2] = ny;
			}
			break;
		}
		// 아무데도 갈 곳이 없으면 가만히 있기
	}

	//cout << "물고기 이동: " << endl;
	//Print();

	// 상어의 선택
	vector<int> fish_list = Listing();
	// for(선택가능경우)
	for (int i = 0; i < fish_list.size(); i++) {
		int shark_d = shark[0];
		int shark_x = shark[1];
		int shark_y = shark[2];
		// 맵의 해당 위치에 상어표시
		map[fish[fish_list[i]][1]][fish[fish_list[i]][2]] = -1;
		// 맵의 상어 위치는 빈칸 표시;
		map[shark_x][shark_y] = 0;
		// 상어 업데이트
		shark[0] = fish[fish_list[i]][0];
		shark[1] = fish[fish_list[i]][1];
		shark[2] = fish[fish_list[i]][2];
		// 물고기 없어짐 표시
		fish[fish_list[i]][1] = -1;

		//cout << "상어의 선택 후: " << fish_list[i] << endl;
		//Print();

		solve(sum + fish_list[i]);

		// 물고기 정보 되돌리기
		fish[fish_list[i]][1] = shark[1];
		// 상어 정보 되돌리기
		shark[0] = shark_d;
		shark[1] = shark_x;
		shark[2] = shark_y;
		// 물고기 되돌리기
		map[fish[fish_list[i]][1]][fish[fish_list[i]][2]] = fish_list[i];
		// 맵에서 상어 되돌리기
		map[shark_x][shark_y] = -1;
	}

	copy(map, c_map, fish, c_fish);
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	// 물고기 정보 입력
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int a, b;
			cin >> a >> b;
			fish[a][0] = b-1;
			fish[a][1] = i;
			fish[a][2] = j;
			map[i][j] = a;
		}
	}
	
	ans = map[0][0];
	// 초기 상어
	shark[0] = fish[map[0][0]][0];
	fish[map[0][0]][1] = -1;
	shark[1] = 0;
	shark[2] = 0;
	map[0][0] = -1;

	// 물고기 이동 및 상어의 물고기 선택방법 완전탐색
	solve(ans);

	cout << ans << endl;

	return 0;
}


/*
모노미노도미노2

1. 두가지 테트리스 동시
  - green_map
  - blue_map
2. 놓을 위치찾기
3. 블럭 놓기
4. 행/열 완성 검사
  4-1. 완성시 블럭 없애기
  4-2. 빈곳 채우기
*/
#include<iostream>
#include<vector>
#include <algorithm> 
using namespace std;

// 각 게임 맵
bool blue_map[4][11];
bool green_map[11][4];
// 블록 놓는 횟수 및 종류(종류, (위치))
int N;
vector<pair<int,pair<int,int>>> block;

int score;

// 블럭 놓기 ( 맵 종류, 블럭 종류, (위치))
void place(int color, int t, int x, int y) {
	if (color == 0) { // green_map
		if (t == 2) { // (x, y), (x, y + 1)
			green_map[x - 1][y] = true;
			green_map[x - 1][y + 1] = true;
		}
		else if (t == 3) { // (x, y), (x + 1, y)
			green_map[x - 2][y] = true;
			green_map[x - 1][y] = true;
		}
		else {
			green_map[x - 1][y] = true;
		}
	}
	else { // blue_map
		if (t == 2) { // (x, y), (x, y + 1)
			blue_map[x][y - 2] = true;
			blue_map[x][y - 1] = true;
		}
		else if (t == 3) { // (x, y), (x + 1, y)
			blue_map[x][y - 1] = true;
			blue_map[x + 1][y - 1] = true;
		}
		else {
			blue_map[x][y - 1] = true;
		}
	}
}

// 열검사
bool check_row(int color, int y) {
	bool flag = true;
	if (color == 0){ // green_map
		for (int i = 4; i < 10; i++) {
			if (green_map[i][y]) {
				flag = false;
				break;
			}
		}
	}
	else {	// blue_map
		for (int i = 0; i < 4; i++) {
			if (blue_map[i][y]) {
				flag = false;
				break;
			}
		}
	}
	if (flag) score++;
	return flag;
}

// 행검사
bool check_colum(int color, int x) {
	bool flag = true;
	if (color == 0) { // green_map
		for (int i = 0; i < 4; i++) {
			if (green_map[x-1][i]) {
				flag = false;
				break;
			}
		}
	}
	else {	// blue_map
		for (int i = 4; i < 10; i++) {
			if (blue_map[x-1][i]) {
				flag = false;
				break;
			}
		}
	}
	if (flag) score++;
	return flag;
}

int main() {
	cin >> N;
	score = 0;
	// 놓을 블럭 정보 입력
	for (int i = 0; i < N; i++) {
		int t, x, y;
		cin >> t >> x >> y;
		block.push_back(make_pair(t, make_pair(x, y)));
	}

	// N 개 블럭놓기
	for (int i = 0; i < N; i++) {
		// 놓을 블럭 정보
		int t = block[i].first;
		int x = block[i].second.first;
		int y = block[i].second.second;

		// 초록맵 블럭이동
			// 놓을 위치 찾기
		int j;
		for (j = 4; j < 10; j++) {
			if (t == 2) { // (x, y), (x, y + 1)
				if (green_map[j][y] || green_map[j][y + 1]) break;
			}
			else if (t == 3) {  // (x, y), (x + 1, y)
				if (green_map[j + 1][y]) break;
			}
			else { // (x, y)
				if (green_map[j][y]) break;
			}
		}
			// 블럭 놓기 ( 맵 종류, 블럭 종류, (위치))
		place(0, t, j, y);
			// 한 행/열 완료 검사 (맵 종류, 검사할 위치-블럭 놓은 위치)
		vector<int> c;
		if (t == 0) {
			if (check_colum(0, j)) c.push_back(j);
		}
		else if(t==1) {
			if (check_colum(0, j)) c.push_back(j);
		}
		else {
			if (check_colum(0, j - 1)) c.push_back(j - 1);
			if (check_colum(0, j)) c.push_back(j);
		}
			// 블럭 없애기
		for (int z = 0; z < c.size(); z++) {
			for (int k = 0; k < 4; k++) green_map[c[z]][k] = false;
		}
			// 빈공간 채우기
		for (int k = 0; k < 4; k++) {
			for (int z = 0; z < *max_element(c.begin(), c.end()); z++) {
				green_map[k][z + c.size()] = green_map[k][z];
			}
		}

		// 파란맵 블럭이동
			// 놓을 위치 찾기
		for (j = 0; j < 10; j++) {
			if (t == 2) { // (x, y), (x, y + 1)
				if (blue_map[x][j + 1]) break;
			}
			else if (t == 3) {  // (x, y), (x + 1, y)
				if (blue_map[x][j] || blue_map[x + 1][j]) break;
			}
			else { // (x, y)
				if (blue_map[x][j]) break;
			}
		}
			// 블럭 놓기(맵 종류, 블럭 종류, (위치))
		place(1, t, x, j);

		vector<int> r;
		// 한 행/열 완료 검사
		if (t == 1) {
			if (check_row(1, j)) r.push_back(j - 1);
		}
		else if (t == 2) {  // (x, y), (x, y + 1)
			if (check_row(1, j)) r.push_back(j - 1);
			if (check_row(1, j - 1)) r.push_back(j - 2);
		}
		else {  // (x, y), (x + 1, y)
			if (check_row(1, j)) c.push_back(j - 1);
		}

		// 블럭 없애기
		for (int j = 0; j < r.size(); j++) {
			for (int k = 0; k < 4; k++) blue_map[k][r[j]] = false;
		}
		// 빈공간 채우기
		for (int k = 0; k < 4; k++) {
			for (int z = 0; z < *max_element(r.begin(), r.end()); z++) {
				green_map[z + r.size()][k] = green_map[z][k];
			}
		}
	}

	cout << score << endl;

	return 0;
}

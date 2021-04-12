/*
주사위 윷놀이

- 이동정보 Look up table 구성
- dfs를 이용해 이동 가지수 완전 탐색 (2^20 == 약 100만)
*/

#include<iostream>
#include<vector>
#include<tuple>
using namespace std;

// move : 가능한 이동 경로 하드 코딩 (0 점수, 1~5 이동)
int _move[33][6] = { 
	{0,1,2,3,4,5}, //0번자리 
	{2,2,3,4,5,9}, //1번자리 
	{4,3,4,5,9,10}, //2번자리 
	{6,4,5,9,10,11}, //3번자리 
	{8,5,9,10,11,12},//4번자리 
	{10,6,7,8,20,29},//5번자리 
	{13,7,8,20,29,30}, //6번자리 
	{16,8,20,29,30,31}, //7번자리 
	{19,20,29,30,31,32}, //8번자리 
	{12,10,11,12,13,14}, //9번자리 
	{14,11,12,13,14,15}, //10번자리 
	{16,12,13,14,15,16}, //11번자리 
	{18,13,14,15,16,17}, //12번자리 
	{20,18,19,20,29,30}, //13번자리 
	{22,15,16,17,24,25}, //14번자리 
	{24,16,17,24,25,26}, //15번자리 
	{26,17,24,25,26,27}, //16번자리 
	{28,24,25,26,27,28}, //17번자리 
	{22,19,20,29,30,31}, //18번자리 
	{24,20,29,30,31,32}, //19번자리 
	{25,29,30,31,32,32}, //20번자리 
	{26,20,29,30,31,32}, //21번자리 
	{27,21,20,29,30,31}, //22번자리 
	{28,22,21,20,29,30}, //23번자리 
	{30,23,22,21,20,29}, //24번자리 
	{32,26,27,28,31,32}, //25번자리 
	{34,27,28,31,32,32}, //26번자리 
	{36,28,31,32,32,32}, //27번자리 
	{38,31,32,32,32,32}, //28번자리 
	{30,30,31,32,32,32}, //29번자리 
	{35,31,32,32,32,32}, //30번자리 
	{40,32,32,32,32,32}, //31번자리 
	{0,32,32,32,32,32} //32번자리 
};

// pieces 말 정보, 위치, 도착 유무
vector<tuple<int, bool>> pieces;

int isthere[35];

// 주사위 10개
int dice[10];
// 최대점수
int ans;

void solve(int idx, int sum) {
	if (idx == 10) {
		ans = sum > ans ? sum : ans;
		return;
	}
	else {
		for (int i = 0; i < 4; i++) {
			int x = get<0>(pieces[i]);
			int nx = _move[x][dice[idx]];
			if (isthere[nx] > 0 && nx && nx != 32) {
				continue;
			}
			else {
				// 이동 정보 업데이트
				get<0>(pieces[i]) = nx;
				isthere[x] --;
				isthere[nx]++;
				// 다음 선택
				solve(idx + 1, sum + _move[nx][0]);
				// 이동 정보 복구
				get<0>(pieces[i]) = x;
				isthere[x] ++;
				isthere[nx]--;
			}
		}
	}
}

int main() {
	// 주사위 정보 입력
	for (int i = 0; i < 10; i++) {
		cin >> dice[i];
	}

	// 초기 말 정보 입력
	for (int i = 0; i < 4; i++) {
		pieces.push_back(make_tuple(0,true));
	}

	isthere[0] = 4;
	ans = 0;
	solve(0, 0);

	cout << ans << endl;

	return 0;
}

/*
색종이 붙이기

- dfs를 이용한 완전탐색
- 한번에 많이 제거할 수록 좋기 때문에 (수량한정) 큰 색종이 부터 놔보기

1. 색종이 둘수 있는 곳 탐색
2. 둘수 있으면 큰것 

*/

#include<iostream>

using namespace std;


int whole_paper[10][10];
int used[6] = { 0, 5, 5, 5, 5, 5 };
int paper_cnt;
int ans;

bool Isok(int x, int y, int size) {
	// 색종이가 맵밖을 벗어나거나 다 썻으면 둘 수 없음
	if (x + size > 10 || y + size > 10 || used[size] == 0) return false;
	
	for (int i = x; i < x + size; i++) {
		for (int j = y; j < y + size; j++) {
			// 범위 중 하나라도 0이 있으면 해당 크기 색종이를 둘수 없음
			if (whole_paper[i][j] == 0) return false;
		}
	}
	// 위 조건 모두 통과시 둘 수 있음
	return true;
}

void Loc_paper(int x, int y, int size) {
	// 사용한 크기의 색종이 수 하나 감소
	used[size]--;
	// 색종이 놓기
	for (int i = x; i < x + size; i++) {
		for (int j = y; j < y + size; j++) {
			whole_paper[i][j] = 0;
		}
	}
	// 없어진 1 많큼 감소
	paper_cnt -= (size * size);
}

void Remove_paper(int x, int y, int size) {
	// 제거한 크기의 색종이 수 하나 감소
	used[size]++;
	// 색종이 제거
	for (int i = x; i < x + size; i++) {
		for (int j = y; j < y + size; j++) {
			whole_paper[i][j] = 1;
		}
	}
	// 생긴 1 많큼 감소
	paper_cnt += (size * size);
}

// 디버깅용
void Print() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << whole_paper[i][j] << "\t";
		}
		cout << endl;
	}
}

void dfs(int cnt) {
	// 모든 곳이 색종이로 덮혔으면
	if (paper_cnt == 0) {
		//cout << "종료" << endl;
		// 최솟값 업데이트
		ans = ans > cnt ? cnt : ans;
		return;
	}
	else {
		// 모든 칸에 대해 검사
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				// 색종이 못두는 곳이면 넘기기
				if (whole_paper[i][j] == 0) continue;
				// 5개 사이즈 큰것 부터 놔보기
				for (int k = 5; k > 0; k--) {
					// k 크기 색종이 놓을 수 있으면
					if (Isok(i, j, k)) {
						// 색종이 놓기
						Loc_paper(i, j, k);

						//cout << endl;
						//Print();
						//cout << endl;

						// 다음 부분 찾아서 진행
						dfs(cnt + 1);

						// 색종이 제거
						Remove_paper(i, j, k);
					}
				}
				return;
			}
		}
	}
}

int main() {
	paper_cnt = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> whole_paper[i][j];
			if (whole_paper[i][j] == 1) paper_cnt++;
		}
	}

	ans = 987654321;

	dfs(0);

	if(ans == 987654321) cout << -1 << endl;
	else cout << ans << endl;
	
	return 0;
}

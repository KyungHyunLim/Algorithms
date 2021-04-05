/*
사다리 조작

완전탐색 - DFS

1. 가로선 선택 DFS()
 1-1. 가로선 연속 선택 불가 조건 주의
2. 사다리판 상태 확인

*/
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

#define MIN(A,B) A<B?A:B
int N, M, H; //N: 세로선 개수 / M: 가로선 개수 / H: 세로선마다 가로선을 놓을 수 있는 위치 개수
bool checked[11][31]; //11: 세로선 (x와 x+1이) 31: 가로선 (에 의해 연결되어있다.)
int answer;

bool isok() {
	for (int i = 0; i <= N; i++) {
		// 현재(출발 사다리 번호)
		int cur = i;
		for (int j = 1; j <= H; j++) {
			// 다음 사다리와 연결된경우 
			if (checked[cur][j]) cur += 1;
			// 이전 사다리와 연결된 경우
			else if(checked[cur-1][j]) cur -= 1;
		}

		// 출발 사다리와 도착사다리가 다르면
		if (cur != i) return false;
	}

	// 출발 사다리와 도착사다리가 모두 같음
	return true;
}

void Select(int line, int cnt) {
	//3개 이상이면 답이 -1 로 출력
	if (cnt >= 4) return;
	//원하는 조건이 완성되었으면 answer 업데이트
	if (isok()) {
		answer = MIN(answer, cnt);
		return;
	}

	for (int i = line; i <= H; i++) {
		for (int j = 1; j < N; j++) {
			// 이미 선택한 라인
			if (checked[j][i]) continue;
			// 이전 라인이 연결되있으면 선택불가
			if (checked[j-1][i]) continue;
			// 이후 라인이 연결되있으면 선택불가
			if (checked[j+1][i]) continue;

			checked[j][i] = true;
			Select(i, cnt + 1);
			checked[j][i] = false;
		}
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	// 사다리 정보 초기화
	memset(checked, false, sizeof(checked));
	cin >> N >> M >> H;

	if (M == 0) {
		cout << 0 << endl;
		return 0;
	}

	// 주어진 사다리 정보 입력
	for (int i = 0; i < M; i++) {
		int k, s;
		cin >> k >> s;
		checked[s][k] = true;
	}

	answer = 987654321;
	
	//각 선택 조합 테스트
	Select(1,0);
	if (answer == 987654321) {
		cout << -1 << endl;
		return 0;
	}
	else {
		cout << answer << endl;
	}

	return 0;
}

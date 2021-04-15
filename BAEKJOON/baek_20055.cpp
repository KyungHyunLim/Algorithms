/*
컨베이어 벨트 위의 로봇

1. 벨트 회전
  1-1. idx = (idx + 1) % (2 * N) 사용 회전
  1-2. 회전후, 로봇이 있고, 내리는 위치일 경우 처리
2. 로봇 이동
  2-0. 로봇의 이동은 위 컨베이어 벨트에서만 일어남 (0 ~ N-1) 
       / 들어온 순서대로 움직어야 함으로 뒤에서 부터(N-1) 검사
  2-1. 이전 칸에 로봇이 있으면
    2-1.1 현재칸에 내구도가 충분하고 로봇이 없으면 이동
  2-2. 이동 불가시 넘어감
3. 로봇 올리기
  3-1. Map[0] 위치에 로봇이 없고 내구도가 0이 아니면 로봇 올리기
    * 로봇이 있을 수는 없음.
4. 1-3 반복, 내구도 0인 벨트가 K개가 될 때까지

*/
#include<iostream>
#include<vector>

using namespace std;

// N: 컨베이어 벨트 길이(한짝)
// K: 종료조건 (내구도 0인 벨트 개수)
int N, K;

struct Belt {
	int idx; // 벨트의 현 위치
	int durability; // 내구도
	bool isRobot; // 로봇이 있는지 없는지
};
Belt belts[200];

// belts의 인덱스
// e.g. map[100] = 3; 100번째에 belts[3]번 벨트가 존재
int map[200];
// 내구도 0 인 벨트 개수
int amount;

void Print() {
	for (int i = 0; i < N; i++) {
		cout <<	map[i] << " " <<
			belts[map[i]].durability << " " <<
			belts[map[i]].isRobot << "\t";
	}
	cout << endl;
	for (int i = 2 * N -1 ; i >= N ; i--) {
		cout <<
			map[i] << " " <<
			belts[map[i]].durability << " " <<
			belts[map[i]].isRobot << "\t";
	}
	cout << endl;
}

// 벨트 회전
void rotation() {
	for (int i = 0; i < 2 * N; i++) {
		// 한칸 회전
		belts[i].idx = (belts[i].idx + 1) % (2 * N);
		// 전체 맵에 벨트 위치 표시
		map[belts[i].idx] = i;
		// 위에 로봇이 있으면
		if (belts[i].isRobot) { 
			// 이동한 곳이 내려가는 위치면 로봇 비활성화
			if (map[N - 1] == i) {
				belts[i].isRobot = false;
			}
		}
	}
}

// 로봇 이동
void move_robot() {
	bool flag = false;
	for (int i = N-1; i > 0; i--) {
		// 이전 벨트 위에 로봇이 있고
		if (belts[map[i - 1]].isRobot) {
			// 현재 벨트 위에 로봇이 없으면서 내구도가 0이 아니면
			if (!belts[map[i]].isRobot && belts[map[i]].durability > 0) {
				// 로봇 이동
				flag = true;
				belts[map[i - 1]].isRobot = false;
				belts[map[i]].durability--;
				// 이동 하려는 곳이 내리는 곳이면
				if (i == N - 1) {
					// 로봇 하차
					belts[map[i]].isRobot = false;
				}
				else { // 아니면
					// 로봇 표시
					belts[map[i]].isRobot = true;
				}
				
				if (belts[map[i]].durability == 0) amount++;
			}
		}
		//if (flag) {
		//	i++;
		//	flag = false;
		//}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;

	// 초기 벨트 상태 입력
	for (int i = 0; i < 2 * N; i++) {
		cin >> belts[i].durability;
		belts[i].idx = i;
		belts[i].isRobot = false;
		map[i] = i;
	}

	// 단계
	int ans = 0;
	// 내구도 0인 벨트 개수
	amount = 0;
	// 내구도 0인 벨트 개수가 K개 되기 전까지
	while (amount < K) {
		//cout << endl;
		//cout << "<0.> 벨트 회전 이전" << endl;
		//Print();
		// 1. 벨트 회전
		rotation();
		//cout << endl;
		//cout << "<1.> 벨트 회전 후" << endl;
		//Print();
		// 2. 로봇 이동
		move_robot();
		//cout << endl;
		//cout << "<2.> 로봇 이동 후" << endl;
		//Print();
		// 3. 로봇 올리기
			// 먼저 올라간 로봇부터 움직임으로 뒤에 추가되는 구조 사용
			// 로봇 배열에 추가
		if (belts[map[0]].durability != 0) {
			belts[map[0]].isRobot = true;
			// 올라가는 위치에 있던 벨트 내구도 감소
			belts[map[0]].durability--;
			// 0이 됬으면 개수 증가
			if (belts[map[0]].durability == 0) amount++;
		}
		//cout << endl;
		//cout << "<3.> 로봇 올린 후" << endl;
		//Print();
		//cout << endl;
		//cout << "0인 벨트 개수: " << amount << endl;
		ans++;
		//cout << "단계: " << ans << endl;
		//cout << endl;
	}

	cout << ans << endl;

	return 0;
}

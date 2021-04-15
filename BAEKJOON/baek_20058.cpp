/*
마법사 상어와 파이어스톰

- 남아있는 얼음 A[r][c]의 합
- 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수

1. 격자 나누기 - 분할정복
2. 회전 - 하드 코딩
3. 얼음 크기 변경 - candidate 뽑은후 
4. 1-3 Q회 반복
5. 덩어리 크기 비교 - bfs()
*/
#include<iostream>
#include<vector>
#include<cmath>
#include<queue>

using namespace std;
/*
3 1
1 2 3 4 5 6 7 8
9 10 11 12 13 14 15 16
17 18 19 20 21 22 23 24
25 26 27 28 29 30 31 32
33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48
49 50 51 52 53 54 55 56
57 58 59 60 61 62 63 64
3
*/

// N: 맵크기
// Q: 파이어 스톰 횟수
int N, Q;
// 맵
int map[64][64];
bool visited[64][64];
// 파이어 스톰 단계
vector<int> L;

// 방향
// 덩어리 탐색, 얼음 크기 조정용
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

// 얼음 회전
void Rotation(int l, int x, int y) {
	int cnt = l / 2;
	for (int z = 0; z < cnt; z++) {
		int base_x = x + z;
		int base_y = y + z;
		int end_x = x + l - z - 1;
		int end_y = y + l - z - 1;
		int len = end_x - base_x;

		int temp[64];
		// 1. 임시배열에 복사
		for (int i = 0; i < len; i++) temp[i] = map[base_x][base_y + i];
		// 2. 회전 4 -> 1
		for (int i = 0; i < len; i++)  map[base_x][base_y + i] = map[end_x - i][base_y];
		for (int i = 0; i < len; i++)  map[end_x - i][base_y] = map[end_x][end_y - i];
		for (int i = 0; i < len; i++)  map[end_x][end_y - i] = map[base_x + i][end_y];
		for (int i = 0; i < len; i++)  map[base_x + i][end_y] = temp[i];
	}
}

// 격자 나누기 (현재 길이 2^N, 타겟 길이 2^l), x, y
void Divide(int sub_N, int l, int x,int y) {
	if (sub_N == l) {
		// 2. 회전
		Rotation(l, x, y);
		return;
	}
	else {
		int next = sub_N / 2;
		Divide(sub_N / 2, l, x, y);
		Divide(sub_N / 2, l, x + next, y);
		Divide(sub_N / 2, l, x, y + next);
		Divide(sub_N / 2, l, x + next, y + next);
	}
}

// 얼음 녹이기
void Melting(int Real_N) {
	vector<pair<int, int>> candidate;
	for (int j = 0; j < Real_N; j++) {
		for (int k = 0; k < Real_N; k++) {
			if (map[j][k] == 0) continue;
			else {
				// 주위 4방향 검사
				int cnt = 0;
				for (int z = 0; z < 4; z++) {
					int nx = j + dx[z];
					int ny = k + dy[z];
					if (nx < 0 || nx >= Real_N || ny < 0 || ny >= Real_N) continue;
					if (map[nx][ny] != 0) cnt++;
				}
				// 주변에 얼음이 3개보다 적으면 얼음량 감소
				if (cnt < 3) candidate.push_back(make_pair(j, k));
			}
		}
	}

	for (int i = 0; i < candidate.size(); i++) {
		map[candidate[i].first][candidate[i].second]--;
	}

}

// 덩어리 크기 탐색
int search(int Real_N, int x, int y) {
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	visited[x][y] = true;
	int cnt = 1;

	while (!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();
		
		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx < 0 || nx >= Real_N || ny < 0 || ny >= Real_N) continue;
			if (map[nx][ny] != 0 && !visited[nx][ny]) {
				visited[nx][ny] = true;
				q.push(make_pair(nx, ny));
				cnt++;
			}
		}
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> Q;
	int Real_N = (int)pow(2, N);

	// 맵정보 입력
	for (int i = 0; i < Real_N; i++) {
		for (int j = 0; j < Real_N; j++) {
			cin >> map[i][j];
		}
	}

	// 파이어 스톰 단계 정보 입력
	for (int i = 0; i < Q; i++) {
		int temp;
		cin >> temp;
		L.push_back(temp);
	}

	// Q번 반복
	for(int i=0; i<Q; i++){
		// 1. 격자 나누기
		// 2. 회전
		Divide(Real_N, (int)pow(2, L[i]), 0, 0);
		// 3. 얼음 크기 변경 

		Melting(Real_N);
	}
	int biggest = 0;
	int count = 0;
	// 덩어리 크기 및 남은 얼음 개수 계산
	for (int i = 0; i < Real_N; i++) {
		for (int j = 0; j < Real_N; j++) {
			// 총 합계
			count += map[i][j];
			// 얼음이 없거나 다른 덩어리에 포함된거 pass
			if (map[i][j] == 0) continue;
			if(!visited[i][j]){
				int temp = search(Real_N, i, j);
				biggest = biggest > temp ? biggest : temp;
			}
		}
	}

	cout << count << endl << biggest << endl;

	return 0;
}

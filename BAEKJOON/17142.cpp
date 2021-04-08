/*
연구소 3

1. 바이러스 M개 조합 (combination)
2. 조합 별, 바이러스가 모두 퍼지기 위한 최소 시간구하기 (bfs-djk 응용)
*/

#define _CRT_NO_SECURE_WARNINGS
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<tuple>
#include<algorithm>

using namespace std;

#define INF 987654321
#define MIN(A,B) A<B?A:B
#define MAX(A,B) A>B?A:B
// N: 연구소 크기
// M: 선택할 바이러스 개수
// ans: 전체 조합 중 최소시간
int N, M;
int ans;

// map: 연구소 현황 
// visited: 방문여부 체크
// d[x][y]: x, y 위치에 바이러스가 퍼지기 위한 최소 시간
int map[50][50];
bool visited[50][50];
int d[50][50];

// 4 방위
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

// 바이러스 리스트
vector<pair<int, int>> viruses;

bool init_virus[10];
void solve(int n, int r, int idx, int cnt) {
	// 조합 완성
	if (cnt == r) {
		// 2. 해당 조합에 대해 최소 시간 계산
			// 바이러스가 전부 퍼졌는지 확인 하기 위한 변수
		int empty_place = 0;
		// 각 위치 최소시간 및 방문 여부 저장할 배열 초기화
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// 값 초기화
				d[i][j] = INF;
				visited[i][j] = false;
				// 벽이면 방문한 것으로 설정
				if (map[i][j] == 1) visited[i][j] = true;
				// 빈공간이면
				if (map[i][j] == 0) empty_place++;
			}
		}

		// 위치(x, y)
		queue<tuple<int, int>> q;
		for (int i = 0; i < n; i++) {
			if (init_virus[i]) {
				// 선택된 바이러스들 큐에 삽입
				q.push(make_tuple(viruses[i].first, viruses[i].second));
				// 선택된 바이러스 위치 방문한 것으로 설정
				visited[viruses[i].first][viruses[i].second] = true;
				// 시작점임으로 시간 0 으로 설정
				d[viruses[i].first][viruses[i].second] = 0;
			}
		}

		// 바이러스가 퍼지기 까지 현재 조합에서 최대 시간
		int T_time = 0;
		// 바이러스가 전부 퍼졌는지 확인 하기 위한 변수
		int spreaded_place = 0;
		// 큐가 빌 때까지 바이러스 확산
		while (!q.empty()) {
			// 현재 노드 정보 get
			int x = get<0>(q.front());
			int y = get<1>(q.front());
			
			q.pop();

			// 방문표시
			visited[x][y] = true;
			for (int i = 0; i < 4; i++) {
				// 다음 좌표
				int nx = x + dx[i];
				int ny = y + dy[i];
				// 맵을 벗어나면
				if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
				// 벽이아니고 방문한 적이 없으면
				if (map[nx][ny] != 1 && d[nx][ny] == INF) {
					d[nx][ny] = d[x][y] + 1;
					if (map[nx][ny] == 0) {
						T_time = d[nx][ny];
						spreaded_place++;
					}
					q.push(make_tuple(nx, ny));
				}
			}
		}
		
		// 3. 글로벌 최소 시간 업데이트
		if(spreaded_place == empty_place){
			ans = MIN(T_time, ans);
		}

		return;
	}
	for (int i = idx; i < n; i++) {
		if (!init_virus[i]) { // 선택하지 않은 바이러스이면
			init_virus[i] = true; // 선택 표시 하고
			solve(n, r, i, cnt + 1); // 다음 진행
			init_virus[i] = false; // 선택 표시 해제
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	// 초기 맵 정보 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			// 바이러스 위치 정보 저장
			if (map[i][j] == 2) {
				viruses.push_back(make_pair(i, j));
			}
		}
	}

	// 1. 바이러스 선택 조합 (개수 viruses.size()_C_M)
	// 2. 해당 조합에 대해 최소 시간 계산
	// 3. 글로벌 최소 시간 업데이트
	ans = INF;
	memset(init_virus, false, sizeof(init_virus));
	solve(viruses.size(), M, 0, 0);

	// ans 값이 안변했으면, 바이러스를 모두 퍼뜨리지 못한 경우
	if (ans == INF) ans = -1;
	cout << ans << endl;

	return 0;
}

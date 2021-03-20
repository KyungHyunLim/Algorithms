/*
파핑파핑 지뢰찾기

0. map, visited 초기
1. map[301][301] -> -1: 지뢰, 0으로 초기화
-> 입력받으면서 지뢰면, 8방향의 map값 ++ / 방문처리
2. bfs 수행 횟수 계산 
  2-1. map이 0인 값 부터 bfs 수행 (0은 영역확장이 가능 -> 최소 클릭)
  2-2. 남은 0이 아닌 숫자 값의 개수 더해주기
3. 결과 출력
*/
#include<iostream>
#include<vector>
#include <queue>
#include <cstring>
using namespace std;

int map[301][301];
bool visited[301][301];
int N;

int dx[8] = {-1,-1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

bool bfs(int x, int y) {
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	
	while (!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		visited[cx][cy] = true;
		q.pop();

		for (int i = 0; i < 8; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if (visited[nx][ny] || map[nx][ny] == -1) continue;
			if (map[nx][ny] != 0) {
				visited[nx][ny] = true;
			}
			else {
				//visited[nx][ny] = true;
				q.push(make_pair(nx, ny));
			}
		}
	}
}


int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		//초기화
		memset(map, 0, sizeof(map));
		memset(visited, false, sizeof(visited));

		cin >> N;

		//게임판 상태 입력
		//지뢰 주위 map 값++, 방문처리
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				char temp;
				cin >> temp;
				if (temp == '*') {
					map[i][j] = -1;
					visited[i][j] = true;
					for (int z = 0; z < 8; z++) {
						int nx = i + dx[z];
						int ny = j + dy[z];
						if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
						map[nx][ny] += 1;
					}
				}
			}
		}

		//0먼저 클릭
		int answer = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j]) continue;
				if (map[i][j] == 0) {
					bfs(i, j);
					answer++;
				}
			}
		}

		//남은 수 처리
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j]) continue;
				//bfs(i, j);
				answer++;				
			}
		}

		cout << "#" << test_case << " " << answer << endl;

	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

/*
인구 이동

1. bfs로 구역 나누기 -> 모든 나라에 대해, 방문한 적이 없고, 인구 이동이 가능하면 bfs 실행
2. 구역별 인구수 업데이트 -> 탐색중 경로 저장, 저장된 경로 내 나라 인구수 변경
*/
#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
#include<cmath>
using namespace std;

// N: 맵 크기
// L, R: 국경 오픈 기준 (L이상 R이하)
int N, L, R;
// 각 나라 인구수
int population[51][51];
// 각 나라가 포함될 연합 번호
int group[51][51];
// 국경 개폐여부
bool isOpen[51][51];

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

bool Can_Move(int x, int y){
    for (int i = 0; i < 4; i++)    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && ny >= 0 && nx < N && ny < N)        {
            if (L <= abs(population[x][y] - population[nx][ny]) &&
                abs(population[x][y] - population[nx][ny]) <= R)
                return true;
        }
    }
    return false;
}

void search(int i, int j) {
    queue<pair<int, int>> Q, Nq;
    Q.push(make_pair(i, j)); // 순회
    Nq.push(make_pair(i, j)); // 경로
    isOpen[i][j] = true;
    int Sum = 0;
    int Cnt = 0;

    while (!Q.empty())    {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        Sum = Sum + population[x][y];
        Cnt = Cnt + 1;
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 맵을 벗어나면
            if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
            // 이미 방문/열려있는 곳이면
            if (isOpen[nx][ny] != 0) continue;
            // 인구 이동 조건에 맞으면
            if (L <= abs(population[x][y] - population[nx][ny]) && 
                abs(population[x][y] - population[nx][ny]) <= R){
                isOpen[nx][ny] = true;
                Q.push(make_pair(nx, ny));
                Nq.push(make_pair(nx, ny));
            }
        }
    }

    int Value = Sum / Cnt;

    // 같은 연합 인구수 통합
    while (Nq.empty() == 0){
        int cx = Nq.front().first;
        int cy = Nq.front().second;
        Nq.pop();
        population[cx][cy] = Value;
    }
}

int main() {
	cin >> N >> L >> R;
	// 인구수 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> population[i][j];
		}
	}

	// 인구이동 횟수
    int time = 0;
    bool check = true;
    // 인구이동이 없을 때까지
    while (check) {
        check = false;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // 아직 방문안했고, 연합이 가능하면
                bool test = Can_Move(i, j);
                if (!isOpen[i][j] && test) {
                    // 연합 구성
                    search(i, j);
                    check = true;
                }
            }
        }
        if (check) time++;
        memset(isOpen, false, sizeof(isOpen));
    }
    
    cout << time << endl;
	
	return 0;
}

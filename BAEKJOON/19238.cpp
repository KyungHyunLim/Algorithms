/*
스타트택시

1. 최단 거리 손님 선택 - bfs
  1.1 손님들 위치, 거리 모두 구하기
  1.2 조건에 맞게 정렬
  1.3 맨 앞 손님 선택
  1.4 택시 이동 및 연료 감소
2. 목적지 까지 이동 - bfs
  2.1 선택 손님 목적지 까지 이동
  2.2 손님 완료 표시
  2.3 택시 이동 및 연료 감소, 충전
3. 모든 손님 다 태우면 종료
  3.1 1-2 중간에 경로를 못찾으면 종료 -1
  3.2 1-2 중간에 연료가 부족해도 종료 -1
*/
#include<iostream>
#include<vector>
#include<queue>
#include<tuple>
#include<algorithm>
using namespace std;

// N: 맵크기
// M: 승객수
// fuel: 초기 연료
int N, M, fuel;

struct person {
	bool fish;
	int d;
	int sx, sy; // 출발 좌표
	int ax, ay; // 도착 좌표
};
// 승객 정보
person persons[401];
// 맵
int map[21][21];
bool visited[21][21];
// 택시 위치
int tx, ty;

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

bool Cmp(person A, person B)
{
	/* 조건에 맞는 손님을 찾기 위해서 Vector를 정렬하기 위한 기준 설정. */
	if (A.d <= B.d)
	{
		if (A.d == B.d)
		{
			if (A.sx <= B.sx)
			{
				if (A.sx == B.sx)
				{
					if (A.sy < B.sy)
					{
						return true;
					}
					return false;
				}
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
}

// 최단 거리 손님 찾기
int find_person(int x, int y, int t_fuel) {
	// 택시 위치가 손님이면
	if (map[x][y] < 0 && !persons[-map[x][y]].fish) {
		return map[x][y];
	}
	// 시작 위치 입력 , {x, y, 거리, 남은 연료}
	queue<tuple<int,int,int,int>> q;
	q.push(make_tuple(x, y, 0, t_fuel));
	visited[x][y] = true;

	vector<person> p;
	while (!q.empty()) {
		int x = get<0>(q.front());
		int y = get<1>(q.front());
		int d = get<2>(q.front());
		int tf = get<3>(q.front());
		q.pop();

		if (map[x][y] < 0 && !persons[-map[x][y]].fish) {
			person temp;
			temp.d = d;
			temp.sx = x;
			temp.sy = y;
			p.push_back(temp);
		}
		// 연료가 부족하면 진행 불가
		if (tf == 0) continue;

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			// 맵을 벗어나면 안됨
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			// 벽은 갈수 없음
			if (map[nx][ny] == 1) continue;
			// 빈칸이면 이동
			if (map[nx][ny] <= 0 && !visited[nx][ny]) {
				visited[nx][ny] = true;
				q.push(make_tuple(nx, ny, d + 1, tf - 1));
			}
		}
	}

	if (p.size() == 0) return 1;

	sort(p.begin(), p.end(), Cmp);
	int num = map[p[0].sx][p[0].sy];
	map[p[0].sx][p[0].sy] = 0;
	tx = p[0].sx;
	ty = p[0].sy;
	//cout << "손님까지 이동거리: " << p[0].d <<endl;
	fuel -= p[0].d;
	return num;
}

// 목적지 까지 이동
bool find_dest(int start_x, int start_y, int dest_x, int dest_y, int t_fuel) {
	queue<tuple<int, int, int, int>> q;
	q.push(make_tuple(start_x, start_y, 0, t_fuel));
	visited[start_x][start_y] = true;

	while (!q.empty()) {
		int x = get<0>(q.front());
		int y = get<1>(q.front());
		int d = get<2>(q.front());
		int tf = get<3>(q.front());
		q.pop();

		// 목적지에 도착했으면
		if (x == dest_x && y == dest_y) {
			// 연료 두배 충전
			//cout << "도착지 까지 이동거리: " << d << endl;
			fuel -= d;
			fuel += (d*2);
			tx = x;
			ty = y;
			return true;
		}
		
		// 연료가 부족하면
		if (tf == 0) {
			if (!q.empty()) continue;
			return false;
		}

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			// 맵을 벗어나면 안됨
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			// 벽은 갈수 없음
			if (map[nx][ny] == 1) continue;
			if (!visited[nx][ny]) {
				visited[nx][ny] = true;
				q.push(make_tuple(nx, ny, d+1, tf-1));
			}
		}
	}
	return false;
}

// visited 함수 초기화 memset 사용시 메모리 초과 오류...
void initilize() {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			visited[i][j] = false;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	// 기본 정보 입력
	cin >> N >> M >> fuel;

	// 맵 정보 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	// 택시 정보 입력
	cin >> tx >> ty;
	tx--; ty--;
	// 승객 정보 입력, 번호 부여 (맵에 표시: -1, -2, ..., -M);
	for (int i = 1; i <= M; i++) {
		cin >>	persons[i].sx >> persons[i].sy >>
			persons[i].ax >> persons[i].ay;
		map[persons[i].sx-1][persons[i].sy-1] = (-1 * i);
	}
	
	// 승객수
	int amount = M;
	while (amount != 0 && fuel > 0) {
		//cout << endl;
		//cout << "초기 택시 위치, 연료: " << tx << " " << ty << " " << fuel << endl;
		// 1. 최단 거리 손님 선택
		initilize();
		int p = -1 * find_person(tx, ty, fuel);
		
		//cout << "손님 선택 후: " << p << " " << tx << " " << ty << " " << fuel << endl;
		//cout << "출발지: " << persons[p].sx - 1 << " " << persons[p].sy - 1 << endl;
		//cout << "도착지: " << persons[p].ax - 1 << " " << persons[p].ay - 1 << endl;
		if (fuel < 0) { fuel = -1;  break; }
		if (p < 0) { fuel = -1; break; }
		// 2. 목적지 까지 이동
		initilize();
			// 이동 중 실패시
		if (find_dest(tx, ty, persons[p].ax-1, persons[p].ay-1, fuel) == false) {
			// -1로 바꾸고 영업 종료
			fuel = -1;
		}
		// 완료 처리
		persons[p].fish = true;
		amount--;
		//cout << "목적지 이동 후: " << " " << tx << " " << ty << " " << fuel << endl;
		//cout << endl;
	}

	cout << fuel << endl;

	return 0;
}

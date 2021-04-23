/*
캐슬 디펜스

1. 궁수 위치 선정 (조합)
2. 게임 시뮬레이션 진행 (1에서 생성되는 조합마다 게임 진행)
  2.1 궁수 공격
    2.1.1 공격 가능 몬스터 탐색
      - 공격범위가 bfs의 확장과 동일
      - 시계방향 확장으로 왼쪽에 있는 적을 먼저 타겟팅
    2.2.2 동일한 타겟팅이 있을 수 있음으로 죽을 몬스터 저장 후 탐색 종료 후에 제거 (총 몬스터수 감소, 죽인 몬스터 수 증가)
  2.2 몬스터 이동
    2.2.1 단순 반복문
    2.2.2 성에 도달한 몬스터 제거(총 몬스터수 감소)
  2.3 몬스터 수가 0이 되면 종료

*/
#include<iostream>
#include<cstring>
#include<queue>
#include<fstream>
using namespace std;

// NxM : 맵크기
// D : 궁수 사거리
int N, M, D;

int map[15][15];
int copy_map[15][15];
bool visited[15][15];
int dx[3] = { 0, -1, 0 };
int dy[3] = { -1, 0, 1 };
int enemy_count;
int temp_enemy_count;
int attaked_enemy;
int ans;

//ofstream out("result.txt");

pair<int, int> search(int loc) {
    queue<pair<int, pair<int, int>>> q;
    q.push(make_pair(1, make_pair(N - 1, loc)));
    visited[N - 1][loc] = true;
    if (copy_map[N - 1][loc] == 1) return make_pair(N - 1, loc);
    else {
        while (!q.empty()) {
            int d = q.front().first;
            int cx = q.front().second.first;
            int cy = q.front().second.second;
            q.pop();

            if (copy_map[cx][cy] == 1) return make_pair(cx, cy);
            if (d == D) continue;

            for (int i = 0; i < 3; i++) {
                int nx = cx + dx[i];
                int ny = cy + dy[i];
                if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
                if (visited[nx][ny]) continue;
                if (d + 1 > D) continue;
                visited[nx][ny] = true;
                q.push(make_pair(d + 1, make_pair(nx, ny)));
            }
        }
    }

    return make_pair(-1, -1);
}


void Attack(vector<int> archers) {
    vector<pair<int, int>> attacked_enenmy;
    bool attacked[15][15];
    memset(attacked, false, sizeof(attacked));
    // 공격할 적 탐색 및 제거
    for (int i = 0; i < 3; i++) {
        memset(visited, false, sizeof(visited));
        pair<int, int> temp = search(archers[i]);
        if (temp.first == -1) continue;
        if (attacked[temp.first][temp.second]) continue;
        attacked[temp.first][temp.second] = true;
        attacked_enenmy.push_back(make_pair(temp.first, temp.second));
    }

    for (int i = 0; i < attacked_enenmy.size(); i++) {
        temp_enemy_count--;
        attaked_enemy++;
        copy_map[attacked_enenmy[i].first][attacked_enenmy[i].second] = 0;
    }
}

void Move() {
    for (int j = 0; j < M; j++) {
        for (int i = N - 1; i > 0; i--) {
            //if (copy_map[i - 1][j] != 1) continue;
            // 성에 도달한 것들 없애기
            if (i == N - 1 && copy_map[i][j] == 1) temp_enemy_count--;
            // 한칸씩 이동
            copy_map[i][j] = copy_map[i - 1][j];
        }
        copy_map[0][j] = 0;
    }
}

/*
void Print() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            out << copy_map[i][j] << "\t";
        }
        out << endl;
    }
    out << endl;
}
*/

void Copy(int a[][15], int b[][15]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            b[i][j] = a[i][j];
        }
    }
}

bool selected_arc[15];
void locate_arc(int idx, int cnt) {
    if (cnt == 3) { // 궁수 배치 완료
        vector<int> archers;
        for (int i = 0; i < M; i++) {
            if (selected_arc[i]) {
                archers.push_back(i);
                //cout << i << "\t";
            }
        }
       
        //out << "궁수 위치: " << archers[0] << archers[1] << archers[2] << endl;

        // 게임 진행
        Copy(map, copy_map);
        temp_enemy_count = enemy_count;
        attaked_enemy = 0;
        while (temp_enemy_count != 0) {
            
            //---------------------------------------------------------
            //out << "궁수 공격전: (남은적수: " << temp_enemy_count << endl;
           // Print();
            //---------------------------------------------------------

            // 궁수 공격
            Attack(archers);

            //---------------------------------------------------------
            //out << "궁수 공격후: (남은적수: " << temp_enemy_count << endl;
            //Print();
            //---------------------------------------------------------

            // 몬스터 이동
            Move();

            //---------------------------------------------------------
            //out << "몬스터 이동 후: (남은적수: " << temp_enemy_count <<  endl;
            //Print();
            //---------------------------------------------------------
        }

        ans = ans > attaked_enemy ? ans : attaked_enemy;
         
        //out << "종료" << endl;
        //cout << endl;
        return;
    }
    else {
        for (int i = idx; i < M; i++) {
            if (selected_arc[i]) continue;
            selected_arc[i] = true;
            locate_arc(i, cnt + 1);
            selected_arc[i] = false;
        }
    }
    
}

int main() {

    cin >> N >> M >> D;
    ans = 0;
    enemy_count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) enemy_count++;
        }
    }

    // 궁수 배치 조합 및 조합에 따른 게임 진행
    locate_arc(0, 0);

    cout << ans << endl;
    //out << "답: " << ans << endl;
    return 0;
}

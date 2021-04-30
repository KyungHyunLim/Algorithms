#include <string>
/*
방문길이

- visited[x][y][nx][ny] 로 (x,y) -> (nx,ny) 방문 여부 체크로 거리 확인
- 마이너스 인덱스를 사용할 수 없으므로, +5, +5 해 0~10범위로 사용
*/
#include <map>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;

int solution(string dirs) {
    
    map<char, vector<int>> info;
  // 명령에 따른 이동방향
    info['U'] = {-1,0};
    info['D'] = {1,0};
    info['R'] = {0,1};
    info['L'] = {0,-1};
    
  // 방문 여부체크
    bool visited[11][11][11][11];
  // false로 초기화
    memset(visited, false, sizeof(visited));
  // 방문길이
    int answer = 0;
  // 시작위치
    int x = 5;
    int y = 5;
  // 명령에 따라이동
    for(int i=0; i<dirs.length(); i++){
        int nx = x + info[dirs[i]][0];
        int ny = y + info[dirs[i]][1];
        // 맵밖으로 나가는 명령 무시
        if(nx < 0 || nx >= 11 || ny < 0 || ny >= 11) continue;
        // 한번도 가본적 없는 길이면 answer ++;
        if(!visited[x][y][nx][ny] && !visited[nx][ny][x][y]) {
            answer++;
        }
        // 방문표시
        visited[x][y][nx][ny] = true;
        visited[nx][ny][x][y] = true;
        // 이동
        x = nx;
        y = ny;
    }
    
    return answer;
}

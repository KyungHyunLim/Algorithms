/*
네트워크

- 기본적인 형태의 BFS (구역 나누기와 비슷)

1. 주어진 컴퓨터에 대해 BFS 수행
2. 1번 수행에 같은 네트워크면 모두 방문 표시가됨
3. 따라서 BFS 수행 횟수가 곧 네트워크 개수
*/
#include <string>
#include <vector>
#include <queue>
using namespace std;

// 중복 탐색 방지용
bool visited[200];

void search(int x, vector<vector<int>> computers){
    queue<int> q;
    q.push(x);
    visited[x] = true;
    
    while(!q.empty()){
        int cx = q.front();
        q.pop();
        
        for(int i=0; i<computers[cx].size(); i++){
            // 네트워크가 연결되어 있으면 진행
            if(computers[cx][i]){
                // 방문한 컴퓨터가 아니면 진행
                if(visited[i]) continue;
                // 방문 표시
                visited[i] = true;
                // 다음 서칭을 위해 큐에 삽입
                q.push(i);
            }
        }
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    for(int i=0; i<computers.size(); i++){
        // 아직 방문하지 않은 노드에 대해서
        if(!visited[i]) {
            search(i, computers);
            // 탐색한번에 네트워트 1개 완성
            answer ++;
        }
    }
    return answer;
}

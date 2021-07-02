/*
순위.

graph => 각 노드간의 승패관계

floydwarshall 알고리즘
=> A->B를 바로 가는 비용과 A->C->B로 거쳐가는 비용을 모두 비교해 최소 거리 정보를 이차원 배열에 저장

floydwarshall 알고리즘 응용
=> 
1. 기본적인 A-B의 승패관계 표현
2. 탐색을 통해 A-C-B의 승패관계 표현
3. 가능한 관계를 모두 찾으면 2번 종료
4. 모든 선수들과의 승패관계가 파악됬으면, 순위 판별 가능
*/
#include <string>
#include <vector>

using namespace std;

bool graph[101][101];
bool D[101][101];

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    
    // results에서 앞 원소가 이긴 선수, 뒤 원소가 패배한 선수
    for(auto result : results) graph[result[0]][result[1]] = true;
    
    // 모든 선수들에 대해서
    for(int i=1; i<=n; i++){
        // j: 이긴선수
        for(int j=1; j<=n; j++){
            // k: 패배한 선수
            for(int k=1; k<=n; k++){
                // j가 i에게 이기고 i가 k에게 이겼으면,
                // j도 k에게 이김
                // j > i > k 관계 입력
                if(graph[j][i] && graph[i][k]) graph[j][k] = true;
            }
        }
    }
    
    // 모든 선수들에 대해서 검사
    for(int i=1; i<=n; i++){
        int count = 0;
        for(int j=1; j<=n; j++){
            // 이기거나 지는 관계를 가지고 있으면 count 증가
            if(graph[i][j] || graph[j][i]) count++;
        }
        // 모든 선수에 대해 관계를 정의할 수 있으면, 순위 판별가능
        if(count == n-1) answer++;
    }
    
    return answer;
}

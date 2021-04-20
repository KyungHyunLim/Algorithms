/*
여행경로

- DFS
- MAP 활용 <string int> // <int string>
- SET을 이용한  알파벳 순 정렬
- 티켓 중복 가능 -> bool이 아니라 int로 처리해야함
*/

#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

set<string> airports;   // 공항 이름(Unique) -> 알파벳 순으로 정렬
set<string>::iterator iter; 
map<string, int> airport_to_idx; // 공항 이름 -> index
map<int, string> idx_to_airport; // index -> 공항 이름
vector<int> t[10001]; // 티켓 정보 t[i] 공항에서 갈수 있는 공항들
int used[10001][10001];
int amount; // 티켓 수
vector<string> ans; // 정답 경로
bool flag; // 경로 완성 되면 true

void DFS(int node, int count, string path) {
    if (flag) return; // 경로 완성됬으면 나머지 재귀 함수들 종료
    if (path.length() - 1 == amount) { // 경로 완성
        // 경로 ans에 넣기
        // 알파벳 순으로 탐색했으므로 처음 완성되는 경로가 답
        for (int i = 0; i < path.length(); i++) {
            ans.push_back(idx_to_airport[path[i] - '0']);
        }
        flag = true;
        return;
    }
    else {
        // 인덱스가 작을 수록 사전에 먼저 나오는 알파벳
        sort(t[node].begin(), t[node].end());
        for (int i = 0; i < t[node].size(); i++) {
            // 다음 공항
            int nn = t[node][i];
            // 이미 사용했으면 pass
            if (used[node][nn] == 0) continue;
            // 사용 안했으면 추가
            // 개수 감소
            used[node][nn]--;
            DFS(nn, count + 1, path + to_string(nn));
            // 개수 복원
            used[node][nn]++;
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    // 티켓 수
    amount = tickets.size();
    
    // SET을 이용한 알파벳순 인덱스 부여
    for (int i = 0; i < tickets.size(); i++) {
        airports.insert(tickets[i][0]);
        airports.insert(tickets[i][1]);
    }

    // SET을 이용한 알파벳순 인덱스 기반으로 HASH_MAP 생성
    int idx = 1;
    for (iter = airports.begin(); iter != airports.end(); iter++) {
        airport_to_idx[*iter] = idx;
        idx_to_airport[idx] = *iter;
        idx++;
    }
    
    // 티켓 정보 인덱스로 변환
    for (int i = 0; i < tickets.size(); i++) {
        t[airport_to_idx[tickets[i][0]]].push_back(airport_to_idx[tickets[i][1]]);
        used[airport_to_idx[tickets[i][0]]][airport_to_idx[tickets[i][1]]]++;
    }

    // 시작 노드, 사용한 티켓수, 경로
    flag = false;
    DFS(airport_to_idx["ICN"], 0, to_string(airport_to_idx["ICN"]));
    return ans;
}

int main() {
    // 테스트용
   // solution({ {"ICN", "JFK"}, {"HND", "IAD"}, {"JFK", "HND"} });
    //solution({ {"ICN", "SFO"}, { "ICN", "ATL" }, { "SFO", "ATL" }, { "ATL", "ICN" }, { "ATL","SFO" } });
    solution({ {"A", "C"}, { "B", "D" }, { "E", "F" }, { "Z", "I" }, { "H","L" } });

    return 0;
}

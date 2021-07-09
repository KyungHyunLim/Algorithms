/*
모두 0으로 만들기

* 트리구조
* 리프노드부터 탐색

1. 초기값 세팅, 트리구조 생성
2. 리프노드로 이동 후 탐색 시작 [Post-order]
3. 현재 노드 값을 부모에 더해주기
4. 2-3 반복.
*/
#include <string>
#include <vector>
#include <iostream>

using namespace std;
long long answer = 0;

void Dfs(vector<vector<int>>& tree, vector<long long>& weight, int cur, int prev){
    // leaf 노드 까지 이동
    for(int i=0; i<tree[cur].size(); i++){
        // 부모 아니면 이동 가능
        if(tree[cur][i] != prev) Dfs(tree, weight, tree[cur][i], cur);
    }
    // leaf 노드 도달시, 부모에 노드 값 계산해주기
    // cout << cur << endl;
    weight[prev] += weight[cur];
    answer += abs(weight[cur]);
}

long long solution(vector<int> a, vector<vector<int>> edges) {
    
    
    vector<long long> weight(a.size());
    // 초기 가중치 값 세팅
    for(int i=0; i<a.size(); i++) weight[i] = a[i];
    
    // 트리구조 생성
    vector<vector<int>> tree(a.size());
    for(int i=0; i<edges.size(); i++){
        tree[edges[i][0]].push_back(edges[i][1]);
        tree[edges[i][1]].push_back(edges[i][0]);
    }
    
    // 탐색
    Dfs(tree, weight, 0, 0);
    // cout << weight[0] << endl;
    
    // 루트 값이 0이 되면, 0으로 만들기 가능
    if(weight[0] == 0) return answer;
    else return -1;
}

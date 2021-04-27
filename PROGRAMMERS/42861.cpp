/*
섬연결하기

최소 신장트리 - 크루스칼 
*/
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> parent;

// 부모 구하기
int getparent(int x) {
    if (parent[x] == x) return x;
    return parent[x] = getparent(parent[x]);
}

// 부모 설정
void Union(int x, int y) {
    int px = getparent(x);
    int py = getparent(y);
    cout << x << ":" << px << " " << y << ":" << py << endl;
    if (px < py) parent[py] = px;
    else parent[px] = py;
}

// 부모 같은지 비교
bool Find(int x, int y) {
    int px = getparent(x);
    int py = getparent(y);
    return px == py;
}

// 간선 비용기준 오름차순 정렬
bool cmp(vector<int> x, vector<int> y) {
    return x[2] < y[2];
}

int solution(int n, vector<vector<int>> costs) {
    // 부모 정보 (사이클 방지)
    int ans = 0;
    // 일단 자기 자신을 부모로 설정
    for (int i = 0; i < n; i++) {
        parent.push_back(i);
    }

    // 간선 정렬
    sort(costs.begin(), costs.end(), cmp);

    // 비용이 적은 간선부터 탐색
    for (int i = 0; i < costs.size(); i++) {
        // 사이클이 생기지 않는 간선이면
        if (!Find(costs[i][0], costs[i][1])) {
            cout << costs[i][0] << " " << costs[i][1] << endl;
            // 선택, 해당 노드들 부모 통일
            Union(costs[i][0], costs[i][1]);

            for (int i = 0; i < n; i++) {
                cout << parent[i] << " ";
            }
            cout << endl;

            // 코스트 증가
            ans += costs[i][2];
        }
    }
    return ans;
}

int main() {

    solution(4, { {0, 1, 1},{0, 2, 2},{1, 2, 5},{1, 3, 1},{2, 3, 8} });

    return 0;
}

#define MAX(A,B) A>B?A:B;

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

vector<int> problems[200001];

int main() {
    int N;
    cin >> N;

    int max_dead_line = 0;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;

        problems[a].push_back(b);
        max_dead_line = MAX(max_dead_line, a);
    }

    int answer = 0;
    priority_queue<int> pq;
    for (int i = 1; i <= max_dead_line; i++) {
        for (int j = 0; j < problems[i].size(); j++) {
            int T = i;
            pq.push(-problems[i][j]);
            if (T < pq.size()) pq.pop();
        }
    }

    int s = pq.size();
    for (int i = 0; i < s; i++) {
        answer += -pq.top();
        pq.pop();
    }

    cout << answer;

    return 0;
}

/*
for (int j = T; j <= max_dead_line; j++) {
            if (!problems[j].empty()) {
                for (int i = 0; i < problems[j].size(); i++) {
                    if (!problems[j][i][1]) {
                        answer += problems[j][i][0];
                        problems[j][i][1] = true;
                        break;
                    }
                }
                break;
            }
        }
*/
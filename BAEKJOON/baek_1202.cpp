#define MAX(A,B) A > B ? A : B;
#define ll long long

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int N, K;
int bag[300000];
pair<int, int> jewelry[300000];
priority_queue<int> q;

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;

    for (int i = 0; i < N; i++) {
        cin >> jewelry[i].first >> jewelry[i].second;
    }

    for (int i = 0; i < K; i++) {
        cin >> bag[i];
    }

    sort(jewelry, jewelry + N);
    sort(bag, bag + K);

    ll answer = 0;
    int idx = 0;

    for (int i = 0; i < K; i++) {
        while (idx < N && jewelry[idx].first <= bag[i]) {
            q.push(jewelry[idx++].second);
        }

        if (!q.empty()) {
            answer += q.top();
            q.pop();
        }
    }

    cout << answer;

    return 0;
}
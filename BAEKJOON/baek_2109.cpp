#define MAX(A,B) A > B ? A : B;

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

struct college {
    int d;
    int p;
};

bool compare(college a, college b) {
    if (a.d < b.d) return true;
    else if (a.d > b.d) return false;
    else {
        if (a.p > b.p) return true;
        else return false;
    }
}

int N;
vector<college> colleges;

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    //input
    cin >> N;
    for (int i = 0; i < N; i++) {
        college temp;
        cin >> temp.p >> temp.d;
        colleges.push_back(temp);
    }

    //solution
    sort(colleges.begin(), colleges.end(), compare);

    priority_queue<int> q;
    int answer = 0;

    for (int i = 0; i < N; i++) {
        answer += colleges[i].p;
        q.push(-colleges[i].p);
        if (colleges[i].d < q.size()) {
            answer += q.top();
            q.pop();
        }
    }

    cout << answer;

    return 0;
}
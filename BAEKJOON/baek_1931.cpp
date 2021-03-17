#define MAX(A,B) A>B?A:B;

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

vector<vector<int>> list;

bool compare(vector<int> a, vector<int> b) {
    if (a[1] < b[1]) return true;
    else if (a[1] == b[1]) {
        if (a[0] < b[0]) return true;
        else return false;
    }
    return false;
}


int main() {
   
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;

        list.push_back({ a,b });
    }

    sort(list.begin(), list.end(), compare);

    int answer = 1;
    int end = list[0][1];
    for (int i = 1; i < list.size(); i++) {
        while (list[i][0] < end) {
            i++;
            if (i >= list.size()) {
                cout << answer;
                return 0;
            }
        }
        answer++;
        end = list[i][1];
    }

    cout << answer;

    return 0;
}

#define MAX(A,B) A>B?A:B;

#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<string> s;
int R, C;
int answer;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

void solution(int x,int y, int c, bool* alpha) {
    answer = MAX(answer, c);
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= R || ny < 0 || ny >= C || alpha[s[nx][ny] - 'A']) continue;
        alpha[s[nx][ny] - 'A'] = true;
        solution(nx, ny, c+1, alpha);
        alpha[s[nx][ny] - 'A'] = false;
    }
}

int main() {
    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        string temp;
        cin >> temp;
        s.push_back(temp);
    }
    bool alpha[26] = { false, };
    answer = 0;
    alpha[s[0][0] - 'A'] = true;
    solution(0,0,1, alpha);
    cout << answer;

    return 0;
}

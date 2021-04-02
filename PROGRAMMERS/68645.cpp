/*
삼각 달팽이

1
2 12
3 13 11
4 141510
5 6 7 8 9

아래 -> 왼쪽 -> 대각선 -> 아래 ... 반복적으로 움직임
n -> n-1 -> n-2 -> ... -> 1 이동 숫자도 1씩 감소

위 방식으로 배열 채우고, 개수만큼씩 출력

*/

#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

int dx[3] = { 1, 0, -1 };
int dy[3] = { 0, 1, -1 };
int map[1000][1000];

vector<int> solution(int n) {

    memset(map, 0, sizeof(map));

    //i 진행 횟수
    int dir = 0;
    int num = 1;
    int x = 0; int y = 0;
    for (int i = n; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            map[x][y] = num;
            if (j + 1 == i) {
                dir++;
                dir = dir % 3;
            }
            x = x + dx[dir];
            y = y + dy[dir];
            num++;
        }

    }

    vector<int> answer;
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i+1; j++) {
            answer.push_back(map[i][j]);
        }
    }

    return answer;
}

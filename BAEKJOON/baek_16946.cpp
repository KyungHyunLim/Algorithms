#define _CRT_SECURE_NO_WARNINGS
#define MIN(A,B) A<B?A:B;

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string.h>

using namespace std;

struct fish {
    int x;
    int y;
    int dist;
};

int dx[4] = { 0, 0, -1, 1};
int dy[4] = { 1, -1, 0, 0};
int N;
int map[21][21];
int sx, sy;
int answer;
/*
x, y = 아기상어 위치
size = 크기
eat = 먹은 물고기 갯수
n_fish = 총물고기 수
*/

bool compare(fish a, fish b) {
    if (a.dist > b.dist) return true;
    else if (a.dist == b.dist && a.x > b.x) return true;
    else if (a.dist == b.dist && a.x == b.x && a.y > b.y) return true;
    return false;
}

fish find_fish(int x, int y, int size) {
    queue<pair<int, int>> q;
    vector<fish> candidates;
    bool visit[21][21] = { false, };

    int minimum_distance = 1e9;
    q.push(make_pair(x, y));
    
    while (!q.empty()) {
        int now_x = q.front().first;
        int now_y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int next_x = now_x + dx[i];
            int next_y = now_y + dy[i];
            // 맵 밖을 벗어 나면 No
            if (next_x < 0 || next_x >= N || next_y < 0 || next_y >= N) continue;

            // 방문을 안했고
            if (visit[next_x][next_y]) continue;

            // 물고기 크기가 상어보다 크면 No
            if (map[next_x][next_y] > size) continue;
            
            int temp_dis = abs(next_x - x) + abs(next_y - y);

            if (temp_dis > minimum_distance) continue;

            visit[next_x][next_y] = true;
            if (map[next_x][next_y] != 0) {
                q.push(make_pair(next_x, next_y));
                minimum_distance = MIN(minimum_distance, temp_dis);
                candidates.push_back({ next_x, next_y, temp_dis });
            }
            else {
                q.push(make_pair(next_x, next_y));
            }
        }
    }
  
    sort(candidates.begin(), candidates.end(), compare);

    return candidates[0];
}

void solution(int x, int y, int size, int eat, int n_fish) {
    while (n_fish != 0) {
        fish selected = find_fish(x, y, size);
        x = selected.x;
        y = selected.y;
        answer += selected.dist;
        if (map[x][y] != size) {
            eat++;
            map[x][y] = 0;
            n_fish--;
        }
        
        if (size == eat) {
            size += 1;
            eat = 0;
        }  
    }
}

int main() {
    cin >> N;

    int number_of_fish = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] > 0 && map[i][j] < 7) {
                number_of_fish++;
            }
            if (map[i][j] == 9) {
                sx = i;
                sy = j;
            }
        }
    }

    if (number_of_fish == 0) {
        cout << 0;
    }
    else {
        answer = 0;
        solution(sx, sy, 2, 0, number_of_fish);
        cout << answer;
    }

    return 0;
}
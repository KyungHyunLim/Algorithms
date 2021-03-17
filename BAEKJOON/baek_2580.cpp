#define MAX(A,B) A>B?A:B;
#define MIN(A,B) A<B?A:B;

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

struct point {
    int x;
    int y;
    vector<int> candidate;
};

vector<point> list_0;
int map[10][10];

int calc_axis(int x, int y) {
    if (x < 3 && y < 3) return 0;
    if (x < 3 && y >= 3 && y < 6) return 3;
    if (x < 3 && y >= 6) return 6;

    if (x >= 3 && x < 6 && y < 3) return 1;
    if (x >= 3 && x < 6 && y >= 3 && y < 6) return 4;
    if (x >= 3 && x < 6 && y >= 6) return 7;

    if (x >= 6 && y < 3) return 2;
    if (x >= 6 && y >= 3 && y < 6) return 5;
    if (x >= 6 && y >= 6) return 8;
}

void calc_candidate(bool row[10][10], bool col[10][10], bool box[10][10]) {
    for (int i = 0; i < list_0.size(); i++) {
        int x = list_0[i].x;
        int y = list_0[i].y;
        
        int z = calc_axis(x, y);
        for (int j = 1; j < 10; j++) {
            if (!row[y][j] && !col[x][j] && !box[z][j]) {
                list_0[i].candidate.push_back(j);
                //cout << j << endl;
            }
        }
    }
}
/*
1 3 5 4 6 9 2 7 8
7 8 2 1 3 5 6 4 9
4 6 9 2 7 8 1 3 5
3 2 1 5 4 6 8 9 7
8 7 4 9 1 3 5 2 6
5 9 6 8 2 7 4 1 3
9 1 7 6 5 2 3 8 4
6 4 3 7 8 1 9 5 2
2 5 8 3 9 4 7 6 1
*/
void solution(int n, bool row[10][10], bool col[10][10], bool box[10][10]) {
    if (n == list_0.size()) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << map[i][j];
                if (j != 8) cout << " ";
            }
            cout << endl;
        }
        exit(0);
    }
    else {
        for (int i = 0; i < list_0.size(); i++) {
            int x = list_0[i].x;
            int y = list_0[i].y;
            int z = calc_axis(x, y);

            for (int j = 0; j < list_0[i].candidate.size(); j++) {
                int candi = list_0[i].candidate[j];
                if (!row[y][candi] && !col[x][candi] && !box[z][candi]) {
                    row[y][candi] = true;
                    col[x][candi] = true;
                    box[z][candi] = true;
                    int temp = map[x][y];
                    map[x][y] = candi;
                    solution(n + 1, row, col, box);

                    row[y][candi] = false;
                    col[x][candi] = false;
                    box[z][candi] = false;
                    map[x][y] = temp;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    bool row[10][10] = { false, };
    bool col[10][10] = { false, };
    bool box[10][10] = { false, };
   

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> map[i][j];
            if (map[i][j] == 0) {
                list_0.push_back({ i,j });
            }
            row[j][map[i][j]] = true;
            col[i][map[i][j]] = true;
            int z = calc_axis(i, j);
            box[z][map[i][j]] = true;
        }
    }

    int count_0 = list_0.size();

    calc_candidate(row, col, box);
    solution(0, row, col, box);

    return 0;
}

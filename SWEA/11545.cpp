/*
틱택톰

- 4X4 게임판 상태 검사
- 행(4) + 열(4) + 대각선(2): 10개의 상태에 대해 검사
- .:0, X: 1, O: 2, T: 3 으로 치환(답 입력의 편의성)
- string res[4] = { "Draw", "X won", "O won", "Game has not completed" };

1. 행열 검사
 [행열 동일]
 1-1 첫문자 획득
 1-2 나머지 열에 문자가 동일 or T인지 확인, 조건에 맞으면 count 증가
 1-3 count가 4면, 승리(종료) 조건 만족, break
2. 대각선 검사
 [행렬 검사와 동일]
 단, 반복문 없이 한번에 검사 가능
3. 결과 출력
*/
#include<iostream>
#include<vector>
using namespace std;

int map[4][4];
vector<int> answer;
string res[4] = { "Draw", "X won", "O won", "Game has not completed" };

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int bin = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				char temp;
				cin >> temp;
				if (temp == '.') { map[i][j] = 0; bin++; }
				if (temp == 'X') map[i][j] = 1;
				if (temp == 'O') map[i][j] = 2;
				if (temp == 'T') map[i][j] = 3;
			}
		}

		//행열 검사 
		for (int i = 0; i < 4; i++) {
			int row = 0;
			int col = 0;
			int row_cnt = 0;
			int col_cnt = 0;
			
			for (int j = 0; j < 4; j++) {
				if (row == 0) {
					if (map[i][j] == 1 || map[i][j] == 2) {
						row_cnt++;
						row = map[i][j];
					}
					else if (map[i][j] == 3) {
						row_cnt++;
					}
				}
				else {
					if (map[i][j] == row || map[i][j] == 3) {
						row_cnt++;
					}
				}

				if (col == 0) {
					if (map[j][i] == 1 || map[j][i] == 2) {
						col_cnt++;
						col = map[j][i];
					}
					else if (map[j][i] == 3) {
						col_cnt++;
					}
				}
				else {
					if (map[j][i] == col || map[j][i] == 3) {
						col_cnt++;
					}
				}
			}
			
			if (col_cnt == 4) {
				answer.push_back(col);
				break;
			}

			if (row_cnt == 4) {
				answer.push_back(row);
				break;
			}
		}

		//대각선 검사
		if (answer.size() != test_case) {
			int left_right = 0;
			int right_left = 0;
			int left_right_cnt = 0;
			int right_left_cnt = 0;
			for (int i = 0; i < 4; i++) {
				if (left_right == 0) {
					if (map[i][i] == 1 || map[i][i] == 2) {
						left_right_cnt++;
						left_right = map[i][i];
					}
					else if (map[i][i] == 3) {
						left_right_cnt++;
					}
				}
				else {
					if (map[i][i] == left_right || map[i][i] == 3) {
						left_right_cnt++;
					}
				}

				if (right_left == 0) {
					if (map[i][3-i] == 1 || map[i][3-i] == 2) {
						right_left_cnt++;
						right_left = map[i][3 - i];
					}
					else if (map[i][3 - i] == 3) {
						right_left_cnt++;
					}
				}
				else {
					if (map[i][3 - i] == right_left || map[i][3 - i] == 3) {
						right_left_cnt++;
					}
				}
			}
			if (left_right_cnt == 4) {
				answer.push_back(left_right);
			}

			if (right_left_cnt == 4) {
				answer.push_back(right_left);
			}
		}

		if (answer.size() < test_case) {
			if (bin == 0) answer.push_back(0);
			else answer.push_back(3);
		}
	}

	for (int i = 0; i < answer.size(); i++) {
		cout << "#" << i + 1 << " " << res[answer[i]] << endl;
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

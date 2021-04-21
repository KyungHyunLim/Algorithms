/*
괄호 추가하기

핵심 => 괄호치기 = 연산자 선택으로 보기

1. 숫자와 연산자 나누어 저장 => 계산시 (num[0] op[0] num[1]) 형태
2. 비트 마스킹을 활용해 연산자 선택/미선택 구분
3. 선택/미선택 여부에 따라
  3-1 계산해서 새로운 수식에 삽입
  3-2 그대로 새로운 수식에 삽입
  3-3 최대값 업데이트
*/
#define _CRT_NO_SECURE_WARNINGS
#include<iostream>
#include<vector>

using namespace std;

// N: 수식의 길이
int N;
// num: 숫자
int num[20];
// op: 연산자
char op[20];
// 연산자에 따른 연산 반환
int operation(int a, int b, char o) {
	switch (o) {
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*': 
		return a * b;
		break;
	}
	return 0;
}

int main() {
	cin >> N;
	
	int idx =0, idx2 = 0;
	int ans = 0;
	// 숫자 연산자 나누어 입력
	for (int i = 0; i < N; i++) {
		char temp;
		cin >> temp;
    // 숫자
		if (i % 2 == 0) num[idx++] = temp - '0';
    // 연산자
		else op[idx2++] = temp;
	}
  // 괄호가 없을 때 합 구하기
	ans = num[0];
	for (int i = 0; i < idx2; i++) {
		//cout << ans << " " << op[i] << " " << num[i + 1] << " = ";
		ans = operation(ans, num[i+1], op[i]);
		//cout << ans << endl;
		
	}
	//cout << ans << endl;
	// 괄호를 치는 것
	// 괄호 사이 하나의 연산자만이 들어갈 수 있고
	// 중첩된 괄호 또한 불가능하기 때문에
	// 연산자를 선택하고, 선택된 연산자는 먼저 계산
	for (int i = 1; i < (1 << idx2); i++) { // idx2가 3 이면 001, 010, 011, 100, 101, 111 이됨
		vector<int> temp_num; // 새롭게 만들어질 수식의 숫자
		vector<char> temp_op; // 새롭게 만들어질 수식의 연산자
		for (int j = 0; j < idx2; j++) {
			// 해당 bit이 1이면 선택된 연산자 임으로 계산 해서 새로운 수식에 삽입
			if (i & (1 << j)) { // 선택되었는지 확인
        // 계산해서 숫자 넣기
				temp_num.push_back(operation(num[j], num[j + 1], op[j]));
        // 마지막 연산자가 아니면 다음 연산자 삽입 (연속선택 불가능 하므로)
				if (j + 1 != idx2) temp_op.push_back(op[j+1]);
				j++; // 연속 선택 불가능
        // 마지막 이전 연산자가 선택되었을 경우 숫자가 남음으로 숫자 삽입
        // E.g 3+8*(7-9)*2 => 3+8*-2*2
        // 72 번째줄 까지만 처리 해주면 3+8*-2* 가됨
				if (j + 1== idx2) temp_num.push_back(num[j + 1]);
			}
      // 선택되지 않은 연산자의 경우
			else {
        // 숫자와 연산자를 새로운 수식에 그대로 삽입
				temp_num.push_back(num[j]);
				temp_op.push_back(op[j]);
        // 마지막 연산자가 선택되지 않은 경우 마지막 숫자 삽입
				if (j + 1 == idx2) {
					temp_num.push_back(num[j+1]);
				}
			}
		}
    // 새롭게 완성된 수식 계산
		int sum = temp_num[0];
		//printf("%d ", sum);
		for (int k = 0; k < temp_op.size(); k++) {
			//printf("%c %d ", temp_op[k], temp_num[k + 1]);
			sum = operation(sum, temp_num[k + 1], temp_op[k]);
		}
		//printf(" = %d\n", sum);
		//cout << endl;
    // 현재까지의 최대값과 비교해 
		ans = ans > sum ? ans : sum;
	}

	cout << ans << endl;
	return 0;
}

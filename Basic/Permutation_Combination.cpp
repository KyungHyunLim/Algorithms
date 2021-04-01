#include <iostream>
#include <vector>

using namespace std;

/*
순열 <Permutationt>
*/
void swap(char* a, char* b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

void permutation(char *str, int l, int r) {
	if (l == r) {
		for (int i = 0; i < r; i++) {
			cout << str[i];
		}
		cout << endl;
		return;
	}
	else {
		for (int i = 0; i < r; i++) {
			swap(str + l, str + i);
			permutation(str, l + 1, r);
			swap(str + l, str + i);
		}
	}
}

/*
조합 <Combination>
_by_index = 인덱스로 원소선택
_by_element = 원소를 직접적으로 선택
*/
void combination_by_index(char* str, int* index, int n, int r, int i, int next) {
	if (i == r) {
		for (int i = 0; i < r; i++) {
			cout << str[index[i]];
		}
		cout << endl;
		return;
	}
	if (next >= n) return;

	index[i] = next;
	combination_by_index(str, index, n, r, i + 1, next + 1);
	combination_by_index(str, index, n, r, i, next + 1);
}

char combination_array[10];
int top = 0;
void push(char c) {
	if (top < 9) {
		combination_array[top++] = c;
		combination_array[top] = '\0';
	}

}

void pop() {
	if (top > 0) {
		combination_array[top--] = '\0';
	}
}

void combination_by_element(const char* str, int length, int offset, int k) {
	if (k == 0) {
		cout << combination_array << endl;
		return;
	}

	for (int i = offset; i <= length - k; i++) {
		push(str[i]);
		combination_by_element(str, length, i + 1, k - 1);
		pop();
	}
}

int main() {
	char temp[10] = "abcde";
	cout << "permutation: " << endl;
	permutation(temp, 0, 3);

	cout << endl;

	cout << "combination_by_element: " << endl;
	combination_by_element(temp, 5, 0, 3);

	cout << endl;

	cout << "combination_by_index: " << endl;
	int ind[5] = { 0,1,2,3,4 };
	combination_by_index(temp, ind, 5, 3, 0, 0);

	return 0;
}

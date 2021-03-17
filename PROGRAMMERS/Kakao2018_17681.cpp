#include <string>
#include <vector>
#include <iostream>

using namespace std;

int get_base(int num) {
    int base = 1;

    while (true) {
        if (num % base == num) break;
        base *= 2;
    }

    return base;
}

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    vector<int> mul_mx;

    int max = -1;
    for (int i = 0; i < arr1.size(); i++) {
        int temp = arr1[i] | arr2[i];
        mul_mx.push_back(temp);
        max = temp > max ? temp : max;
    }

    int base = get_base(max);

    for(int i = 0; i < mul_mx.size(); i++) {
        int sh = base;
        answer.push_back("");
        while (sh != 1) {
            sh = sh >> 1;
            if ((sh & mul_mx[i]) == 0) answer[i] += " ";
            else answer[i] += "#";
        }
    }

    return answer;
}

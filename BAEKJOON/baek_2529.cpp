#define MAX(A,B) A>B?A:B;
#define MIN(A,B) A<B?A:B;

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

vector<char> sign;
string min_ = "9999999999";
string max_ = "0000000000";

bool isok(int a, int b, char s) {
    if (s == '<') {
        if (a < b) return true;
        else return false;
    }
    else {
        if (a > b) return true;
        else return false;
    }
}

void solution(int idx, int target, bool* numbers, string result) {
    if (idx == target) {
        if (stoll (min_) > stoll(result)) {
            min_ = result;
        }
        if (stoll(max_) < stoll(result)) {
            max_ = result;
        }
        return;
    }
    else {
        for (int i = 0; i < 10; i++) {
            //방문했으면
            if (numbers[i]) continue; 
            //부등호에 안맞으면
            if (!result.empty() && !isok(result[idx - 1] - '0', i, sign[idx-1])) continue;
            numbers[i] = true;
            solution(idx + 1, target, numbers, result + to_string(i));
            numbers[i] = false;
        }
    }
}
/*
9
< < < > < < > < >
*/
int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        char temp;
        cin >> temp;
        sign.push_back(temp);
    }
    bool numbers[10] = { false, };
    solution(0,N+1, numbers, "");
          
    cout << max_ << endl;
    cout << min_ << endl;

    return 0;
}

#define MAX(A,B) A>B?A:B;
#define MIN(A,B) A<B?A:B;

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
using namespace std;

vector<string> equations;
vector<char> alphabets;
int N;
long long int answer;

void solution(int idx, int target, bool* numbers, map<char, char> dic) {
    if (idx == target) {
        long long int sum = 0;
        for (int i = 0; i < equations.size(); i++) {
            string e1;
            for (int j = 0; j < equations[i].size(); j++) {
                char temp = dic[equations[i][j]];
                e1 += temp;
            }
            sum += stoll(e1);
        }
        answer = MAX(answer, sum);
        return;
    }
    else {
        for (int i = 10 - dic.size(); i < 10 ; i++) {
            //방문했으면
            if (numbers[i]) continue;
            numbers[i] = true;
            dic[alphabets[idx]] = i+'0';
            solution(idx + 1, target, numbers, dic);
            numbers[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    map<char, char> dic;
    for (int i = 0; i < N; i++) {
        string temp;
        cin >> temp;
        equations.push_back(temp);
        for (int j = 0; j < temp.length(); j++) {
            if (dic.find(temp[j]) == dic.end()) {
                dic.insert(make_pair(temp[j], -1));
                alphabets.push_back(temp[j]);
            }
        }
    }
    bool numbers[10] = { false, };
    solution(0, dic.size(), numbers, dic);
    cout << answer;   

    return 0;
}

/*
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
vector<string> word;
int result = 0;
int alpha[26];		//어떤 알파벳이 사용되었는지 확인

void cal() {
    for (int i = 0; i < word.size(); i++) {
        int pow = 1;
        for (int j = word[i].size() - 1; j >= 0; j--) {
            int val = word[i][j] - 'A';
            alpha[val] += pow;
            pow *= 10;
        }
    }
    sort(alpha, alpha + 26);
    int num = 9;네입
    for (int i = 25; i >= 0; i--) {
        if (alpha[i] == 0) break;
        result += (alpha[i] * num);
        num--;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int num;
    string ss;
    cin >> num;
    for (int i = 0; i < num; i++) {
        cin >> ss;
        word.push_back(ss);
    }
    cal();
    cout << result;
    system("pause");
    return 0;
}
*/
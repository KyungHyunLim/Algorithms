#include <string>
#include <iostream>
#include <vector>

using namespace std;

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int solution(string s) {
    int answer = s.length();

    for (int i = 1; i < s.length() / 2 + 1; i++) {
        string first = s.substr(0, i);
        int same = 1;
        string temp;
        for (int j = i; j < s.length(); j += i) {
            if (first == s.substr(j, i)) same++;
            else {
                if (same != 1) temp += to_string(same);
                temp += first;
                first = s.substr(j, i);
                same = 1;
            }
        }
        if (same != 1) temp += to_string(same);
        temp += first;
        answer = min(answer, temp.length());            
    }
    return answer;
}

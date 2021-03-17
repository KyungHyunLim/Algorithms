#include <string>
#include <vector>
#include <stack>

using namespace std;
int pos;

bool isCorrect(string str) {
    bool ret = true;
    int left = 0, right = 0;

    stack<char> s;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            left++;
            s.push('(');
        }
        else {
            right++;
            if (s.empty()) {
                ret = false;
            }
            else {
                s.pop();
            }
        }
        if (left == right) {
            pos = i + 1;
            return ret;
        }
    }
    return ret;
}

string solution(string p) {
    
    if (p.length() == 0) {
        return "";
    }
    
    bool correct = isCorrect(p);
    string u = p.substr(0, pos);
    string v = p.substr(pos, p.length());

    if (correct) {
        return u + solution(v);
    }  
    
    string answer = "(" + solution(v) + ")";
    for (int i = 1; i < u.length() - 1; i++) {
        if (u[i] == '(') {
            answer += ")";
        }
        else {
            answer += "(";
        }
    }
    return answer;
}
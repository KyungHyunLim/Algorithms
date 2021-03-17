#include <string>
#include <vector>
#include <iostream>
using namespace std;

string solution(string new_id) {
    string answer = "";

    //1. 대소문자 치환 & 2. 사용가능한 문자 제외 모두 제거 & 3. '.' 여러개 한개로 치환
    int idx = 0;
    for (int i = 0; i < new_id.length(); i++) {
        //1. 대소문자 치환
        if (new_id[i] >= 'A' && new_id[i] <= 'Z') {
            new_id[i] = new_id[i] - 'A' + 'a';
        }

        //2. 사용가능한 문자 제외 모두 제거, 
        if ((new_id[i] >= '0' && new_id[i] <= '9') || (new_id[i] >= 'a' && new_id[i] <= 'z') || new_id[i] == '.' || new_id[i] == '-' || new_id[i] == '_'){
            //3. '.' 여러개 한개로 치환
            if (answer.length() > 0 && answer[idx - 1] == '.' && new_id[i] == '.') continue;
            answer += new_id[i];
            idx++;
        }
    }

    //4. '.'가 처음, 또는 끝이면 제거
    if (answer.length() > 0 && answer[0] == '.') answer.erase(0, 1);
    if (answer.length() > 0 && answer[answer.length()-1] == '.') answer.erase(answer.length() - 1, 1);
    
    //5. 빈문자열이면 a 추가
    if (answer.length() == 0) answer = "a";

    //6. 16자 이상이면 다 제거
    if (answer.length() > 15) answer.erase(15, answer.length() - 15);
    //15번째가 .일수 있음.
    if (answer.length() > 0 && answer[answer.length() - 1] == '.') answer.erase(answer.length() - 1, 1);

    //7. 길이가 2 이하면 3이 될때까지 마지막 글자 만복
    char last_one = answer[answer.length()-1];
    while (answer.length() < 3) {
        answer += last_one;
    }

    return answer;
}

int main() {
    string a;
    //a = solution("...!@BaT#*..y.abcdefghijklm");
    //cout << a << endl;

    //a = solution("z-+.^.");
    //cout << a << endl;

    //a = solution("=.=");
    //cout << a << endl;

    //a = solution("123_.def");
    //cout << a << endl;

    a = solution("abcdefghijklmn.p");
    cout << a << endl;
    return 0;
}
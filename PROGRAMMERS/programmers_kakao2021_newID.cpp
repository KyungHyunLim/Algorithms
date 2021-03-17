#include <string>
#include <vector>
#include <iostream>
using namespace std;

string solution(string new_id) {
    string answer = "";

    //1. ��ҹ��� ġȯ & 2. ��밡���� ���� ���� ��� ���� & 3. '.' ������ �Ѱ��� ġȯ
    int idx = 0;
    for (int i = 0; i < new_id.length(); i++) {
        //1. ��ҹ��� ġȯ
        if (new_id[i] >= 'A' && new_id[i] <= 'Z') {
            new_id[i] = new_id[i] - 'A' + 'a';
        }

        //2. ��밡���� ���� ���� ��� ����, 
        if ((new_id[i] >= '0' && new_id[i] <= '9') || (new_id[i] >= 'a' && new_id[i] <= 'z') || new_id[i] == '.' || new_id[i] == '-' || new_id[i] == '_'){
            //3. '.' ������ �Ѱ��� ġȯ
            if (answer.length() > 0 && answer[idx - 1] == '.' && new_id[i] == '.') continue;
            answer += new_id[i];
            idx++;
        }
    }

    //4. '.'�� ó��, �Ǵ� ���̸� ����
    if (answer.length() > 0 && answer[0] == '.') answer.erase(0, 1);
    if (answer.length() > 0 && answer[answer.length()-1] == '.') answer.erase(answer.length() - 1, 1);
    
    //5. ���ڿ��̸� a �߰�
    if (answer.length() == 0) answer = "a";

    //6. 16�� �̻��̸� �� ����
    if (answer.length() > 15) answer.erase(15, answer.length() - 15);
    //15��°�� .�ϼ� ����.
    if (answer.length() > 0 && answer[answer.length() - 1] == '.') answer.erase(answer.length() - 1, 1);

    //7. ���̰� 2 ���ϸ� 3�� �ɶ����� ������ ���� ����
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
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int power(int num, int x) {
    int temp = 1;
    for (int i = 0; i < x; i++) {
        temp = temp * num;
    }
    
    return temp;
}

int bonus_to_int(char b) {
    if (b == 'D') {
        return 2;
    }
    else if(b == 'T'){
        return 3;
    }
    else {
        return 1;
    }
}

int solution(string dartResult) {
    int answer = 0;
    vector<int> score_list;


    for (int i = 0; i < dartResult.length(); i++) {
        int num = dartResult[i] - '0';
        i++;
        if (dartResult[i] - '0' == 0) { num = 10; i++; }

        char bonus = dartResult[i];
        char option = '!';
        if ((i+1) < dartResult.length() && (dartResult[i+1] - '0' < 0 || dartResult[i+1] - '0' > 9)) {//숫자가 아니면 처리
            i++;
            option = dartResult[i];

            num = power(num, bonus_to_int(bonus));

            if (option == '*') {
                if (score_list.size() == 0) {
                    score_list.push_back(num * 2);
                }
                else {
                    score_list.push_back(num * 2);
                    score_list[score_list.size() - 2] = score_list[score_list.size() - 2] * 2;
                }
            }
            else if(option =='#'){
                score_list.push_back(num * (-1));
            }
        }
        else {
            score_list.push_back(power(num, bonus_to_int(bonus)));
        }
    }

    for (int i = 0; i < score_list.size(); i++) {
        answer += score_list[i];
    }

    return answer;
}

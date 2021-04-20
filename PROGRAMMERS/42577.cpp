/*
전화번호 목록

- 전화번호의 일부분을 map의 key로 사용해
중복된 key가 등장 했을 경우 false, 아니면 true

* 문자열이 길이 순서대로 되어있어야함

*/
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

bool solution(vector<string> phone_book) {

    // 부분 전화번호, 개수 (초기값 = 0)
    // 1 이상이면 접두사가 있는 것
    map<string, int> data;
    vector<pair<int, string>> copy;
    // 최소길이 전화번호 구하기
    int min = 30;
    for (int i = 0; i < phone_book.size(); i++) {
        //min = min > phone_book[i].length() ? phone_book[i].length() : min;
        copy.push_back(make_pair(phone_book[i].length(), phone_book[i]));
    }

    sort(copy.begin(), copy.end(), less<pair<int, string>>());
    min = copy[0].first;

    // 최소단위로 잘라 비교
    bool answer = true;
    // 모든 전화번호
    for (int i = 0; i < copy.size(); i++) {
        // 최소 길이부터 잘라서 data에 입력
        for (int j = min; j <= copy[i].first; j++) {
            // 부분 전화번호
            string sub = copy[i].second.substr(0, j);
            //cout << sub << endl;
            // 0이 아니면 접두사가 되므로 반복문 종료
            if (data[sub] != 0) { answer = false; break; }
            // 0이면 개수 증가
            else {
                if (j == copy[i].first) data[sub] += 1;
            }
        }
        // 0이 아니면 접두사가 되므로 반복문 종료
        if (!answer) break;
    }

    return answer;
}

/*
튜플

- 문자열 내부에서 숫자 찾기
- counting sort와 유사(등장 횟수가 많은 순으로 정리)
*/
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

// 현재 문자가 숫자인지 아닌지 확인
bool isnum(char a) {
    if (a >= '0' && a <= '9') return true;
    return false;
}

// value가 큰 순으로 기준 (숫자 - 등장 횟수)
bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.second > b.second) return true;
    return false;
}

// 솔루션
vector<int> solution(string s) {
    vector<int> answer;
    map<int, int> nums;
    // 문자열 순회
    for (int i = 0; i < s.length(); i++) {
        // 문자가 숫자이면
        if (isnum(s[i])) {
            string temp = "";
            // 숫자로 만들어줌
            while (isnum(s[i])) {
                temp += s[i];
                i++;
            }
            // 해당 숫자 등장 횟수 증가
            nums[stoi(temp)] ++;
            
        }
    }
    
    // 등장 횟수 기준 정렬을 위해 벡터로 변환
    vector<pair<int, int>> v(nums.begin(), nums.end());
    // 정의한 cmp 함수를 이용해 정렬
    sort(v.begin(), v.end(), cmp);
    
    // 순서대로 숫자 answer에 입력
    for (int i = 0; i < v.size(); i++) {
        answer.push_back(v[i].first);
    }

    return answer;
}

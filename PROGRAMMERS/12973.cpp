/*
짝지어 제거하기

* 자료구조 스택 활용
* 문자열 길이 => 1,000,000 한번탐색에 끝내야함

*/
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int solution(string s)
{
    int answer = -1;
  // 스택 선언
    stack<char> st;
    
  // 문자열 순회
    for(int i=0; i < s.length(); i++){
      // 스택이 비었으면 스택에 push
        if(st.empty()) st.push(s[i]);
      // 아니면 다음을 검사
        else{
          // 스택의 탑이 문자열의 현재 문자와 같으면 제거
            if(st.top() == s[i]) st.pop();
          // 아니면 스택에 push
            else st.push(s[i]);
        }
    }
  // 스택의 크기가 0이면 모두 지워 진것 임으로 1
  // 아니면 0
    answer = st.size() == 0 ? 1:0;
    
    return answer;
}

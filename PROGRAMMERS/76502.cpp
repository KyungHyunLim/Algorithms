/*
괄호 회전하기

*/
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 검사
bool check(string s){
    char a[1000]; // 스택
    int top = 0; // top 포인터
  // 문자 하나씩 검사
    for(int i=0; i<s.length(); i++){
      // 여는 괄호면 스택에 삽입
        if(s[i] == '(' || s[i] == '{' || s[i] == '[') a[top++] = s[i];
        else{
          // 맨 위에 있는 요소와 비교
            top--;
          // top이 -가 되면 짝이 안맞는것, 
            if(top < 0) return false;
          // top에 있는 괄호와 닫는 괄호 짝이 안맞으면 안됨
            if(!((a[top] == '(' && s[i] == ')') || 
               (a[top] == '{' && s[i] == '}') || 
               (a[top] == '[' && s[i] == ']'))) return false;
        }
    }
  // 문자열 순회 종료시 top이 0이 아니면 짝이 안맞는것
    if(top != 0) return false;
  // 이외 경우 바른 문자열
    return true;
}

int solution(string s) {
    int answer = 0;
  // 문자열 하나씩 쉬프트 하며 검사
    for(int i=0; i<s.length(); i++){
        //cout << s << endl;
        if(check(s)) answer++;
        char temp = s[0];
        s = s.substr(1);
        s += temp;
    }
    
    return answer;
}

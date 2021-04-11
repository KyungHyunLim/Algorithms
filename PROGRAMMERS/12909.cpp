/*
올바른 괄호

스택 사용 (top 만 사용해도 무방)
- ( 면 top 1 증가
- ) 면 top 1 감소, top이 0 이하가 되면 false 리턴
- 문자열 순회 후 top이 0이면  true else false
*/
#include<string>
#include <iostream>

using namespace std;

char stack[100000];
int top = 0;
bool solution(string s)
{
    for(int i=0; i<s.length(); i++){
        if(s[i] == '(') stack[top++] == '(';
        else {
            top--;
            if(top < 0) return false;
        }
    }
    
    return top==0;
}

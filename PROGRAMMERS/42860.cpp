/*
조이스틱(그리디)

- 개인적으로 어려운 분야...


*/
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(string name) {
    
    int answer = 0;
    int cnt = 0;
    int cur = 0;
    string temp(name.length(), 'A');
    
    while(1){
        // 위로 돌릴지 아래로 돌릴지 선택
        if(temp[cur] != name[cur]){ 
            answer = answer + (('Z' + 1 - name[cur] > name[cur] - 'A') ? name[cur] - 'A'  : 'Z' + 1 - name[cur]);
            temp[cur] = name[cur];
        }
        if(name == temp) break;
        
        // 왼쪽 오른쪽 선택
        for(int i=1; i<name.length(); i++){
            if(name[(i+cur)%name.length()] != temp[(i+cur)%name.length()]){
                cur = (i+cur)%name.length();
                answer += i;
                break;
            }
            else if((name[(cur + name.length() - i) % name.length()] 
                != temp[(cur + name.length() - i) % name.length()])){
                cur = (cur + name.length() - i) % name.length();
                answer += i;
                break;
            }
         }
    }

    return answer;
}

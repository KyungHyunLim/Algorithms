/*
월간 코드 챌린지 1
이진 변환 반복하기

1. 1개수 세기/0개수 세기
2. 1개수 2진 변환
3. 1-2 반복
*/
#include <string>
#include <vector>

using namespace std;

vector<int> solution(string s) {
    vector<int> answer;
    
    answer.push_back(0);
    answer.push_back(0);
 
    while(s != "1"){
        int length = 0;
        for(int i=0; i<s.length(); i++){
            if(s[i] == '1') length++;
            else answer[1]++;
        }
        
        string temp = "";
        while(length > 0){
            int l = length % 2;
            length /= 2;
            temp += (l + '0');
        }
        s = temp;
        answer[0]++;
    }
    
    return answer;
}

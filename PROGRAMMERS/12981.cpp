/*
영어 끝말잇기

map을 이용해 이전에 나왔던 단어를 빠르게 확인
*/
#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer;
    map<string, int> m;
    
    for(int i=0; i<words.size(); i++){
        if(i>=1 && (m[words[i]] != 0 || 
                words[i-1][words[i-1].length()-1] != words[i][0])){
            answer.push_back((i%n)+1);
            answer.push_back((i/n)+1);
            return answer;
        }
        m[words[i]] = 1;
    
    }
    return {0,0};
}

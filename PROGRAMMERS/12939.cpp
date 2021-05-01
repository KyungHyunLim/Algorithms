/*
최댓값과 최솟값

sstream, isringstream ss(s) 사용

steing stringBUffer
geline(ss, stringBuffer, ' ') ==> s를 공백으로 구분한 문자열

*/
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

string solution(string s) {
    string answer = " ";
    istringstream ss(s);
    string stringBuffer;
    
    int _min = 987654321;
    int _max = -987654321;
    
    while (getline(ss, stringBuffer, ' '))
    {
        _min = min(_min, stoi(stringBuffer));
        _max = max(_max, stoi(stringBuffer));
    }
        
    return to_string(_min) + answer + to_string(_max);
}
